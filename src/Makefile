SUBDIRS := ${shell find * -type d -print}

OBJS    := $(wildcard *.cpp)
OBJS    := $(OBJS:.cpp=.o)
OBJS    += $(SUBDIRS:=.o)

all: $(PROJECT_NAME)

$(PROJECT_NAME): subdirs $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(PROJECT_NAME)

subdirs: $(SUBDIRS)
	for dir in $(SUBDIRS); do \
		export SUBDIR=$$dir; \
		make -C $$dir; \
	done

.cpp.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean: clean-subdirs
	$(CLEAN) $(PROJECT_NAME) $(OBJS)

clean-subdirs:
	for dir in $(SUBDIRS); do \
		make -C $$dir clean; \
	done
