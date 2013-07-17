OBJS := main.o events.o

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(PROJECT_NAME)

.cpp.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(CLEAN) $(PROJECT_NAME) $(OBJS)

