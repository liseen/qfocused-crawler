#ifndef QCRAWLER_URL_QUEUE_H
#define QCRAWLER_URL_QUEUE_H

#include <QObject>
#include <QDebug>
#include <QQueue>
#include <QMap>
#include <QByteArray>

#include "qcrawler_config.h"

class QCrawlerUrlQueue : public QObject {
    Q_OBJECT

public:
    QCrawlerUrlQueue() {
        it = host_map.end();
    }

    virtual void push(const QString &host, const QByteArray &content);
    virtual bool shift(QByteArray *content);
private:
    QMap< QString, QQueue<QByteArray> > host_map;
    QMap< QString, QQueue<QByteArray> >::iterator it;
    QMap< QString, QQueue<QByteArray> >::iterator last_it;
    QQueue<QString> queue;
};

#endif
