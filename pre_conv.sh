#!/usr/bin/bash

PWD=`pwd`

echo $PWD

chmod +x $PWD/tools/bin/gorm-conv
chmod +x $PWD/tools/bin/protoc

$PWD/tools/bin/gorm-conv  --pb=true --sql=true -I=$PWD/conf/ -O=$PWD/conf/  --protoversion="3" --cpppath=$PWD/src/tables/ --codetype=server
#$PWD/tools/bin/protoc --proto_path=$PWD/conf/  --cpp_out=$PWD/src/tables $PWD/conf/gorm-db.proto $PWD/conf/gorm_pb_tables_inc.proto $PWD/conf/gorm_pb_proto.proto

protoc --proto_path=$PWD/conf/  --cpp_out=$PWD/src/tables $PWD/conf/gorm-db.proto $PWD/conf/gorm_pb_tables_inc.proto $PWD/conf/gorm_pb_proto.proto
