#include <QObject>
#include <QDebug>

/**
 * crawler
 */
class QCrawler : public QObject
{
    Q_OBJECT

public:
    QCrawler() {
        // TODO config
    }

signals:
    void startCrawler();
};
