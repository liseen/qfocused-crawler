#ifndef QCRAWLER_URL_QUEUE_H
#define QCRAWLER_URL_QUEUE_H

#include <QObject>
#include <QDebug>
#include <QQueue>
#include <QMap>

#include "qcrawler_config.h"

class QCrawlerUrlQueue : public QObject {
    Q_OBJECT

public:
    QCrawlerUrlQueue() {
        //QCrawlerConfig *crawler_config = QCrawlerConfig::getInstance();
        // TODO config
        it = host_map.end();
    }

    virtual void push(const std::string &host, const std::string &content);

    virtual bool shift(std::string *str);
private:
    QMap<std::string, QQueue<std::string> > host_map;
    QMap<std::string, QQueue<std::string> >::iterator it;
    QQueue<std::string> queue;
};

#endif
