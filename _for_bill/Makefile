#=========================================================================
#  Simple Makefile for magdata
#
#  Author:      David Witten, KD0EAG
#  Date:        December 18, 2023
#  License:     GPL 3.0
#  Note:        replaces i2c.c (using file system calls to read(), write(), etc.
#               with calls to pigpio. 
#               Also adding callbacks on GPIO27 for PPS rising edge.
#=========================================================================
CC = gcc
LD = gcc
GPERF = gperf
CXX = g++
#DEPS = main.h MCP9808.h rm3100.h magdata.h cmdmgr.h commands.h 
DEPS = main.h MCP9808.h rm3100.h
#SRCS = main.c magdata.c cmdmgr.c
SRCS = main.c
OBJS = $(subst .c,.o,$(SRCS))
#DOBJS = main.o magdata.o cmdmgr.o
#DOBJS = main.o magdata.o
DOBJS = main.o
LIBS = -lm -lpigpiod_if2 -lrt
DEBUG = -g -Wall
CFLAGS = -I.
LDFLAGS =
TARGET_ARCH =
LOADLIBES =
LDLIBS =
GPERFFLAGS = --language=ANSI-C 

TARGET = magdata

RM = rm -f

all: release

debug: main.c$(DEPS) 
#	$(CC) -c $(DEBUG) magdata.c  
#	$(CC) -o $(TARGET) $(DEBUG) main.c magdata.o $(LIBS)
	$(CC) -o $(TARGET) $(DEBUG) main.c $(LIBS)

release: main.c $(DEPS)
#	$(CC) -Wall -pthread -c $(CFLAGS) magdata.c
	$(CC) -Wall -pthread -o $(TARGET) $(CFLAGS) main.c $(LIBS)
	
#release: magdata.c $(DEPS)
#	$(CC) -Wall -pthread -c $(CFLAGS) magdata.c
#	$(CC) -Wall -pthread -o $(TARGET) $(CFLAGS) main.c magdata.o $(LIBS)
#	$(CC) -Wall -pthread -c $(CFLAGS) cmdmgr.c
#	$(CC) -Wall -pthread -o $(TARGET) $(CFLAGS) main.c magdata.o cmdmgr.o $(LIBS)

clean:
	$(RM) $(OBJS) $(TARGET)

distclean: clean
	
.PHONY: clean distclean all debug release
