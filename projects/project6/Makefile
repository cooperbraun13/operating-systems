CC = gcc
CFLAGS = -Wall -pthread
TARGET = buffer

all: $(TARGET)

$(TARGET): buffer_starter.c buffer2.h
	$(CC) $(CFLAGS) buffer_starter.c -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET) 10 3 3

