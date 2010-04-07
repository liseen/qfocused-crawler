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

    std::string user_agent();
    bool quit_on_no_url_found();
    bool enable_js();
    bool auto_load_image();

    std::string url_hash_db_host();
    int url_hash_db_port();

    // cassandra or tt?  default is tt
    std::string record_db_type();
    std::string record_db_host();
    int record_db_port();

    std::string url_queue_host();
    int url_queue_port();
    std::string url_queue_name();

    std::string freq_control_memcached_servers();
    int freq_control_cycle_time();

    bool init(const std::string &conf_file);

private:
    static QCrawlerConfig* config;

    QCrawlerConfig() {}

private:
    QSettings *settings;
};

#endif
