#include "qcrawler_task.h"


void QCrawlerTask::getNextUrl() {
    while (true) {
        url = QUrl("http://www.qunar.com");
        emit urlGetFinished(true);
    }
}
