UNAME := $(shell uname -s)
ifeq ($(UNAME),Darwin)
	CC = gcc-5
else
	CC = gcc
endif

HEADER_DIR=headers/
SRC_DIR=src/
BUILD_DIR=build/
BIN_DIR=bin/

DEBUG=yes
ifeq ($(DEBUG),yes)
	CFLAGS=-g
	LDFLAGS=
	# -W -Wall -ansi -pedantic
else
	CFLAGS=
	LDFLAGS=
endif

EXECUTABLES=$(BIN_DIR)Offline 
#$(BIN_DIR)Post4

all: $(EXECUTABLES)
ifeq ($(DEBUG),yes)
	@echo "Génération en mode debug"
else
	@echo "Génération en mode release"
endif

$(BIN_DIR)Offline: $(BUILD_DIR)offline.o $(BUILD_DIR)rdjpeg.o $(BUILD_DIR)proc.o $(BUILD_DIR)utils.o
	$(CC) $(CFLAGS) $^ -o $@

$(BIN_DIR)Post4: $(BUILD_DIR)post4.o $(BUILD_DIR)cgiu.o
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)post4.o: $(SRC_DIR)post4.c $(HEADER_DIR)cgiu.h
	$(CC) $(CFLAGS) -c $< -I$(HEADER_DIR) -o $@

$(BUILD_DIR)offline.o: $(SRC_DIR)offline.c $(HEADER_DIR)rdjpeg.h $(HEADER_DIR)proc.h $(HEADER_DIR)utils.h
	$(CC) $(CFLAGS) -c $< -I$(HEADER_DIR) -o $@

$(BUILD_DIR)%.o: $(SRC_DIR)%.c $(HEADER_DIR)%.h 
	$(CC) $(CFLAGS) -c $< -I$(HEADER_DIR) -o $@

.PHONY: clean mrproper

clean:
	rm -f $(BUILD_DIR)*

mrproper: clean
	rm -f $(EXECUTABLES) 
