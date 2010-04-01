#include "qcrawler_processor.h"


void QCrawlerProcessor::process(bool r, QCrawlerRecord &rec) {
     emit processFinished(r, rec);
}
