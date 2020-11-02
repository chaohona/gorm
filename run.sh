#!/bin/bash

chmod +x bin/killall
./bin/killall /root/github.com/gorm/bin/gorm-server

rm -rf log.txt

nohup /root/github.com/gorm/bin/gorm-server > log.txt 2>&1 &
