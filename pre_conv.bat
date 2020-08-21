@echo off

set pwd=%~dp0

::
%pwd%/tools/bin/gorm-conv.exe -I=%pwd%/conf/ -O=%pwd%/conf/ --pb=true --sql=true --cpppath=%pwd%/src/tables/ --codetype=server
::%pwd%/tools/gorm-conv/bin/gorm-conv.exe -I=%pwd%/conf/ -O=%pwd%/conf/ -fb=true -pb=true
::%pwd%/tools/bin/flatc.exe --cpp -o %pwd%/src/tables %pwd%/conf/gorm-db.fbs
::%pwd%/tools/bin/protoc.exe --proto_path=%pwd%/conf/  --cpp_out=%pwd%/src/tables %pwd%/conf/gorm-db.proto %pwd%/conf/gorm_pb_tables_inc.proto %pwd%/conf/gorm_pb_proto.proto

:exit