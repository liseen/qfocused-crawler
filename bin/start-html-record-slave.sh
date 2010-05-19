#!/usr/bin/env bash

export TZ=Asia/Shanghai
export LC_ALL='en_US.UTF8'

export LD_LIBRARY_PATH=/opt/qcrawler-thirdparty/lib:$LD_LIBRARY_PATH
export PATH=/opt/qcrawler-thirdparty/bin:$PATH

ROOT_DIR=/export/m2
DATA_DIR=$ROOT_DIR/qcrawler-html/data
LOG_DIR=$ROOT_DIR/qcrawler-html/log
ULOG_DIR=$ROOT_DIR/qcrawler-html/ulog

test -d $DATA_DIR || mkdir -p $DATA_DIR
test -d $LOG_DIR || mkdir -p $LOG_DIR
test -d $ULOG_DIR || mkdir -p $ULOG_DIR

LOG_FILE=$LOG_DIR/qcrawler-html.log
RTS_FILE=$DATA_DIR/61.rts

DAEMON="-dmn -pid ${LOG_DIR}/qcrawler-html.pid  -le -log ${LOG_FILE}"

exec ttserver -port 9860 -ulog ${ULOG_DIR} -sid 61 -thnum 32 -mul 16 ${DAEMON} -mport 9860 -mhost 192.168.10.176 -rts ${RTS_FILE} \
    "${DATA_DIR}/qcrawler-html.tch#bnum=100000000#opts=lb#rcnum=5000#xmsiz=536870912"
