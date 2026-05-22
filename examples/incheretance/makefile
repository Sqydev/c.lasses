CC = gcc

CFLAGS = -Wall -Wextra -I../../include
LDFLAGS = ../../lib/local/libc_lasses.a

TARGET = incheretance
SRC = $(wildcard *.c)

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)
