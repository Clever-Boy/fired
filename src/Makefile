OBJS := main.o events.o input.o
SUBDIRS := input

all: $(PROJECT_NAME)

$(PROJECT_NAME): subdirs $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(PROJECT_NAME)

subdirs: input
	for dir in $(SUBDIRS); do \
		make -C $$dir; \
	done

.cpp.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean: clean-subdirs
	$(CLEAN) $(PROJECT_NAME) $(OBJS)
	make -C input clean

clean-subdirs:
	for dir in $(SUBDIRS); do \
		make -C $$dir clean; \
	done
