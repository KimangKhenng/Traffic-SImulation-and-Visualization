#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H
#include <QtCore>
#include "visualizepanel.h"
class WorkerThread : public QThread
{
    Q_OBJECT
public:
    WorkerThread(QObject *Owner,QObject *parent = 0);
protected:
    void run() override;
private:
    QObject *m_worker;
signals:
    void resultReady();
};

#endif // WORKERTHREAD_H
