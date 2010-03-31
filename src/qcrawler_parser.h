#ifndef QCRALER_PARSER
#define QCRALER_PARSER
#include <QObject>
#include <QDebug>

#include "qcrawler_common.h"
#include "qcrawler_webpage.h"

class QCrawlerParser : public QObject
{
    Q_OBJECT

public:
    QCrawlerParser() {
        // TODO config
        page = new QCrawlerPage();
    }

    ~QCrawlerParser() {
        delete page;
    }

public slots:
    void parse(bool r, QCrawlerRecord &rec);

signals:
    void parseFinished(bool, QCrawlerRecord &);

private:
    QCrawlerPage* page;
};

#endif
