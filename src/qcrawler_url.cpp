#include "qcrawler_url.h"

#include <QMap>
#include <QVariant>
#include <QMetaObject>
#include <QMetaProperty>
#include <QDataStream>
#include <QDebug>

QCrawlerUrl::QCrawlerUrl(const QCrawlerUrl &other)
{
    const QMetaObject *metaobject = other.metaObject();
    int count = metaobject->propertyCount();
    for (int i = 0; i < count; ++i) {
        QMetaProperty metaproperty = metaobject->property(i);
        const char *name = metaproperty.name();
        QVariant value = other.property(name);
        this->setProperty(name, value);
    }
}

QCrawlerUrl& QCrawlerUrl::operator=(const QCrawlerUrl& other)
{
    const QMetaObject *metaobject = other.metaObject();
    int count = metaobject->propertyCount();
    for (int i = 0; i < count; ++i) {
        QMetaProperty metaproperty = metaobject->property(i);
        const char *name = metaproperty.name();
        QVariant value = other.property(name);
        this->setProperty(name, value);
    }
}

QString QCrawlerUrl::url() const
{
    return m_url.toString(QUrl::StripTrailingSlash);
}

void QCrawlerUrl::set_url(const QString &url)
{
    m_url = QUrl(url);
}

void QCrawlerUrl::set_url(const QUrl &url)
{
    m_url = url;
}


QString QCrawlerUrl::host() const
{
    return m_url.host();
}

QString QCrawlerUrl::path() const
{
    return m_url.path();
}


QString QCrawlerUrl::url_md5() const
{
    return m_url_md5;
}

void QCrawlerUrl::set_url_md5(const QString &url_md5)
{
    m_url_md5 = url_md5;
}

QString QCrawlerUrl::parent_url_md5() const
{
    return m_parent_url_md5;
}

void QCrawlerUrl::set_parent_url_md5(const QString &parent_url_md5)
{
    m_parent_url_md5 = parent_url_md5;
}

QString QCrawlerUrl::anchor_text() const
{
    return m_anchor_text;
}

void QCrawlerUrl::set_anchor_text(const QString &anchor_text)
{
    m_anchor_text = anchor_text;
}

QCrawlerUrl::Status QCrawlerUrl::status() const
{
    return m_status;
}

void QCrawlerUrl::set_status(const QCrawlerUrl::Status &status)
{
    m_status = status;
}

int QCrawlerUrl::failed_times() const
{
    return m_failed_times;
}

void QCrawlerUrl::set_failed_times(int failed_times)
{
    m_failed_times = failed_times;
}

int QCrawlerUrl::crawl_level() const
{
    return m_crawl_level;
}

void QCrawlerUrl::set_crawl_level(int crawl_level)
{
    m_crawl_level = crawl_level;
}



QCrawlerUrl::CrawlType QCrawlerUrl::crawl_type() const
{
    return m_crawl_type;
}

void QCrawlerUrl::set_crawl_type(const QCrawlerUrl::CrawlType &crawl_type)
{
    m_crawl_type = crawl_type;
}

bool QCrawlerUrl::parse_from_bytes(const QByteArray &str)
{
    bool ret = false;
    QMap<QString, QVariant> map;
    QDataStream in(str);
    in >> map;

    QMap<QString, QVariant>::const_iterator it = map.constBegin();
    while (it != map.constEnd()) {
        this->setProperty(it.key().toAscii().constData(), it.value());
        it++;
        ret = true;
    }

    return ret;
}

bool QCrawlerUrl::serialize_to_bytes(QByteArray &bytes)
{
    bool ret = false;
    QDataStream out(&bytes, QIODevice::WriteOnly);
    QMap<QString, QVariant> map;

    const QMetaObject *metaobject = this->metaObject();
    int count = metaobject->propertyCount();
    for (int i = 0; i < count; ++i) {
        QMetaProperty metaproperty = metaobject->property(i);
        const char *name = metaproperty.name();
        QVariant value = this->property(name);
        map.insert(name, value);
        ret = true;
    }
    out << map;

    return ret;
}
