########################################################################
#                                                                       
#                   Main Makefile for FIRED project                     
#                                                                       
########################################################################
export PROJECT=fired
export CC=gcc
export STRIP=strip
export LD=ld
export CLEAN=rm -f
export MAKE=make
export MAKESRC=$(MAKE) -f $(PWD)/Makefile.src
export MAKESUB=$(MAKE) -j8 -C $$$$dir -f $(PWD)/Makefile.sub

export INCLUDE_DIR=$(PWD)/include
export LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lm -lstdc++ -lsqlite3
export CFLAGS=-Wall                   \
              -Wextra                 \
              -I$(INCLUDE_DIR)        \
              -I$(INCLUDE_DIR)/meta   \
              -I$(INCLUDE_DIR)/common



all: src
	$(MAKESRC) -C src
	$(STRIP) $(PROJECT)


clean:
	$(CLEAN) $(PROJECT)
