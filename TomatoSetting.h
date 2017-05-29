#ifndef __TOMATOSETTING_H__
#define __TOMATOSETTING_H__

#include <QDialog>

#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QPushButton>

#include <memory>

class TomatoSetting : public QDialog
{
    //Q_OBJECT

public:
    TomatoSetting(QWidget* parent = Q_NULLPTR);
    virtual ~TomatoSetting() {}

public slots:
    void reset_button_slot();
    void ok_button_slot();

private:
    void initConf();
    void initWorkSetting();
    void initRestSetting();
    void initButton();

private:
    unsigned int working_time_;
    unsigned int resting_time_;

    std::shared_ptr<QLabel> work_label_;
    std::shared_ptr<QLabel> rest_label_;
    
    std::shared_ptr<QSpinBox> work_spinbox_;
    std::shared_ptr<QSpinBox> rest_spinbox_;

    std::shared_ptr<QSlider> work_slider_;
    std::shared_ptr<QSlider> rest_slider_;

    std::shared_ptr<QPushButton> reset_button_;
    std::shared_ptr<QPushButton> ok_button_;
};

#endif  //__TOMATOSETTING_H__



