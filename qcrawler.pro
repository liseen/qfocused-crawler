TEMPLATE = app
SOURCES +=\
    src/qcrawler_robots.cpp\
    src/qcrawler.cpp\
    src/main.cpp\
    src/qcrawler_get_task.cpp\
    src/qcrawler_webpage.cpp\
    src/qcrawler_kit_parser.cpp\
    src/qcrawler_common.cpp\
    src/qcrawler_util.cpp\
    src/qcrawler_processor.cpp\
    src/qcrawler_db.cpp\
    src/qcrawler_url_queue.cpp\
    src/qcrawler_storage_record.cpp\
    src/qcrawler_focus_filter.cpp\
    src/qcrawler_config.cpp\
    src/qcrawler_freq_control.cpp\
    ./src/qcrawler_record.pb.cc

HEADERS +=\
    src/qcrawler_storage_record.h\
    src/qcrawler_util.h\
    src/qcrawler_webpage.h\
    src/qcrawler_freq_control.h\
    src/qcrawler_db.h\
    src/qcrawler_url_queue.h\
    src/qcrawler_config.h\
    src/qcrawler_processor.h\
    src/qcrawler_kit_parser.h\
    src/qcrawler_get_task.h\
    src/qcrawler.h\
    src/qcrawler_eventloop.h\
    src/qcrawler_record.pb.h\
    src/qcrawler_focus_filter.h\
    src/qcrawler_common.h

LIBS = -lprotobuf -L/usr/local/lib -ltokyotyrant -ltokyocabinet -lz -lbz2 -lresolv -lnsl -ldl -lrt -lpthread -lm -lc -llog4cxx -lmemcached
QT += network webkit testlib
