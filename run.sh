#!/bin/bash

chmod +x bin/killall
./bin/killall /root/github.com/async/gorm/bin/gorm-server


nohup /root/github.com/async/gorm/bin/gorm-server > log.txt 2>&1 &
