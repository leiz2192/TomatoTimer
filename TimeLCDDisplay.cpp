#include "TimeLCDDisplay.h"

#include <QTime>
#include <QString>

#include <iostream>

TimeLCDDisplay::TimeLCDDisplay(QWidget *parent)
    : LCDDisplay(parent)
{
    initialize();
}

void TimeLCDDisplay::initialize()
{
    LCDDisplay::initialize();
}

void TimeLCDDisplay::displaySlot()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm:ss");
    display_->display(text);
}

