CC = gcc
CFLAGS = -g -Wall 
SRC := $(wildcard *.c)
BIN := main
OBJS := $(SRC:.c=.o) 

.PHONY: clean all 

comp: $(OBJS)
	$(CC) $(CFLAGS) $^ 

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	@rm *.o 
