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

CFLAGS= 
LDFLAGS= 

EXECUTABLES=Offline

all: $(EXECUTABLES)

Offline: $(BUILD_DIR)offline.o $(BUILD_DIR)rdjpeg.o
	$(CC) $(CFLAGS) $(BUILD_DIR)rdjpeg.o $(BUILD_DIR)offline.o -o $@
	mv $@ $(BIN_DIR)

$(BUILD_DIR)offline.o: $(SRC_DIR)offline.c $(HEADER_DIR)rdjpeg.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)offline.c -I$(HEADER_DIR) -o $@

# $(BUILD_DIR)rdjpeg.o: $(SRC_DIR)rdjpeg.c $(HEADER_DIR)rdjpeg.h
# 	$(CC) $(CFLAGS) -c $(SRC_DIR)rdjpeg.c -I$(HEADER_DIR) -o $@

# Offline: offline.c rdjpeg.h rdjpeg.c
# 	$(CC) $(CFLAGS) rdjpeg.o offline.c -o $@

$(BUILD_DIR)%.o: $(SRC_DIR)%.c $(HEADER_DIR)%.h 
	$(CC) $(CFLAGS) -c $< -I$(HEADER_DIR) -o $@

clean:
	rm -f $(BUILD_DIR)*

mrproper: clean
	rm -f $(BIN_DIR)$(EXECUTABLES) 