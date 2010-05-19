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

    //QString log_path();
    // TRACE, DEBUG, INFO, WARN, ERROR and FATAL
    //QString log_level();

    QString user_agent();
    bool quit_on_no_url_found();
    bool enable_js();
    bool auto_load_image();
    bool need_freq_control();
    bool enable_central_queue();
    bool enable_debug();

    QString url_hash_db_host();
    int url_hash_db_port();

    // cassandra or tt?  default is tt
    QString record_db_type();
    QString record_db_host();
    int record_db_port();

    QString html_record_db_host();
    int html_record_db_port();


    QString url_queue_server();

    QString freq_control_memcached_servers();
    int freq_control_cycle_time();

    QStringList focus_filter_bin_extensions();

    bool init(const QString &conf_file);

private:
    static QCrawlerConfig* config;

    QCrawlerConfig() {}

private:
    QSettings *settings;
};

#endif
