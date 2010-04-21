#ifndef QCRAWLER_URL_H
#define QCRAWLER_URL_H

#include <QObject>
#include <QString>
#include <QCryptographicHash>
#include <QUrl>

class QCrawlerUrl : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl url READ url WRITE set_url)
    Q_PROPERTY(Status status READ status WRITE set_status)
    Q_PROPERTY(QString url_md5 READ url_md5 WRITE set_url_md5)
    Q_PROPERTY(QString parent_url_md5 READ parent_url_md5 WRITE set_parent_url_md5)
    Q_PROPERTY(QString anchor_text READ anchor_text WRITE set_anchor_text)
    Q_PROPERTY(int failed_times READ failed_times WRITE set_failed_times)
    Q_PROPERTY(int crawl_level READ crawl_level WRITE set_crawl_level)
    Q_PROPERTY(CrawlType crawl_type READ crawl_type WRITE set_crawl_type)
    Q_ENUMS(Status)
    Q_ENUMS(CrawlType)

public:
    QCrawlerUrl() {}
    ~QCrawlerUrl() {}

    enum Status {
        NOT_EXIST = 100,
        NOT_CRAWLED = 0,
        CRAWLED_OK = 1,

        NOT_NEED_CRAWL = 10,

        FAILED_CRAWL_1 = -1,
        FAILED_CRAWL_2 = -2,
        FAILED_CRAWL_3 = -3,
        FAILED_CRAWL_4 = -4,
        FAILED_CRAWL_5 = -5
    };

    enum CrawlType {
       HOST_RESTRICTED,
       UPDATE
    };

    QCrawlerUrl(const QCrawlerUrl&);
    QCrawlerUrl& operator=(const QCrawlerUrl&);

    QString url() const;
    void set_url(const QString &url);
    void set_url(const QUrl &url);
    QString host() const;
    QString path() const;
    QString url_md5() const;
    void set_url_md5(const QString &url_md5);
    QString parent_url_md5() const;
    void set_parent_url_md5(const QString &parent_url_md5);
    QString anchor_text() const;
    void set_anchor_text(const QString &anchor_text);
    Status status() const;
    void set_status(const Status &status);
    int failed_times() const;
    void set_failed_times( int failed_times);
    int crawl_level() const;
    void set_crawl_level( int crawl_level);
    CrawlType crawl_type() const;
    void set_crawl_type(const CrawlType &crawl_type);

    bool parse_from_bytes(const QByteArray &str);
    bool serialize_to_bytes(QByteArray &str);

private:
    QUrl m_url;
    Status m_status;
    QString m_url_md5;
    QString m_parent_url_md5;
    QString m_anchor_text;
    int m_failed_times;
    int m_crawl_level;
    CrawlType m_crawl_type;
};

#endif
