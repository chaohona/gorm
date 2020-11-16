#!/bin/bash

chmod +x bin/killall
./bin/killall /root/github.com/gorm/bin/gorm-server

now=`date '+%Y%m%d%H%M%S'`

mv log.txt log.txt.$(now)

nohup /root/github.com/gorm/bin/gorm-server > log.txt 2>&1 &
