#ifndef THEADOBJECT_H
#define THEADOBJECT_H

#include <QThread>

class ThreadObject : public QThread
{
public:
    ThreadObject();
    void run();
};

#endif // THEADOBJECT_H
