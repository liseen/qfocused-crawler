#ifndef QCRAWLER_CENTRAL_QUEUE_H
#define QCRAWLER_CENTRAL_QUEUE_H

#include "url_queue_client.h"

#include "qcrawler_config.h"
#include "qcrawler_url_queue.h"

class QCrawlerCentralQueue : public QCrawlerUrlQueue {
    Q_OBJECT

public:
    QCrawlerCentralQueue() {
        QCrawlerConfig *config = QCrawlerConfig::getInstance();
        QString server = config->url_queue_server();
        client = new UrlQueueClient(server.toStdString());
    }

    ~QCrawlerCentralQueue() {
        delete client;
    }

    virtual void push(const QString &host, const QByteArray &content);
    virtual bool shift(QByteArray *content);
private:
    UrlQueueClient *client;
};

#endif

