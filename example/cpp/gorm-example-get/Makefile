# ================================================================
# Makefile for gorm example
#
# Date:   2020-06-29
# ================================================================

CCFILE=$(wildcard $(PWD)/src/*.cc)
TABLEFILE=$(wildcard $(GORM_HOME)/src/tables/*.cc)

SHARE_LIB=-L$(GORM_HOME)/lib/gorm -lgorm-client $(GORM_HOME)/lib/yaml/libyaml-cpp.a -lprotobuf -lpthread  -lm -lrt -lssl -lcrypto -ldl

INC =-I$(GORM_HOME)/include -I$(GORM_HOME)/example/gorm-example-get/src


.PHONY: all clean 

all:
	g++ -std=c++11 -lstdc++ -g -ggdb -rdynamic -DGORM_DEBUG=1 -o test_get gorm-example-get.cc $(CCFILE) $(TABLEFILE) $(INC) ${SHARE_LIB}

clean:
	rm -f test_get log.txt
