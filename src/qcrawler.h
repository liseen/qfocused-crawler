#ifndef QCRALER_H
#define QCRALER_H

#include <QObject>
#include <QDebug>

#include "qcrawler_common.h"
#include "qcrawler_db.h"
#include "qcrawler_task.h"
#include "qcrawler_parser.h"
#include "qcrawler_processor.h"
#include "qcrawler_focus_filter.h"
/**
 * crawler
 */
class QCrawler : public QObject
{
    Q_OBJECT

public:
    QCrawler() {
        // TODO config
        db = new QCrawlerDB();
        task = new QCrawlerTask(db);

        parser = new QCrawlerParser();
        focus_filter = new QCrawlerFocusFilter(db);

        QObject::connect(task, SIGNAL(urlGetFinished(bool, QCrawlerRecord &)),
                    parser, SLOT(parse(bool, QCrawlerRecord &)));
        QObject::connect(parser, SIGNAL(parseFinished(bool, QCrawlerRecord &)),
                    focus_filter, SLOT(process(bool, QCrawlerRecord &)));
        QObject::connect(focus_filter, SIGNAL(processFinished(bool, QCrawlerRecord &)),
                    db, SLOT(process(bool, QCrawlerRecord &)));
    }

    void start();

private:
    QCrawlerTask* task;
    QCrawlerParser* parser;
    QCrawlerDB* db;
    QCrawlerFocusFilter* focus_filter;
};

#endif
