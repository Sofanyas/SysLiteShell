# CC = gcc
# CFLAGS = -c -g -Wall $(INCLUDES)
# LDLIBS = -pthread

# all: sh257

# sh257: sh257.o csapp.o shellex.o
# 	$(CC) $(CFLAGS) $(LDLIBS) -o sh257 sh257.o csapp.o shellex.o

# sh257.o: sh257.c csapp.h
# 	$(CC) $(CFLAGS) $(LDLIBS) -c sh257.c

# csapp.o: csapp.c csapp.h
# 	$(CC) $(CFLAGS) $(LDLIBS) -c csapp.c

# shellex.o: shellex.c csapp.h
# 	$(CC) $(CFLAGS) $(LDLIBS) -c shellex.c

# clean:
# 	rm -v sh257

CC=gcc
CFLAGS= -c -g -Wall $(INCLUDES)

# Files
OBJECT_FILES=	csapp.o shellex.o

TARGET = sh257

# Productions
all : sh257

sh257 : $(OBJECT_FILES)
	$(CC)  $(OBJECT_FILES) -g -o $@ -pthread 

shellex.o : shellex.c csapp.h
	$(CC) $(CFLAGS) $< -o $@

csapp.o : csapp.c csapp.h
	$(CC) $(CFLAGS) $< -o $@

clean : 
	rm -v sh257 $(OBJECT_FILES)