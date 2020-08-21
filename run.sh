#!/bin/bash


./bin/killall /root/gorm/bin/gorm-server

rm -rf log.txt

nohup /root/gorm/bin/gorm-server > log.txt 2>&1 &
