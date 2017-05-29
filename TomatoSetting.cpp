#include "TomatoSetting.h"
#include "TomatoConfigFile.h"
#include "CommonDef.h"

#include <QGridLayout>

TomatoSetting::TomatoSetting(QWidget* parent)
    : QDialog(parent)
    , working_time_(DEFAULT_WORKTIMERCOUNT)
    , resting_time_(DEFAULT_RESTTIMERCOUNT)
{
    initConf();
    initWorkSetting();
    initRestSetting();
    initButton();

    QGridLayout* layout = new QGridLayout();
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setHorizontalSpacing(10);
    layout->setVerticalSpacing(10);
    
    layout->addWidget(work_label_.get(),   0, 0, 1, 1);
    layout->addWidget(work_spinbox_.get(), 0, 1, 1, 3);
    layout->addWidget(work_slider_.get(),  0, 4, 1, 16);
    
    layout->addWidget(rest_label_.get(),   1, 0, 1, 1);
    layout->addWidget(rest_spinbox_.get(), 1, 1, 1, 3);
    layout->addWidget(rest_slider_.get(),  1, 4, 1, 16);

    layout->addWidget(reset_button_.get(), 2, 4, 1, 2);
    layout->addWidget(ok_button_.get(),    2, 8, 1, 2);

    setLayout(layout);
    setWindowTitle(tr("Tomato Setting"));
}

void TomatoSetting::initWorkSetting()
{
    work_label_ = std::make_shared<QLabel>(tr("Work:"));

    work_spinbox_ = std::make_shared<QSpinBox>();
    work_spinbox_->setRange(1, 59);
    work_spinbox_->setSingleStep(1);
    work_spinbox_->setSuffix(tr(" min"));
    work_spinbox_->setValue(working_time_);

    work_slider_ = std::make_shared<QSlider>(Qt::Horizontal);
    work_slider_->setRange(1, 59);
    work_slider_->setSingleStep(1);
    work_slider_->setTickInterval(1);
    work_slider_->setTickPosition(QSlider::TicksAbove);
    work_slider_->setValue(working_time_);

    connect(work_slider_.get(), SIGNAL(valueChanged(int)), work_spinbox_.get(), SLOT(setValue(int)));
    connect(work_spinbox_.get(), SIGNAL(valueChanged(int)), work_slider_.get(), SLOT(setValue(int)));
}

void TomatoSetting::initRestSetting()
{
    rest_label_ = std::make_shared<QLabel>(tr("Rest:"));

    rest_spinbox_ = std::make_shared<QSpinBox>();
    rest_spinbox_->setRange(1, 15);
    rest_spinbox_->setSingleStep(1);
    rest_spinbox_->setSuffix(tr(" min"));
    rest_spinbox_->setValue(resting_time_);

    rest_slider_ = std::make_shared<QSlider>(Qt::Horizontal);
    rest_slider_->setRange(1, 15);
    rest_slider_->setSingleStep(1);
    rest_slider_->setTickInterval(1);
    rest_slider_->setTickPosition(QSlider::TicksAbove);
    rest_slider_->setValue(resting_time_);

    connect(rest_slider_.get(), SIGNAL(valueChanged(int)), rest_spinbox_.get(), SLOT(setValue(int)));
    connect(rest_spinbox_.get(), SIGNAL(valueChanged(int)), rest_slider_.get(), SLOT(setValue(int)));
}

void TomatoSetting::initConf()
{
    if (!TomatoConfigFile::readConfigFile(working_time_, resting_time_)) {
        working_time_ = DEFAULT_WORKTIMERCOUNT;
        resting_time_ = DEFAULT_RESTTIMERCOUNT;
    }
}

void TomatoSetting::initButton()
{
    reset_button_ = std::make_shared<QPushButton>(tr("&Reset"));
    connect(reset_button_.get(), SIGNAL(clicked()), this, SLOT(reset_button_slot()));

    ok_button_ = std::make_shared<QPushButton>(tr("&OK"));
    connect(ok_button_.get(), SIGNAL(clicked()), this, SLOT(ok_button_slot()));
}

void TomatoSetting::reset_button_slot()
{
    work_spinbox_->setValue(working_time_);
    rest_spinbox_->setValue(resting_time_);
}

void TomatoSetting::ok_button_slot()
{
    close();
}

