#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <QDialog>

#include <QLCDNumber>
#include <QTimer>
#include <QGroupBox>

#include <memory>

class LCDDisplay : public QDialog
{
    Q_OBJECT

public :
    LCDDisplay(QWidget *parent = 0);
    virtual ~LCDDisplay() {}
    virtual void initialize();
    
    std::shared_ptr<QGroupBox> getDisplayQGroupBox()
    {
        return displayGroupBox_;
    }

    void timer_start()
    {
        if (timer_.get()) {
            timer_->start(1000);
        }
    }

    void timer_stop()
    {
        if (timer_.get()) {
            timer_->stop();
        }
    }

    virtual void timer_reset() {}

signals:
    void timer_end();

public slots:
    virtual void displaySlot() = 0;

protected :
    std::shared_ptr<QLCDNumber> display_;
    std::shared_ptr<QTimer> timer_;
    std::shared_ptr<QGroupBox> displayGroupBox_;
};

#endif  //__DISPLAY_H__

