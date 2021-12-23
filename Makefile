CC = gcc
CFLAGS = -g -Wall -Wextra -pedantic -fsanitize=address
BIN = test
SRC = main.c base.c bits.c

.PHONY: all
all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o $(BIN)
