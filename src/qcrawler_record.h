#ifndef QCRAWLER_RECORD_H
#define QCRAWLER_RECORD_H

#include <QList>
#include <QString>

#include "qcrawler_url.h"

class QCrawlerRecord : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString raw_html READ raw_html WRITE set_raw_html)
    Q_PROPERTY(QString raw_title READ raw_title WRITE set_raw_title)
    Q_PROPERTY(QString raw_content READ raw_content WRITE set_raw_content)
    Q_PROPERTY(QString raw_content_md5 READ raw_content_md5 WRITE set_raw_content_md5)
    Q_PROPERTY(QString content READ content WRITE set_content)
    Q_PROPERTY(QString title READ title WRITE set_title)
    Q_PROPERTY(int download_time READ download_time WRITE set_download_time)
    Q_PROPERTY(int loading_time READ loading_time WRITE set_loading_time)
    Q_PROPERTY(int last_modified READ last_modified WRITE set_last_modified)

public:
    QCrawlerRecord() {
        m_download_time = 0;
        m_loading_time = 0;
        m_last_modified = 0;
    }

    ~QCrawlerRecord() {}

    QString raw_html() const;
    void set_raw_html(const QString &raw_html);
    QString raw_title() const;
    void set_raw_title(const QString &f);
    QString raw_content() const;
    void set_raw_content(const QString &raw_content);
    QString raw_content_md5() const;
    void set_raw_content_md5(const QString &raw_content_md5);
    QString title() const;
    void set_title(const QString &title);
    QString content() const;
    void set_content(const QString &content);
    int download_time() const;
    void set_download_time(int download_time);
    int loading_time() const;
    void set_loading_time(int loading_time);
    int last_modified() const;
    void set_last_modified(int last_modified);

    const QCrawlerUrl& crawl_url() const;
    QCrawlerUrl& crawl_url();
    QList<QCrawlerUrl>& raw_sub_links();
    QCrawlerUrl& raw_sub_links(int i);
    QCrawlerUrl* add_raw_sub_links();
    QList<QCrawlerUrl>& focused_links();
    QCrawlerUrl& focused_links(int i);
    QCrawlerUrl* add_focused_links();

private:
    QString m_raw_html;
    QString m_raw_title;
    QString m_raw_content;
    QString m_raw_content_md5;
    QString m_title;
    QString m_content;

    int m_download_time;
    int m_loading_time;
    int m_last_modified;

    QCrawlerUrl m_crawl_url;
    QList<QCrawlerUrl> m_raw_sub_links;
    QList<QCrawlerUrl> m_focused_links;
};

#endif
