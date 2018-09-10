#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H
#include <QThread>

class WorkerThread : public QThread
{
    Q_OBJECT
    void run() override;
signals:
    void resultReady();
};

#endif // WORKERTHREAD_H
