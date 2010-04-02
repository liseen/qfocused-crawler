#ifndef QCRALER_CONFIG_H
#define QCRALER_CONFIG_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QSettings>

class QCrawlerConfig;

class QCrawlerConfig
{
public:

    static QCrawlerConfig* getInstance();

    //std::string log_path();
    // TRACE, DEBUG, INFO, WARN, ERROR and FATAL
    //std::string log_level();

    std::string url_hash_db_host();
    int url_hash_db_port();

    // cassandra or tt?  default is tt
    std::string record_db_type();
    std::string record_db_host();
    int record_db_port();

    std::string url_queue_host();
    int url_queue_port();

    std::string url_queue_name();

    bool init(const std::string &conf_file);

private:
    static QCrawlerConfig* config;

    QCrawlerConfig() {}

private:
    QSettings *settings;
};

#endif
