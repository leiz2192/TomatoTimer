#include "TomatoTimepiece.h"
#include "TomatoConfigFile.h"

TomatoTimepiece::TomatoTimepiece(QWidget *parent)
    : QDialog(parent)
    , working_time_(DEFAULT_WORKTIMERCOUNT)
    , resting_time_(DEFAULT_RESTTIMERCOUNT)
{
    initConf();
    
    //tomato_setting_ = std::make_shared<TomatoSetting>(parent);

    timeDisplay_ = std::make_shared<TimeLCDDisplay>(parent);
    
    workTimerDisplay_ = std::make_shared<TimerLCDDisplay>(parent, working_time_);
    connect(workTimerDisplay_.get(), SIGNAL(timer_end()), this, SLOT(cancelslots()));
    
    restTimerDisplay_ = std::make_shared<TimerLCDDisplay>(parent, resting_time_);
    connect(restTimerDisplay_.get(), SIGNAL(timer_end()), this, SLOT(cancelslots()));

    displayGroupBox_ = timeDisplay_->getDisplayQGroupBox();
    
    menuBar_ = std::shared_ptr<QMenuBar>(new QMenuBar(this));
    initTomatoMenu();
    //initSettingMenu();
    initHelpMenu();

    mainLayout_ = std::shared_ptr<QHBoxLayout>(new QHBoxLayout());
    mainLayout_->addWidget(displayGroupBox_.get());
    mainLayout_->setMenuBar(menuBar_.get());
    setLayout(mainLayout_.get());

    setWindowTitle(tr(MainDialogName.c_str()));
    resize(289, 112);
}

void TomatoTimepiece::initTomatoMenu()
{
    tomatoMenu_ = std::shared_ptr<QMenu>(menuBar_->addMenu(tr("&TomatoTimer")));

    workAct_ = std::shared_ptr<QAction>(new QAction(tr("&Work"), this));
    connect(workAct_.get(), SIGNAL(triggered()), this, SLOT(workslots()));

    restAct_ = std::shared_ptr<QAction>(new QAction(tr("&Rest"), this));
    connect(restAct_.get(), SIGNAL(triggered()), this, SLOT(restslots()));

    cancelAct_ = std::shared_ptr<QAction>(new QAction(tr("&Cancel"), this));
    connect(cancelAct_.get(), SIGNAL(triggered()), this, SLOT(cancelslots()));
    cancelAct_->setEnabled(false);

    tomatoMenu_->addAction(workAct_.get());
    tomatoMenu_->addAction(restAct_.get());
    tomatoMenu_->addAction(cancelAct_.get());
}

void TomatoTimepiece::initSettingMenu()
{
    settingMenu_ = std::shared_ptr<QMenu>(menuBar_->addMenu(tr("&Setting")));

    settingAct_ = std::shared_ptr<QAction>(new QAction(tr("&TimeSetting"), this));
    connect(settingAct_.get(), SIGNAL(triggered()), this, SLOT(settingslots()));

    settingMenu_->addAction(settingAct_.get());
}

void TomatoTimepiece::initHelpMenu()
{
    helpMenu_ = std::shared_ptr<QMenu>(menuBar_->addMenu(tr("&Help")));

    timeAct_ = std::shared_ptr<QAction>(new QAction(tr("&Time"), this));
    connect(timeAct_.get(), SIGNAL(triggered()), this, SLOT(timeslots()));

    exitAct_ = std::shared_ptr<QAction>(new QAction(tr("&Exit"), this));
    connect(exitAct_.get(), SIGNAL(triggered()), this, SLOT(exitslots()));

    helpMenu_->addAction(timeAct_.get());
    helpMenu_->addAction(exitAct_.get());
}

void TomatoTimepiece::exitslots()
{
    close();
}

void TomatoTimepiece::timeslots()
{
    cancelAct_->setEnabled(false);

    displayGroupBox_->setParent(NULL);

    displayGroupBox_ = timeDisplay_->getDisplayQGroupBox();
    mainLayout_->addWidget(displayGroupBox_.get());
}

void TomatoTimepiece::workslots()
{
    restAct_->setEnabled(false);
    cancelAct_->setEnabled(true);

    displayGroupBox_->setParent(NULL);

    workTimerDisplay_->initialize();
    displayGroupBox_ = workTimerDisplay_->getDisplayQGroupBox();
    mainLayout_->addWidget(displayGroupBox_.get());
}

void TomatoTimepiece::restslots()
{
    workAct_->setEnabled(false);
    cancelAct_->setEnabled(true);

    displayGroupBox_->setParent(NULL);

    restTimerDisplay_->initialize();
    displayGroupBox_ = restTimerDisplay_->getDisplayQGroupBox();
    mainLayout_->addWidget(displayGroupBox_.get());
}

void TomatoTimepiece::cancelslots()
{
    restAct_->setEnabled(true);
    workAct_->setEnabled(true);

    workTimerDisplay_->timer_reset();
    restTimerDisplay_->timer_reset();

    timeslots();
}

void TomatoTimepiece::settingslots()
{
    //tomato_setting_->show();
    tomato_setting_->exec();
}

void TomatoTimepiece::initConf()
{
    if (!TomatoConfigFile::readConfigFile(working_time_, resting_time_)){
        TomatoConfigFile::setConfigFile(working_time_, resting_time_);
    }
}


