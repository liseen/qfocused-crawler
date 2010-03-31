#include "qcrawler_task.h"


void QCrawlerTask::getUrl() {
    url = QUrl("http://www.qunar.com");
    emit urlGetFinished(true);
}
