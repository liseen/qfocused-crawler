#ifndef QCRALER_UTIL_H
#define QCRALER_UTIL_H

#include <QDebug>
#include <google/protobuf/text_format.h>

#include "qcrawler_common.h"

void debug_record(const QCrawlerRecord &rec);
QString md5_hash(const QString &data);

int get_current_time();

#endif
