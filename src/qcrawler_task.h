#ifndef QCRALER_TASK_H
#define QCRALER_TASK_H

#include <QObject>
#include <QUrl>
#include <QDebug>

#include "qcrawler_common.h"

class QCrawlerTask : public QObject
{
    Q_OBJECT

public:
    QCrawlerTask() {
        // TODO config
    }

public slots:
    void getUrl();

signals:
    void urlGetFinished(bool, QCrawlerRecord &rec);

private:
    QUrl url;
};

#endif
