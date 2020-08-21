#gorm makefile
PWD=$(shell pwd)
THIRD_PATH=$(PWD)/src/thirdparty/
LIB_PATH=$(PWD)/lib/linux/

COMMON_INC=-I$(PWD)/src/common/
SERVER_INC=-I$(PWD)/src/server/
TABLE_INC=-I$(PWD)/src/tables/
CLIENT_INC=-I$(PWD)/src/client/
TABLE_SVR_INC=-I$(PWD)/src/tables/server
MYSQL_INC=-I$(THIRD_PATH)/mysql-connector/
YAML_INC=-I$(THIRD_PATH)/yaml/include/

TEST_INC=-I$(PWD)/src/test/
INC=$(COMMON_INC) -I$(THIRD_PATH) $(TABLE_INC)  $(CLIENT_INC)  $(TABLE_SVR_INC) $(SERVER_INC)

GORM_SERVER_INC=$(SERVER_INC) $(INC) $(SERVER_INC) $(TABLE_SVR_INC) $(YAML_INC) $(MYSQL_INC)

PROTO_LIB=-lprotobuf -lprotobuf-lite
#LIB=-L$(LIB_PATH)/protobuf/ /root/gorm/lib/mysql-connector/libmysqlclient.a $(PROTO_LIB) -L$(LIB_PATH)/yaml/ -lyaml-cpp -lpthread  -lm -lrt -lssl -lcrypto -ldl
LIB=-lmysqlclient $(PROTO_LIB) -lpthread

SHARE_LIB=-lmysqlclient $(PROTO_LIB) -lpthread  -lm -lrt -lssl -lcrypto -ldl

CXX=g++
DEBUG=-g -ggdb -rdynamic -DGORM_DEBUG=1
CXXFLAGS=-std=c++11 -lstdc++ $(DEBUG) $(INC) -fPIC
SVRCXXFLAGS=-std=c++11 -lstdc++ $(DEBUG) $(GORM_SERVER_INC) -fPIC
DEBUG_FLAGS=-DGORM_DEBUG=1 $(SVRCXXFLAGS) 
DEPS=$(LIB)

GORM_SERVER_DEBUG=$(PWD)/bin/gorm-serverd

GORMServer=$(PWD)/bin/gorm-server
GORMClient=$(PWD)/bin/gorm-client
GORMProxy=$(PWD)/bin/gorm-proxy
SHAREClient=$(PWD)/lib/gorm/libgorm-client.so
STATICClient=$(PWD)/lib/gorm/libgorm-client.a
SHARETABLES=$(PWD)/lib/gorm/libgorm-tables.so
STATICTABLES=$(PWD)/lib/gorm/libgorm-tables.a
GORM_SVR_SRC=$(wildcard $(PWD)/src/server/*.cc)
GORM_SVR_OBJ=$(GORM_SVR_SRC:%.cc=%.o)
GORM_SVR_INC_SRC=$(wildcard $(PWD)/src/server/*.h)
COMMON_SRC=$(wildcard $(PWD)/src/common/*.cc)
COMMON_INC_SRC=$(wildcard $(PWD)/src/common/*.h)
COMMON_OBJ=$(COMMON_SRC:%.cc=%.o)
TABLES_INC_SRC=$(wildcard $(PWD)/src/tables/*.h)
TABLES_SRC=$(wildcard $(PWD)/src/tables/*.cc)
TABLES_OBJ=$(TABLES_SRC:%.cc=%.o)
TABLES_SVR_SRC=$(wildcard $(PWD)/src/tables/server/*.cc)
TABLES_SVR_OBJ=$(TABLES_SVR_SRC:%.cc=%.o)
PROXY_SRC=$(wildcard $(PWD)/src/proxy/*.cc)
PROXY_OBJ=$(PROXY_SRC:%.cc=%.o)
GORM_CLIENT_SRC=$(wildcard $(PWD)/src/client/*.cc)
GORM_CLIENT_OBJ=$(GORM_CLIENT_SRC:%.cc=%.o)
GORM_CLIENT_INC=$(wildcard $(PWD)/src/client/*.h)


ASYNC_TEST=$(PWD)/bin/async-test
ASYNC_TEST_SRC=$(wildcard $(PWD)/src/test/*.cc)
ASYNC_TEST_OBJ=$(ASYNC_TEST_SRC:%.cc=%.o)

SHARE_TABLES_OBJ=$(TABLES_SRC:%.cc=%.o)

#test: /root/gorm/src/test/test.pb.h
#	@echo $(ASYNC_TEST)
#	@echo $(ASYNC_TEST_OBJ)

# 编译服务器需要的库
SERVER_LIBS=$(LIB_PATH)/redis/libhiredis.a -L$(LIB_PATH)/yaml/ -lyaml-cpp

DEBUG_FLAGS=$(SVRCXXFLAGS) -DGORM_DEBUG=1
$(GORM_SERVER_DEBUG) : $(SHAREClient) $(COMMON_OBJ) $(TABLES_OBJ) $(GORM_SVR_OBJ) $(TABLES_SVR_OBJ)
	$(CXX) $(DEBUG_FLAGS) -o $@ $^ $(DEPS) $(SERVER_LIBS) -L$(PWD)/lib/gorm -lgorm-client -lgorm-tables

$(GORMServer) : $(SHAREClient) $(COMMON_OBJ) $(TABLES_OBJ) $(GORM_SVR_OBJ) $(TABLES_SVR_OBJ)
	$(CXX) $(SVRCXXFLAGS) -o $@ $^ $(DEPS) $(SERVER_LIBS) -L$(PWD)/lib/gorm -lgorm-client -lgorm-tables
	if [ "$$?" != "0" ]; then\
		echo "make $(GORMServer) failed...";\
	else\
		echo "make $(GORMServer) success...";\
	fi;
	
$(GORMProxy) : $(PROXY_OBJ) $(COMMON_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(DEPS)  $(SERVER_LIBS) -L$(PWD)/lib/gorm -lgorm-tables

$(STATICTABLES) : $(TABLES_OBJ)
	ar rcs $(STATICTABLES) $(TABLES_OBJ)
$(SHARETABLES) : $(TABLES_OBJ)
	$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(SHARE_LIB)
$(STATICClient) : $(COMMON_OBJ) $(GORM_CLIENT_OBJ)
	ar rcs $(STATICClient) $(COMMON_OBJ) $(GORM_CLIENT_OBJ)
$(SHAREClient) : $(COMMON_OBJ) $(GORM_CLIENT_OBJ)
	$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(SHARE_LIB)
$(GORMClient) : $(COMMON_OBJ) $(GORM_CLIENT_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIB) -L$(PWD)/lib/gorm -lgorm-client

server: prepare $(GORMServer)

debug_server: $(GORM_SERVER_DEBUG)

proxy: prepare $(GORMProxy)

client: $(GORMClient)
	@echo "make client"

lib: $(STATICClient) $(SHAREClient) $(STATICTABLES) $(SHARETABLES) pack_inc
	@echo "make client"

test: $(ASYNC_TEST) $(COMMON_SRC)
	@echo $(ASYNC_TEST)

$(ASYNC_TEST) : $(ASYNC_TEST_SRC)
	@echo $(ASYNC_TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(INC)

prepare:
	if [ ! -d $(PWD)/bin ]; then mkdir -p $(PWD)/bin; fi;

pack_inc:
	rm -rf $(PWD)/include
	mkdir -p $(PWD)/include
	cp -rf $(PWD)/src/client/*h $(PWD)/include/
	cp -rf $(PWD)/src/common/*h $(PWD)/include/
	cp -rf $(PWD)/src/tables/gorm_msg_helper.h $(PWD)/include/
	cp -rf $(PWD)/src/tables/gorm_pb_proto.pb.h $(PWD)/include/
	cp -rf $(PWD)/src/tables/gorm_table_field_map.h $(PWD)/include/
	cp -rf $(PWD)/src/tables/gorm_table_field_map_define.h $(PWD)/include/
	cp -rf $(PWD)/src/tables/gorm_record.h $(PWD)/include/

all: lib server pack_inc
	
release: all
	rm -rf release
	mkdir -p $(PWD)/release
	mkdir -p $(PWD)/release/conf
	mkdir -p $(PWD)/release/tools
	mkdir -p $(PWD)/release/proto
	mkdir -p $(PWD)/release/bin
	mkdir -p $(PWD)/release/lib
	mkdir -p $(PWD)/release/src/tables
	cp -rf $(PWD)/src/thirdparty $(PWD)/release
	cp -rf $(PWD)/include $(PWD)/release
	cp -rf $(PWD)/example $(PWD)/release
	cp -rf $(PWD)/tools/bin/gorm-conv $(PWD)/release/tools
	cp -rf $(PWD)/conf/gorm-server.yml $(PWD)/release/conf/gorm-server.yml.example
	cp -rf $(PWD)/conf/gorm-db.yml $(PWD)/release/conf/gorm-db.yml.example
	cp -rf $(PWD)/bin/gorm-server $(PWD)/release/bin/
	cp -rf $(PWD)/lib/gorm $(PWD)/release/lib/
	cp -rf $(PWD)/lib/linux/yaml $(PWD)/release/lib/
	cp -rf $(PWD)/lib/linux/mysql-connector $(PWD)/release/lib/
	cp -rf $(PWD)/conf/gorm_pb_proto.proto $(PWD)/release/proto/
	cp -rf $(PWD)/run.sh $(PWD)/release/run.sh.example
	cp -rf $(PWD)/readme.md $(PWD)/release/readme.md
	cp -rf $(PWD)/src/tables/gorm_msg_helper.cc $(PWD)/release/src/tables
	#cp -rf $(PWD)/src/tables/gorm_pb_proto.pb.cc $(PWD)/release/src/tables
	cp -rf $(PWD)/src/tables/gorm_table_field_map.cc $(PWD)/release/src/tables
	cp -rf $(PWD)/src/tables/gorm_record.cc $(PWD)/release/src/tables
	git show > $(PWD)/release/version
	#tar zcvf gorm-release.`date +%Y%m%d%H%M`.tar.gz release/

clean:
	$(RM) $(GORMServer) $(ASYNC_TEST) $(ASYNC_TEST_OBJ) $(COMMON_OBJ) $(GORM_SVR_OBJ) $(GORMClient) $(TABLES_OBJ) $(GORM_CLIENT_OBJ) $(SHAREClient) $(STATICClient) $(SHARETABLES) $(STATICTABLES) $(TABLES_SVR_OBJ)

.PHONY: all 
