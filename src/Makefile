OBJS := main.o events.o input.o

all: $(PROJECT_NAME)

$(PROJECT_NAME): subdirs $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(PROJECT_NAME)

subdirs: input
	make -C input && cp input/input.o ./

.cpp.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(CLEAN) $(PROJECT_NAME) $(OBJS)

