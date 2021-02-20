CC = gcc
CFLAGS = -g -Wall 

BIN = main
SRC := $(wildcard *.c)
OBJS := $(SRC:.c=.o) 

.PHONY: clean 

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	@rm *.o 
