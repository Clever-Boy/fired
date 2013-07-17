OBJS := mouse.o keyboard.o
OUT  := input.o

all: $(OUT)

$(OUT): $(OBJS)
	$(CC) -o ../$(OUT) -c $(OBJS)

.cpp.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(CLEAN) $(OBJS)

