SHELL := /bin/bash

CC = gcc
CFLAGS = -g -Wall

BIN = ./a.out

SRC_DIR = ./src
BUILD_DIR = ./build

SRC := $(shell find $(SRC_DIR) -name "*.c")
OBJS := $(patsubst $(SRC_DIR)%.c,$(BUILD_DIR)%.o,$(SRC))
SUBDIRS := $(shell find $(SRC_DIR) -type d | grep -v ./src$)
SUBDIRS := $(patsubst $(SRC_DIR)%,$(BUILD_DIR)%,$(SUBDIRS))

.PHONY: all clean directories test

all: directories $(BIN)

test: directories $(BIN)
	@time ./a.out

$(BIN): $(OBJS) 
	$(CC) $(CFLAGS) $^ -o $(BIN)
	@echo 

directories:
	@mkdir -p $(SUBDIRS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	@rm -r $(BUILD_DIR)
