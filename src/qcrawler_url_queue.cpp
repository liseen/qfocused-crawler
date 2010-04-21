#include "qcrawler_url_queue.h"

void QCrawlerUrlQueue::push(const QString &host, const QByteArray &content)
{
    if (host_map.contains(host)) {
        host_map[host].enqueue(content);
    } else {
        QQueue<QByteArray> q;
        q.enqueue(content);
        host_map.insert(host, q);
    }
}

bool QCrawlerUrlQueue::shift(QByteArray *content) {
    if (host_map.size() < 1) {
        return false;
    }

    bool r = false;
    last_it = it;
    do {
        if (it == host_map.end()) {
            it = host_map.begin();
        } else {
            it++;
        }

        if (it != host_map.end()) {
            if (! it.value().isEmpty()) {
                *content = it.value().dequeue();
                r = true;
                break;
            }
        }
    } while (it != last_it);

    return r;
}


