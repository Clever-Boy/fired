OBJS := mouse.o keyboard.o
OUT  := input.o

all: $(OUT)

$(OUT): $(OBJS)
	$(LD) -r $(OBJS) -o ../$(OUT) 

.cpp.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(CLEAN) $(OBJS)

