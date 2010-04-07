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

std::string QCrawlerConfig::user_agent() {
    QString user_agent = settings->value("user_agent").toString();
    if (user_agent.isEmpty()) {
        return "user_agent";
    }
    return user_agent.toUtf8().constData();
}

bool QCrawlerConfig::quit_on_no_url_found() {
    QString need_quit = settings->value("quit_on_on_url_found").toString();

    qDebug() << "need quit on url no found: " << need_quit;
    if (need_quit.isEmpty()) {
        return 1;
    }

    return (bool)need_quit.toInt();
}

bool QCrawlerConfig::enable_js() {
    QString enable_js = settings->value("enable_js").toString();

    if (enable_js.isEmpty()) {
        return 0;
    }
    return (bool)enable_js.toInt();
}

bool QCrawlerConfig::auto_load_image() {
    QString auto_load = settings->value("auto_load_image").toString();

    if (auto_load.isEmpty()) {
        return 0;
    }
    return (bool)auto_load.toInt();
}

std::string QCrawlerConfig::url_hash_db_host() {
    settings->beginGroup("url_hash");
    QString host = settings->value("host").toString();
    settings->endGroup();

    if (host.isEmpty()) {
        return "localhost";
    }
    return host.toUtf8().constData();
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
std::string QCrawlerConfig::record_db_type() {
    settings->beginGroup("record_db");
    QString type = settings->value("type").toString();
    settings->endGroup();

    if (type.isEmpty()) {
        return "tt";
    }
    return type.toUtf8().constData();
}

std::string QCrawlerConfig::record_db_host() {
    settings->beginGroup("record_db");
    QString host = settings->value("host").toString();
    settings->endGroup();

    if (host.isEmpty()) {
        return "localhost";
    }
    return host.toUtf8().constData();
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

std::string QCrawlerConfig::url_queue_host() {
    settings->beginGroup("url_queue");
    QString host = settings->value("host").toString();
    settings->endGroup();

    if (host.isEmpty()) {
        return "localhost";
    }
    return host.toUtf8().constData();
}

int QCrawlerConfig::url_queue_port() {
    settings->beginGroup("url_queue");
    QString port = settings->value("port").toString();
    settings->endGroup();

    if (port.isEmpty()) {
        return 3380;
    }
    return port.toInt();
}

std::string QCrawlerConfig::url_queue_name() {
    settings->beginGroup("url_queue");
    QString name = settings->value("name").toString();
    settings->endGroup();

    if (name.isEmpty()) {
        return "urlqueue";
    }
    return name.toUtf8().constData();
}


std::string QCrawlerConfig::freq_control_memcached_servers() {
    settings->beginGroup("freq_control");
    QString servers = settings->value("memcached_servers").toString();
    settings->endGroup();

    if (servers.isEmpty()) {
        return "localhost:11211";
    }
    return servers.toUtf8().constData();
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

