#include "qcrawler_central_queue.h"



void QCrawlerCentralQueue::push(const QString &host, const QByteArray &content)
{
    QByteArray host_bytes = host.toUtf8();
    std::string host_str(host_bytes.constData(), host_bytes.size());
    std::string content_str(content.constData(), content.size());
    client->push(host_str, content_str);
}

bool QCrawlerCentralQueue::shift(QByteArray *content)
{
    std::string str;
    bool r = client->shift(&str);
    if (r) {
        content->append(str.c_str(), str.size());
    }

    return r;
}

