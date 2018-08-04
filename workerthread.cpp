#include "workerthread.h"

WorkerThread::WorkerThread(QObject *Owner,QObject *parent):QThread(parent),m_worker(Owner)
{

}

void WorkerThread::run()
{

}
