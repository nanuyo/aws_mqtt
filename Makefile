CC = gcc
CFLAGS = -Wall -Wextra

# Find all C source files in the current directory
SRCS := $(wildcard *.c)

# Include directory
INCLUDES = -I./include -I./interface

# Generate corresponding object file names
OBJS := $(SRCS:.c=.o)

# Generate corresponding executable file names
EXECS := $(SRCS:.c=)

.PHONY: all clean

all: $(EXECS)

%: %.o
	$(CC) $(CFLAGS) $(INCLUDES)  $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES)  -c $< -o $@

clean:
	rm -f $(OBJS) $(EXECS)
