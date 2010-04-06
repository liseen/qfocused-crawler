#!/usr/bin/env bash

export TZ=Asia/Shanghai
export LC_ALL='en_US.UTF8'

BIN=$(readlink -f -- $(dirname -- "$0"))
cd $BIN/..

#memcached -d -p 11211 -m1024
memcached -vv -p 11211 -m10
