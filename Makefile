CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
TARGET = grep-lite

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

clean:
	rm -f $(TARGET) *.o
