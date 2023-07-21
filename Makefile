CC = gcc
CFLAGS = -Wall -Wextra -pthread

all: libfilesearch.a file_search_app

libfilesearch.a: file_search_lib.o
    ar rcs libfilesearch.a file_search_lib.o

file_search_lib.o: file_search_lib.c file_search_lib.h
    $(CC) $(CFLAGS) -c file_search_lib.c

file_search_app: main.c libfilesearch.a
    $(CC) $(CFLAGS) -o file_search_app main.c -L. -lfilesearch

clean:
    rm -f *.o *.a file_search_app
