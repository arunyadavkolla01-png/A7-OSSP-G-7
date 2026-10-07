CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

SRC = src/main.c \
      src/auth.c \
      src/input.c \
      src/parser.c \
      src/process.c \
      src/builtin.c \
      src/signals.c \
      src/pipes.c \
      src/redirect.c

TARGET = bin/shellforge

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf bin/*

.PHONY: all run clean

