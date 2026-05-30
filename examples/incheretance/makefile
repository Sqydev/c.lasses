CC = gcc

CFLAGS = -Wall -Wextra -I../../include
LDFLAGS = ../../lib/local-c99/libc_lasses.a

TARGET = incheretance
SRC = $(wildcard *.c)

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)
