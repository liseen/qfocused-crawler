#include "qcrawler_config.h"

QCrawlerConfig* QCrawlerConfig::config = NULL;

QCrawlerConfig* QCrawlerConfig::getInstance() {
    if (config != NULL) {
        return config;
    } else {
        config = new QCrawlerConfig();
        return config;
    }
}

bool QCrawlerConfig::init(const std::string &conf_file) {
    settings = new QSettings(QString::fromUtf8(conf_file.c_str()), QSettings::IniFormat);
    if (QSettings::NoError == settings->status()) {
        return true;
    }

    return false;
}

std::string QCrawlerConfig::url_hash_db_host() {
    return "localhost";
}

int QCrawlerConfig::url_hash_db_port() {
    return 1979;
}


// cassandra or tt?  default is tt
std::string QCrawlerConfig::record_db_type() {
    return "tt";
}

std::string QCrawlerConfig::record_db_host() {
    return "localhost";
}

int QCrawlerConfig::record_db_port() {
    return 1978;
}


std::string QCrawlerConfig::url_queue_host() {
    return "localhost";
}

int QCrawlerConfig::url_queue_port() {
    return 3380;
}

std::string QCrawlerConfig::url_queue_name() {
    return "urlqueue";
}


