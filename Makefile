TARGETS = madvise
OBJS = 
CC := gcc
CFLAGS = 
LDFLAGS = 


all: bigFile madvise

bigFile: 
	fallocate -l 1G bigFile

madvise:
	$(CC) -o madvise madvise.c

clean:
	rm -rf madvise
	rm -rf bigFile
