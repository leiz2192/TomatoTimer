#ifndef __TOMATOTIMEPIECE_H__
#define __TOMATOTIMEPIECE_H__

//#include <QtWidgets/QMainWindow>
//#include "ui_tomatotimer.h"

#include "LCDDisplay.h"
#include "TimeLCDDisplay.h"
#include "TimerLCDDisplay.h"
#include "CommonDef.h"
#include "TomatoSetting.h"

#include <QHBoxLayout>
#include <QDialog>
#include <QMenuBar>

class TomatoTimepiece : public QDialog
{
    Q_OBJECT

public:
    TomatoTimepiece(QWidget *parent = 0);
    virtual ~TomatoTimepiece() {}

private:
    void initConf();

    void initTomatoMenu();
    void initSettingMenu();
    void initHelpMenu();

private slots:
    void timeslots();
    void exitslots();
    
    void settingslots();

    void workslots();
    void restslots();
    void cancelslots();

private:
    unsigned int working_time_;
    unsigned int resting_time_;
    std::shared_ptr<LCDDisplay> timeDisplay_;
    std::shared_ptr<LCDDisplay> workTimerDisplay_;
    std::shared_ptr<LCDDisplay> restTimerDisplay_;

    std::shared_ptr<QGroupBox> displayGroupBox_;

    std::shared_ptr<QHBoxLayout> mainLayout_;
    
    std::shared_ptr<QMenuBar> menuBar_;

    std::shared_ptr<QMenu> helpMenu_;
    std::shared_ptr<QAction> timeAct_;
    std::shared_ptr<QAction> exitAct_;

    std::shared_ptr<QMenu> tomatoMenu_;
    std::shared_ptr<QAction> workAct_;
    std::shared_ptr<QAction> restAct_;
    std::shared_ptr<QAction> cancelAct_;

    std::shared_ptr<QMenu> settingMenu_;
    std::shared_ptr<QAction> settingAct_;

    std::shared_ptr<TomatoSetting> tomato_setting_;
};

#endif  //__TOMATOTIMEPIECE_H__

