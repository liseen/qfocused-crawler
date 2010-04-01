#ifndef QCRALER_PROCESSOR_H
#define QCRALER_PROCESSOR_H

#include <QObject>
#include <QDebug>

#include "qcrawler_common.h"

class QCrawlerProcessor : public QObject
{
    Q_OBJECT

public:
    QCrawlerProcessor() {
        // TODO config
    }

public slots:
    virtual void process(bool r, QCrawlerRecord &rec);

signals:
    void processFinished(bool, QCrawlerRecord &rec);
};

#endif
