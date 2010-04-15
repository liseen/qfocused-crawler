#!/bin/sh

export TZ=Asia/Shanghai
export LC_ALL='en_US.UTF8'

BIN=$(readlink -f -- $(dirname -- "$0"))
cd $BIN/..

#ulimit -v $(( 2048 * 1024 ))
#ulimit -t 1800

exec Xvfb :99 -auth scripts/Xauth.conf -shmem -dpi 96 -nolisten tcp -screen 1 1280x1024x8 2>/dev/null &
