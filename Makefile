########################################################################
#                                                                       
#                   Main Makefile for FIRED project                     
#                                                                       
########################################################################
PROJECT     = fired
CC          = g++
STRIP       = strip
CLEAN       = rm -f
MAKE        = make -j8 --no-print-directory
INCLUDE_DIR = $(PWD)/include
OBJS        = $(patsubst %.cpp,%.o,$(wildcard src/*/*.cpp))

LDFLAGS     = -static-libstdc++ \
              -static-libgcc    \
              -lsfml-graphics   \
              -lsfml-window     \
              -lsfml-system     \
              -lsfml-audio      \
              -lm               \
              -lsqlite3

CFLAGS      = -Wall                 \
              -Wextra               \
              -I$(INCLUDE_DIR)      \
              -I$(INCLUDE_DIR)/meta


all:
	$(MAKE) $(PROJECT)


$(PROJECT): $(OBJS)
	$(CC) $(OBJS) -o $(PROJECT) $(LDFLAGS)
	$(STRIP) $(PROJECT)


.cpp.o:
	$(CC) $(CFLAGS) -o $@ -c $<


clean:
	$(CLEAN) $(OBJS) $(PROJECT)
