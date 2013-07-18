########################################################################
#                                                                       
#                   Main Makefile for FIRED project                     
#                                                                       
########################################################################
export PROJECT_NAME=fired
export PROJECT_VER=0.99

export CC=gcc
export LD=ld
export CLEAN=rm -rf
export MAKE=make
export MAKESUB=$(MAKE) -C $$$$dir -f ../Makefile.sub

export PROJECT_DIR="$(PWD)"
export INCLUDE_DIR="$(PWD)/include"

export LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
export CFLAGS=-I$(INCLUDE_DIR) -DPROJECT_NAME="\"$(PROJECT_NAME)\"" -DPROJECT_VER="\"$(PROJECT_VER)\""



all: src
	$(MAKE) -C src
	cp -f src/$(PROJECT_NAME) ./


clean: src
	$(MAKE) -C src clean
	$(CLEAN) $(PROJECT_NAME)
