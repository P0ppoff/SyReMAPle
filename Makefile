UNAME := $(shell uname -s)
ifeq ($(UNAME),Darwin)
	CC = gcc-5
else
	CC = gcc
endif

CFLAGS= 
LDFLAGS= 

EXECUTABLES=Offline

all: $(EXECUTABLES)

Offline: offline.o rdjpeg.o
	$(CC) $(CFLAGS) rdjpeg.o offline.o -o $@

offline.o: offline.c rdjpeg.h
	$(CC) $(CFLAGS) -c offline.c 

rdjpeg.o: rdjpeg.c rdjpeg.h
	$(CC) $(CFLAGS) -c rdjpeg.c

# Offline: offline.c rdjpeg.h rdjpeg.c
# 	$(CC) $(CFLAGS) rdjpeg.o offline.c -o $@

# %.o: %.c %.h 
# 	$(CC) $(CFLAGS) $< -c $@

clean:
	rm -f offline.o rdjpeg.o

mrproper: clean
	rm -f $(EXECUTABLES) 