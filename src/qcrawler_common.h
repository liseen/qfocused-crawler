#ifndef QCRAWLER_COMMON_H
#define QCRAWLER_COMMON_H

#include "qcrawler_record.h"

#define MAX_CRAWL_LEVEL 10000
#define MAX_URL_LENGTH 512
#define QCRAWLER_VERSION 0.0.2
/*
#include "log4cxx/logger.h"
#include "log4cxx/basicconfigurator.h"
#include "log4cxx/propertyconfigurator.h"
#include "log4cxx/helpers/exception.h"
#include <log4cxx/fileappender.h>
#include <log4cxx/simplelayout.h>

#define log_trace LOG4CXX_TRACE
#define log_debug LOG4CXX_DEBUG
#define log_info  LOG4CXX_INFO
#define log_warn  LOG4CXX_WARN
#define log_error LOG4CXX_ERROR
#define log_fatal LOG4CXX_FATAL

#define QCrawlerLogger log4cxx::LoggerPtr
#define get_qcrawler_logger(x) log4cxx::Logger::getLogger(x)

void  GLOBAL_INIT_LOGGER(const std::string &file_name);
*/
#endif
