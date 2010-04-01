#ifndef QCRALER_TASK_H
#define QCRALER_TASK_H

#include <QObject>
#include <QUrl>
#include <QDebug>

#include "qcrawler_common.h"
#include "qcrawler_util.h"
#include "qcrawler_db.h"

class QCrawlerTask : public QObject
{
    Q_OBJECT

public:
    QCrawlerTask(QCrawlerDB* qc_db) {
        // TODO config

        qcrawler_db = qc_db;
    }

public slots:
    void getUrl();

signals:
    void urlGetFinished(bool, QCrawlerRecord &rec);

private:
    QCrawlerDB *qcrawler_db;
};

#endif
