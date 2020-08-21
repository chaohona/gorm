# ================================================================
# Makefile for gorm example
#
# Date:   2020-06-29
# ================================================================

CCFILE=$(wildcard $(PWD)/src/*.cc)
TABLEFILE=$(wildcard $(GORM_HOME)/src/tables/*.cc)

SHARE_LIB=-L$(GORM_HOME)/lib/mysql-connector -lmysqlclient -L$(GORM_HOME)/lib/gorm -lgorm-client $(GORM_HOME)/lib/yaml/libyaml-cpp.a -lprotobuf -lpthread  -lm -lrt -lssl -lcrypto -ldl

INC =-I$(GORM_HOME)/include -I$(GORM_HOME)/example/gorm-example-update/src -I$(GORM_HOME)/thirdparty/mysql-connector


.PHONY: all clean 

all:
	g++ -std=c++11 -lstdc++ -g -ggdb -rdynamic -o test_update gorm-example-update.cc $(CCFILE) $(TABLEFILE) $(INC) ${SHARE_LIB}

clean:
	rm -f test_update log.txt
