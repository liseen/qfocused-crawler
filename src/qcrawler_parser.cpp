#include "qcrawler_parser.h"


void QCrawlerParser::parse(bool r) {
    qDebug() << "parser\n";
    emit parseFinished(true);
}
