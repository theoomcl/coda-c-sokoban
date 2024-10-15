CC = gcc
CFLAGS = -Wall -g
TARGET = sokoban

all: $(TARGET)

$(TARGET): sokoban.o
		$(CC) $(CFLAGS) -o $(TARGET) sokoban.o

sokoban.o: sokoban.c sokoban.h
		$(CC) $(CFLAGS) -c sokoban.c 

clean:
	rm -f $(TARGET) *.o