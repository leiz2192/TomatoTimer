#ifndef __WORKLCDDISPLAY_H__
#define __WORKLCDDISPLAY_H__

#include "LCDDisplay.h"
#include "CommonDef.h"

class TimerLCDDisplay : public LCDDisplay
{
public:
    TimerLCDDisplay(QWidget *parent, unsigned timecount);
    virtual ~TimerLCDDisplay() {}

    virtual void initialize();

    void timer_reset();

public slots:
    virtual void displaySlot();

private:
    int timecnt_;
    int seed_;
};

#endif  //__WORKLCDDISPLAY_H__


