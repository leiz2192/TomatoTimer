#include "TimerLCDDisplay.h"

#include <QTime>
#include <QString>
#include <QMessageBox>

TimerLCDDisplay::TimerLCDDisplay(QWidget *parent, unsigned timecount)
    : LCDDisplay(parent)
    , timecnt_(timecount)
    , seed_(timecount)
{
}

void TimerLCDDisplay::initialize()
{
    LCDDisplay::initialize();
}

void TimerLCDDisplay::displaySlot()
{
    if (timecnt_ < 0) {
        timer_reset();

        QMessageBox::information(this, "Info", "TomatoTime over");

        emit timer_end();
    } else {
        QTime time(0, 0, 0);
        time = time.addSecs(timecnt_);
        QString text = time.toString("hh:mm:ss");
        display_->display(text);

        --timecnt_;
    }
}

void TimerLCDDisplay::timer_reset()
{
    timecnt_ = seed_;
    timer_stop();
}

