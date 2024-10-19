# Makefile for ppmdiff (Comp 40 Assignment)
#
# This Makefile includes build rules for ppmdiff and its related object files.
#
# Last updated: October 11, 2024

############## Variables ###############

CC = gcc  # The compiler being used

# Update include path to use Comp 40 .h files and CII interfaces
IFLAGS = -I/comp/40/build/include -I/usr/sup/cii40/include/cii

# Compile flags
# Set debugging information, use the GNU 99 standard, max out warnings,
# and use the updated include path
CFLAGS = -g -std=gnu99 -Wall -Wextra -Werror -Wfatal-errors -pedantic $(IFLAGS)

# Linking flags
# Set debugging information and update linking path to include course binaries and CII implementations
LDFLAGS = -g -L/comp/40/build/lib -L/usr/sup/cii40/lib64

# Libraries needed for linking
# Includes libraries for PPM image handling and CII implementations
LDLIBS = -l40locality -lnetpbm -lcii40 -lm -lrt -larith40

# Collect all .h files in your directory.
# This way, you can never forget to add a local .h file in your dependencies.
INCLUDES = $(shell echo *.h)

############### Rules ###############

# Default target: build the ppmdiff executable
all: ppmdiff unit_test

## Compile step (.c files -> .o files)

# Rule for building object files from C files
%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

## Linking step (.o -> executable program)

# Rule for building ppmdiff from its object files
ppmdiff: ppmdiff.o uarray2b.o uarray2.o a2blocked.o a2plain.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

uarray2b.o: uarray2b.c uarray2b.h uarray2.o
	$(CC) $(CFLAGS) -c uarray2b.c

uarray2.o: uarray2.c uarray2.h
	$(CC) $(CFLAGS) -c uarray2.c

compress40.o: compress40.c uarray2b.o uarray2.o a2blocked.o a2plain.o
	$(CC) $(CFLAGS) -c compress40.c

unit_test: unit_test.o compress40.o uarray2b.o uarray2.o a2blocked.o a2plain.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

# Clean up the built files
clean:
	rm -f ppmdiff *.o
