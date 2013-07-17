########################################################################
#                                                                       
#                   Main Makefile for FIRED project                     
#                                                                       
########################################################################
export PROJECT_NAME=fired
export PROJECT_VER=0.99

export CC=gcc
export LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
export CLEAN=rm -rf
export CFLAGS=-I$(PWD)/include

all: src
	make -C src
	cp -f src/$(PROJECT_NAME) ./

clean: src
	make -C src clean
	$(CLEAN) $(PROJECT_NAME)
