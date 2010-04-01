#!/usr/bin/env bash

export TZ=Asia/Shanghai
export LC_ALL='en_US.UTF8'

BIN=$(readlink -f -- $(dirname -- "$0"))
cd $BIN/..

LOGFILE=log/qcrawler_record_ttserver.log
DATAFILE=data/qcrawler_record.tct

test -d log || mkdir -p log
test -d data || mkdir -p data

#Table database supports "mode", "bnum", "apow", "fpow", "opts", "rcnum", "lcnum", "ncnum", "xmsiz", "dfunit", and "idx".
#ttserver -port 1978 -thnum 10 -log "$LOGFILE" -dmn -le "${DATAFILE}#bnum=100000000#opts=lb#rcnum=200"
ttserver -port 1978 -thnum 10 -le "${DATAFILE}#bnum=100000#opts=lb#rcnum=200"
