#include "qcrawler.h"

#include <QDateTime>

void QCrawler::start() {
    int proc_size = processors.size();
    while (true) {
        QCrawlerRecord rec;

        int task_ret = get_task->process(rec);

        if (task_ret == 0) {
            for (int i = 0; i < proc_size; i++) {
                int ret = processors[i]->process(rec);
                qDebug() << QDateTime::currentDateTime().toString("yyyy-dd-mm hh:mm:ss")
                        << processors[i]->objectName() << "url: " << rec.crawl_url().url() << " ret: " << ret;
                if (ret > 0) {
                // log
                    break;
                } else if (ret < 0) {
                    // log
                    exit(1);
                }
            }
        } else if (task_ret > 0) {
            // none op
        } else {
            exit(1);
        }
    }
}

QCrawler::QCrawler(){

    db = new QCrawlerDB();

    if (QCrawlerConfig::getInstance()->enable_central_queue()) {

        url_queue = new QCrawlerCentralQueue();
    } else {
        url_queue = new QCrawlerUrlQueue();
    }

    freq_control = new QCrawlerFreqControl();

    get_task = new QCrawlerGetTask(db, url_queue, freq_control);
    get_task->setObjectName("task");

    parser = new QCrawlerKitParser(db, url_queue);
    parser->setObjectName("parser");
    processors.append(parser);


    focus_filter = new QCrawlerFocusFilter(db, url_queue);
    focus_filter->setObjectName("filter");
    processors.append(focus_filter);

    simple_extractor = new QCrawlerSimpleExtractor(db, url_queue);
    simple_extractor->setObjectName("extractor");
    processors.append(simple_extractor);

    storage_record = new QCrawlerStorageRecord(db, url_queue);
    storage_record->setObjectName("storage");
    processors.append(storage_record);
}

QCrawler::~QCrawler()
{
    int proc_size = processors.size();
    for (int i = 0; i < proc_size; i++) {
        delete processors[i];
    }
}
