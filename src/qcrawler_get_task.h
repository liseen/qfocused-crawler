#ifndef QCRALER_GET_TASK_H
#define QCRALER_GET_TASK_H

#include <QObject>
#include <QUrl>
#include <QDebug>

#include "qcrawler_common.h"
#include "qcrawler_util.h"
#include "qcrawler_db.h"
#include "qcrawler_config.h"
#include "qcrawler_freq_control.h"
#include "qcrawler_processor.h"

class QCrawlerGetTask : public QCrawlerProcessor
{
    Q_OBJECT

public:
    QCrawlerGetTask(QCrawlerDB * db, QCrawlerUrlQueue *queue, QCrawlerFreqControl *fc) : QCrawlerProcessor(db, queue) {
        logger = get_qcrawler_logger("get_task");

        freq_control = fc;
        //QCralwerConfig *crawler_config = QCrawlerConfig::getInstance();
        // TODO config

    }

public slots:
    virtual void process(bool r, QCrawlerRecord &rec);

private:
    QCrawlerLogger logger;
    QCrawlerFreqControl *freq_control;
};

#endif
