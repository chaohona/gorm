@echo off

set pwd=%~dp0



%pwd%/bin/gorm-conv.exe --pb=true --sql=true -I=%pwd%/conf/ -O=%pwd%/conf/ --gopath=%pwd%/src/gorm/gorm --gopackage="gorm/gorm" --protoversion="3"

%pwd%/bin/protoc.exe --proto_path=%pwd%/conf/  --go_out=%pwd%/src %pwd%/conf/gorm-db.proto %pwd%/conf/gorm_pb_tables_inc.proto %pwd%/conf/gorm_pb_proto.proto --experimental_allow_proto3_optional

:exit