#include "qcrawler.h"

void QCrawler::start() {
    while (true) {
        QCrawlerRecord rec;
        get_task->process(true, rec);
    }
}

QCrawler::QCrawler(const std::string &conf_file){

    logger = get_qcrawler_logger("qcrawler");

    // TODO config
    QCrawlerConfig* crawler_config =  QCrawlerConfig::getInstance();
    bool init_ret = crawler_config->init(conf_file);
    if (!init_ret) {
        log_fatal(logger, "init config failed\n");
        fprintf(stderr, "init config failed\n");
        exit(1);
    }

    db = new QCrawlerDB();
    url_queue = new QCrawlerUrlQueue();

    get_task = new QCrawlerGetTask(db, url_queue);
    parser = new QCrawlerKitParser(db, url_queue);
    focus_filter = new QCrawlerFocusFilter(db, url_queue);
    storage_record = new QCrawlerStorageRecord(db, url_queue);

    QObject::connect(get_task, SIGNAL(processFinished(bool, QCrawlerRecord &)),
            parser, SLOT(process(bool, QCrawlerRecord &)));
    QObject::connect(parser, SIGNAL(processFinished(bool, QCrawlerRecord &)),
            focus_filter, SLOT(process(bool, QCrawlerRecord &)));
    QObject::connect(focus_filter, SIGNAL(processFinished(bool, QCrawlerRecord &)),
            storage_record, SLOT(process(bool, QCrawlerRecord &)));
}


