#ifndef QCRALER_H
#define QCRALER_H

#include <QObject>
#include <QDebug>

#include "qcrawler_common.h"
#include "qcrawler_util.h"
#include "qcrawler_config.h"
#include "qcrawler_db.h"
#include "qcrawler_freq_control.h"
#include "qcrawler_get_task.h"
#include "qcrawler_kit_parser.h"
#include "qcrawler_processor.h"
#include "qcrawler_focus_filter.h"
#include "qcrawler_storage_record.h"
#include "qcrawler_central_queue.h"
#include "qcrawler_simple_extractor.h"

/**
 * crawler
 */

class QCrawler : public QObject
{
    Q_OBJECT

public:
    QCrawler();
    ~QCrawler();

    void start();

private:
    QCrawlerDB* db;
    QCrawlerUrlQueue *url_queue;
    QCrawlerFreqControl *freq_control;

    QCrawlerGetTask* get_task;
    QCrawlerKitParser* parser;
    QCrawlerFocusFilter* focus_filter;
    QCrawlerStorageRecord* storage_record;

    QCrawlerSimpleExtractor* simple_extractor;

    QVector<QCrawlerProcessor*> processors;
};

#endif
