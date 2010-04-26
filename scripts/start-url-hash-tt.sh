#!/usr/bin/env bash

export TZ=Asia/Shanghai
export LC_ALL='en_US.UTF8'

export LD_LIBRARY_PATH=/opt/qcrawler-thirdparty/lib:$LD_LIBRARY_PATH
export PATH=/opt/qcrawler-thirdparty/bin:$PATH

DATA_DIR=/export/m1/qcrawler/data
LOG_DIR=/export/m1/qcrawler/log

test -d $DATA_DIR || mkdir -p $DATA_DIR
test -d $LOG_DIR || mkdir -p $LOG_DIR

LOG_FILE=$LOG_DIR/qcrawler-url.log

#xmsiz=536870912 512M at least
exec ttserver -port 19860 -thnum 40 -log ${LOG_FILE} -le "${DATA_DIR}/qcrawler-url.tch#bnum=10000000#opts=lb#rcnum=5000#opts=l#xmsiz=536870912"
