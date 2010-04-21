#include "qcrawler_record.h"


QString QCrawlerRecord::raw_html() const
{
    return m_raw_html;
}

void QCrawlerRecord::set_raw_html(const QString &raw_html)
{
    m_raw_html = raw_html;
}

QString QCrawlerRecord::raw_title() const
{
    return m_raw_title;
}

void QCrawlerRecord::set_raw_title(const QString &raw_title)
{
    m_raw_title = raw_title;
}

QString QCrawlerRecord::raw_content() const
{
    return m_raw_content;
}

void QCrawlerRecord::set_raw_content(const QString &raw_content)
{
    m_raw_content = raw_content;
}

QString QCrawlerRecord::raw_content_md5() const
{
    return m_raw_content_md5;
}

void QCrawlerRecord::set_raw_content_md5(const QString &raw_content_md5)
{
    m_raw_content_md5 = raw_content_md5;
}


QString QCrawlerRecord::title() const
{
    return m_title;
}

void QCrawlerRecord::set_title(const QString &title)
{
    m_title = title;
}

QString QCrawlerRecord::content() const
{
    return m_content;
}

void QCrawlerRecord::set_content(const QString &content)
{
    m_content = content;
}


QList<QCrawlerUrl>& QCrawlerRecord::raw_sub_links()
{
    return m_raw_sub_links;
}

QCrawlerUrl& QCrawlerRecord::raw_sub_links(int i)
{
    return m_raw_sub_links[i];
}

QList<QCrawlerUrl>& QCrawlerRecord::focused_links()
{
    return m_focused_links;
}

QCrawlerUrl* QCrawlerRecord::add_raw_sub_links()
{
    QCrawlerUrl crawlerUrl;
    m_raw_sub_links.append(crawlerUrl);
    return &m_raw_sub_links.last();
}

QCrawlerUrl& QCrawlerRecord::focused_links(int i)
{
    return m_focused_links[i];
}

QCrawlerUrl* QCrawlerRecord::add_focused_links()
{
    QCrawlerUrl crawlerUrl;
    m_focused_links.append(crawlerUrl);
    return &m_focused_links.last();
}


const QCrawlerUrl& QCrawlerRecord::crawl_url() const
{
    return m_crawl_url;
}

QCrawlerUrl& QCrawlerRecord::crawl_url()
{
    return m_crawl_url;
}

int QCrawlerRecord::download_time() const
{
    return m_download_time;
}

void QCrawlerRecord::set_download_time(int download_time)
{
    m_download_time = download_time;
}

int QCrawlerRecord::loading_time() const
{
    return m_loading_time;
}

void QCrawlerRecord::set_loading_time(int loading_time)
{
    m_loading_time = loading_time;
}

int QCrawlerRecord::last_modified() const
{
    return m_last_modified;
}

void QCrawlerRecord::set_last_modified(int last_modified)
{
    m_last_modified = last_modified;
}

