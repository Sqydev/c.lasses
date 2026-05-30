CC = gcc

CFLAGS = -Wall -Wextra -I../../include
LDFLAGS = ../../lib/local-c11/libc_lasses.a

TARGET = polimorphism
SRC = $(wildcard *.c)

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS) -std=c11
