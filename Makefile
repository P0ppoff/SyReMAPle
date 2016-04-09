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

DEBUG=no
ifeq ($(DEBUG),yes)
	CFLAGS=-g
	LDFLAGS=-lm
	# -W -Wall -ansi -pedantic
else
	CFLAGS=
	LDFLAGS=-lm
endif

EXECUTABLES=$(BIN_DIR)MakeHisto $(BIN_DIR)Offline $(BIN_DIR)Rdsift
#$(BIN_DIR)Post4 

all: $(EXECUTABLES)
ifeq ($(DEBUG),yes)
	@echo "Génération en mode debug"
else
	@echo "Génération en mode release"
endif

$(BIN_DIR)Rdsift: $(BUILD_DIR)rdsift.o $(BUILD_DIR)proc.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BIN_DIR)MakeHisto: $(BUILD_DIR)make_histo.o $(BUILD_DIR)rdjpeg.o $(BUILD_DIR)proc.o $(BUILD_DIR)histogramme.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BIN_DIR)Offline: $(BUILD_DIR)offline.o $(BUILD_DIR)rdjpeg.o $(BUILD_DIR)proc.o $(BUILD_DIR)histogramme.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)rdsift.o: $(SRC_DIR)rdsift.c $(HEADER_DIR)proc.h
	$(CC) $(CFLAGS) -c $< -I$(HEADER_DIR) -o $@ $(LDFLAGS)

$(BUILD_DIR)offline.o: $(SRC_DIR)offline.c $(HEADER_DIR)histogramme.h
	$(CC) $(CFLAGS) -c $< -I$(HEADER_DIR) -o $@ $(LDFLAGS)

$(BUILD_DIR)make_histo.o: $(SRC_DIR)make_histo.c $(HEADER_DIR)histogramme.h
	$(CC) $(CFLAGS) -c $< -I$(HEADER_DIR) -o $@ $(LDFLAGS)

$(BUILD_DIR)histogramme.o: $(SRC_DIR)histogramme.c $(HEADER_DIR)rdjpeg.h $(HEADER_DIR)proc.h $(HEADER_DIR)histogramme.h
	$(CC) $(CFLAGS) -c $< -I$(HEADER_DIR) -o $@ $(LDFLAGS)

$(BUILD_DIR)%.o: $(SRC_DIR)%.c $(HEADER_DIR)%.h 
	$(CC) $(CFLAGS) -c $< -I$(HEADER_DIR) -o $@ $(LDFLAGS)

# $(BIN_DIR)Post4: $(BUILD_DIR)post4.o $(BUILD_DIR)cgiu.o
# 	$(CC) $(CFLAGS) $^ -o $@

# $(BUILD_DIR)post4.o: $(SRC_DIR)post4.c $(HEADER_DIR)cgiu.h
# 	$(CC) $(CFLAGS) -c $< -I$(HEADER_DIR) -o $@

.PHONY: clean mrproper

clean:
	rm -f $(BUILD_DIR)*

mrproper: clean
	rm -f $(EXECUTABLES) 
