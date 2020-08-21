#!/bin/bash

source gorm.env

if [ -z "${GORM_HOME}" ];then
    echo "GORM_HOME is null,please source gorm.env first"
    exit
fi

if [ -z "${PROTOBUF_HOME}" ];then
    echo "PROTOBUF_HOME is null,please source gorm.env first"
    exit
fi

mkdir -p ${GORM_HOME}/example/gorm-example-insert/src/
chmod +x ${GORM_HOME}/tools/gorm-conv

cp ${GORM_HOME}/proto/gorm_pb_proto.proto ${GORM_HOME}/example/gorm-example-insert/conf/

#将表定义文件通过protoc转换为h和cc文件
${GORM_HOME}/tools/gorm-conv -I=${GORM_HOME}/example/gorm-example-insert/conf/ -O=${GORM_HOME}/example/gorm-example-insert/conf/ -pb=true --cpppath=${GORM_HOME}/example/gorm-example-insert/src/
${PROTOBUF_HOME}/protoc --proto_path=${GORM_HOME}/example/gorm-example-insert/conf/  --cpp_out=${GORM_HOME}/example/gorm-example-insert/src/ gorm-db.proto gorm_pb_tables_inc.proto gorm_pb_proto.proto
