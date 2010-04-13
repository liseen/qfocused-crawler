#!/bin/env bash

export TZ=Asia/Shanghai
export LC_ALL='en_US.UTF8'

export LD_LIBRARY_PATH=/opt/qcrawler-thirdparty/lib:$LD_LIBRARY_PATH
export PATH=/opt/qcrawler-thirdparty/bin:$PATH


BIN=$(readlink -f -- $(dirname -- "$0"))
cd $BIN/..

export DISPLAY=:99
exec ./qcrawler
