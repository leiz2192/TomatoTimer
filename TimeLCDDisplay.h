#ifndef __TIMEDISPLAY_H__
#define __TIMEDISPLAY_H__

#include "LCDDisplay.h"

class TimeLCDDisplay : public LCDDisplay
{
public:
    TimeLCDDisplay(QWidget *parent = Q_NULLPTR);
    virtual ~TimeLCDDisplay() {}

    virtual void initialize();

protected slots :
    virtual void displaySlot();
};

#endif  //__TIMEDISPLAY_H__

