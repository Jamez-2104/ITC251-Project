CC = gcc
CFLAGS = -Wall -g

all:
	$(CC) $(CFLAGS) -o grep-lite main.c search.c

clean:
	rm -f grep-lite
