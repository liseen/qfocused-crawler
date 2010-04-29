#include "qcrawler_simple_extractor.h"

#include <QStringList>

QString QCrawlerSimpleExtractor::extractTitle(const QString &raw_title)
{
    QRegExp numExp("\\s*\\d+");
    QStringList tl = raw_title.split(QRegExp("\\s*(?:_|-|——|\\|)\\s*"));
    if (tl.size() > 1) {
        int max_len = -1;
        int max_idx = -1;
        for ( int i = 0; i < tl.size(); i++) {
            QString cad_title = tl.at(i);
            cad_title = cad_title.trimmed();
            if (cad_title.size() > max_len && !cad_title.endsWith(QString::fromUtf8("网")) && !numExp.exactMatch(cad_title)) {
                max_len = tl.at(i).size();
                max_idx = i;
            }
        }
        if (max_idx > -1) {
            return tl.at(max_idx);
        }
    } else if (tl.size() == 1) {
        if (tl.at(0).size() > 6) {
            return tl.at(0);
        }
    }

    return raw_title;
}

QString QCrawlerSimpleExtractor::extractMainContent(const QString &raw_content) {
    // blocks
    // best blocks
    // combine
    QString main_content;
    QRegExp reg(QString::fromUtf8("(?:、|，|。|,)"));
    QStringList list = raw_content.split("\n");
    QRegExp noise_reg(QString::fromUtf8("(?:联系我们|版权|Copyright)"));
    int bestIdx = -1;
    int best_size = 20;

    for (int i = 0; i < list.size(); i++) {
        QString block = list.at(i);
        if (block.size() <= 0) {
            continue;
        }
        float punc_ratio = ((float)block.count(reg))/block.size();
        if (punc_ratio < 0.3 && punc_ratio > 0.05 && !block.contains(noise_reg) && block.size() > best_size) {
            bestIdx = i;
            best_size = block.size();
        }
    }

    if (bestIdx == -1) {
        main_content = "";
    } else {
        int base_size = 0.33 * best_size > 15 ? 15 : 0.33 * best_size;
        int max_intervals = 6;
        int min_idx = bestIdx;
        for (int i = bestIdx - 1;  i >= 0; i--) {
            QString block = list.at(i);
            if (block.contains(reg) && !block.contains(noise_reg) && list.at(i).size() > base_size) {
                min_idx = i;
            };
            if (i < min_idx - max_intervals) {
                break;
            }
        }

        int max_idx = bestIdx;
        for (int i = bestIdx + 1; i < list.size(); i++) {
            QString block = list.at(i);
            if (block.contains(reg) && !block.contains(noise_reg) && block.size() > base_size) {
                max_idx = i;
            };
            if (i > max_idx + max_intervals) {
                break;
            }
        }

        max_idx = max_idx + 1;

        for (int i = min_idx; i < max_idx; i++) {
            main_content.append(list.at(i) + "\n");
        }
    }

    return main_content;
}


int QCrawlerSimpleExtractor::process(QCrawlerRecord &rec)
{
    rec.set_title(extractTitle(rec.raw_title()));
    rec.set_content(extractMainContent(rec.raw_content()));
    return 0;
}




