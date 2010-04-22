#include "qcrawler_util.h"

#include <sys/time.h>
#include <QDebug>

void debug_record(const QCrawlerRecord &)
{
}

QString md5_hash(const QString &data)
{
    QByteArray bytes = QCryptographicHash::hash (data.toUtf8(), QCryptographicHash::Md5);
    return QString(bytes.toHex());
}

int get_current_time()
{
    struct timeval timer;
    gettimeofday(&timer, NULL);
    return timer.tv_sec;
}



