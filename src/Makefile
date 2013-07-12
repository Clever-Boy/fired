all: $(PROJECT_NAME)

$(PROJECT_NAME): main.o
	$(CC) $(LDFLAGS) main.o -o $(PROJECT_NAME)

main.o: main.cpp
	$(CC) -o main.o -c main.cpp

clean:
	$(CLEAN) $(PROJECT_NAME) main.o

