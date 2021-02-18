CC = gcc
CFLAGS = -g -Wall 
SRC := $(wildcard *.c)
BIN := prueba
OBJS := $(SRC:.c=.o) 

.PHONY: clean all

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	@rm *.o $(BIN)
