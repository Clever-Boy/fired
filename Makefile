########################################################################
#                                                                       
#                   Main Makefile for FIRED project                     
#                                                                       
########################################################################
export PROJECT_NAME=fired
export PROJECT_VER=0.99

export CC=gcc
export STRIP=strip
export LD=ld
export CLEAN=rm -rf
export MAKE=make
export MAKESRC=$(MAKE) -f $(PWD)/Makefile.src
export MAKESUB=$(MAKE) -C $$$$dir -f $(PWD)/Makefile.sub

export PROJECT_DIR="$(PWD)"
export INCLUDE_DIR="$(PWD)/include"

export LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lm
export CFLAGS=-I$(INCLUDE_DIR) -DPROJECT_NAME="\"$(PROJECT_NAME)\"" -DPROJECT_VER="\"$(PROJECT_VER)\""



all: clean src
	$(MAKESRC) -C src
	cp -f src/$(PROJECT_NAME) ./


clean: src
	$(MAKESRC) -C src clean
	$(CLEAN) $(PROJECT_NAME)
