#!/usr/bin/env bash

export TZ=Asia/Shanghai
export LC_ALL='en_US.UTF8'

export LD_LIBRARY_PATH=/opt/qcrawler-thirdparty/lib:$LD_LIBRARY_PATH
export PATH=/opt/qcrawler-thirdparty/bin:$PATH


BIN=$(readlink -f -- $(dirname -- "$0"))
cd $BIN/..

LOGFILE=log/qcrawler_record_ttserver.log
DATAFILE=data/qcrawler_record.tct

test -d log || mkdir -p log
test -d data || mkdir -p data

#Table database supports "mode", "bnum", "apow", "fpow", "opts", "rcnum", "lcnum", "ncnum", "xmsiz", "dfunit", and "idx".
exec ttserver -port 1978 -thnum 10 -log "$LOGFILE" -dmn -le "${DATAFILE}#bnum=10000000#opts=lb#rcnum=200"
#ttserver -port 1978 -thnum 10 -le "${DATAFILE}#bnum=100000#opts=lb#rcnum=200"
