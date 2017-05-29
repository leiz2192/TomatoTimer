//#include "tomatotimer.h"
#include "TomatoTimepiece.h"
#include <QtWidgets/QApplication>

#include "TimeLCDDisplay.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //TomatoTimer w;
    //w.show();

    TomatoTimepiece w;
    w.show();
    return a.exec();
}
