#ifndef SLEEPER_H
#define SLEEPER_H

#include <QThread>


class Sleeper : public QThread
{
public:
    Sleeper();
    static void msleep() {
                           QThread::msleep(100);
                       }
};

#endif // SLEEPER_H
