TEMPLATE = app
SOURCES +=\
    ./src/qcrawler_robots.cpp\
    ./src/qcrawler.cpp\
    ./src/main.cpp\
    ./src/qcrawler_webpage.cpp\
    ./src/qcrawler_task.cpp\
    ./src/qcrawler_processor.cpp\
    ./src/qcrawler_parser.cpp\
    ./src/qcrawler_dns_cache.cpp\
    ./src/qcrawler_db.cpp\
    ./src/qcrawler_url.cpp\
    ./src/qcrawler_queue.cpp\
    ./src/qcrawler_focus_filter.cpp\
    ./src/qcrawler_freq_control.cpp

HEADERS +=\
    ./src/qcrawler_webpage.h\
    ./src/qcrawler_freq_control.h\
    ./src/qcrawler_db.h\
    ./src/qcrawler_config.h\
    ./src/qcrawler_task.h\
    ./src/qcrawler_processor.h\
    ./src/qcrawler.h\
    ./src/qcrawler_parser.h\
    ./src/qcrawler_focus_filter.h

QT += network webkit
