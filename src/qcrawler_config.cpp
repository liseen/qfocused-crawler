#include "qcrawler_config.h"

#include <QRegExp>
#include <QStringList>

QCrawlerConfig* QCrawlerConfig::config = NULL;

QCrawlerConfig* QCrawlerConfig::getInstance()
{
    if (config != NULL) {
        return config;
    } else {
        config = new QCrawlerConfig();
        return config;
    }
}

bool QCrawlerConfig::init(const QString &conf_file)
{
    settings = new QSettings(conf_file, QSettings::IniFormat);
    if (QSettings::NoError == settings->status()) {
        return true;
    }

    return false;
}

QString QCrawlerConfig::user_agent()
{
    QString user_agent = settings->value("user_agent").toString();
    if (user_agent.isEmpty()) {
        return "user_agent";
    }
    return user_agent;
}

bool QCrawlerConfig::quit_on_no_url_found()
{
    QString need_quit = settings->value("quit_on_no_url_found").toString();

    //qDebug() << "need quit on url no found: " << need_quit;
    if (need_quit.isEmpty()) {
        return 1;
    }

    return (bool)need_quit.toInt();
}

bool QCrawlerConfig::enable_js()
{
    QString enable_js = settings->value("enable_js").toString();

    if (enable_js.isEmpty()) {
        return 0;
    }
    return (bool)enable_js.toInt();
}

bool QCrawlerConfig::auto_load_image()
{
    QString auto_load = settings->value("auto_load_image").toString();

    if (auto_load.isEmpty()) {
        return 0;
    }
    return (bool)auto_load.toInt();
}

bool QCrawlerConfig::need_freq_control()
{
    QString need = settings->value("need_freq_control").toString();

    if (need.isEmpty()) {
        return true;
    }
    return (bool)need.toInt();
}

bool QCrawlerConfig::enable_central_queue()
{
    QString e = settings->value("enable_central_queue").toString();

    if (e.isEmpty()) {
        return true;
    }
    return (bool)e.toInt();
}

bool QCrawlerConfig::enable_debug()
{
    QString e = settings->value("enable_debug").toString();

    if (e.isEmpty()) {
        return false;
    }
    return (bool)e.toInt();
}

QString QCrawlerConfig::url_hash_db_host() {
    settings->beginGroup("url_hash");
    QString host = settings->value("host").toString();
    settings->endGroup();

    if (host.isEmpty()) {
        return "localhost";
    }
    return host;
}

int QCrawlerConfig::url_hash_db_port() {
    settings->beginGroup("url_hash");
    QString port = settings->value("port").toString();
    settings->endGroup();

    if (port.isEmpty()) {
        return 1979;
    }
    return port.toInt();
}


// cassandra or tt?  default is tt
QString QCrawlerConfig::record_db_type() {
    settings->beginGroup("record_db");
    QString type = settings->value("type").toString();
    settings->endGroup();

    if (type.isEmpty()) {
        return "tt";
    }
    return type;
}

QString QCrawlerConfig::record_db_host() {
    settings->beginGroup("record_db");
    QString host = settings->value("host").toString();
    settings->endGroup();

    if (host.isEmpty()) {
        return "localhost";
    }
    return host;
}

int QCrawlerConfig::record_db_port() {
    settings->beginGroup("record_db");
    QString port = settings->value("port").toString();
    settings->endGroup();

    if (port.isEmpty()) {
        return 1978;
    }
    return port.toInt();
}

QString QCrawlerConfig::url_queue_server() {
    settings->beginGroup("url_queue");
    QString host = settings->value("server").toString();
    settings->endGroup();

    if (host.isEmpty()) {
        return "localhost:19854";
    }
    return host;
}

QString QCrawlerConfig::freq_control_memcached_servers() {
    settings->beginGroup("freq_control");
    QString servers = settings->value("memcached_servers").toString();
    settings->endGroup();

    if (servers.isEmpty()) {
        return "localhost:11211";
    }
    return servers;
}

int QCrawlerConfig::freq_control_cycle_time() {
    settings->beginGroup("freq_control");
    QString cycle_time = settings->value("cycle_time").toString();
    settings->endGroup();

    if (cycle_time.isEmpty()) {
        return 10;
    }
    return cycle_time.toInt();
}

QStringList QCrawlerConfig::focus_filter_bin_extensions()
{
    settings->beginGroup("focus_fitler");
    QString exts = settings->value("bin_extension").toString();
    settings->endGroup();

    if (exts.isEmpty()) {
        return QStringList();
    }
    return exts.split(QRegExp("\\s+"));
}
