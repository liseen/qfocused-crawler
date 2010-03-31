#include <QObject>
#include <QUrl>
#include <QDebug>

class QCrawlerTask : public QObject
{
    Q_OBJECT

public:
    QCrawlerTask() {
        // TODO config
    }

public slots:
    void getUrl();

signals:
    void urlGetFinished(bool);

private:
    QUrl url;
};


