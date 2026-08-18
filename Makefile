CC = gcc

CFLAGS = -Wall -Wextra -g -Iinclude

SRC = src/main.c src/auth.c src/input.c

TARGET = bin/multishell


all: $(TARGET)


$(TARGET): $(SRC)
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)


run:
	./$(TARGET)


clean:
	rm -rf bin/*


rebuild: clean all
