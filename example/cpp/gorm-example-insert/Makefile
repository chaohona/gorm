# ================================================================
# Makefile for gorm example
#
# Date:   2020-06-29
# ================================================================

CCFILE=$(wildcard $(PWD)/src/*.cc)
TABLEFILE=$(wildcard $(GORM_HOME)/src/tables/*.cc)

SHARE_LIB=-L$(GORM_HOME)/lib/mysql-connector -lmysqlclient -L$(GORM_HOME)/lib/gorm -lgorm-client $(GORM_HOME)/lib/yaml/libyaml-cpp.a -lprotobuf -lpthread  -lm -lrt -lssl -lcrypto -ldl

INC =-I$(GORM_HOME)/include -I$(GORM_HOME)/example/gorm-example-insert/src -I$(GORM_HOME)/thirdparty/mysql-connector


.PHONY: all clean 

all:
	g++ -std=c++11 -lstdc++ -o test_insert gorm-example-insert.cc $(CCFILE) $(TABLEFILE) $(INC) ${SHARE_LIB}

clean:
	rm -f test_insert log.txt
