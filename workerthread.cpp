#include "workerthread.h"

WorkerThread::WorkerThread(QObject *Owner,QObject *parent):QThread(parent),m_worker(Owner)
{

}

void WorkerThread::run()
{
    if(dynamic_cast<VisualizePanel*>(m_worker)){
        (dynamic_cast<VisualizePanel*>(m_worker))->update_all();
    }
    emit resultReady();
}
