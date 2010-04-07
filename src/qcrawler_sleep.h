#ifndef QCRAWLER_SLEEP_H
#define QCRAWLER_SLEEP_H

#include <QThread>

class QCrawlerSleep : public QThread
{
public:
    static void sleep(unsigned long secs) {
        QThread::sleep(secs);
    }

};


#endif
