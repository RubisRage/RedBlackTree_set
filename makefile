CC = gcc
CFLAGS = -g -Wall 

BIN = test
SRC := $(wildcard *.c)
OBJS := $(SRC:.c=.o) 
OBJS += wrappers.o
SRC += $(wildcard */*.c)

.PHONY: clean 

$(BIN): $(OBJS)
	@echo $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	@rm *.o 
