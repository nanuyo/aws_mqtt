# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Wpedantic -DMQTT_DO_NOT_USE_CUSTOM_CONFIG


# Include directory
INCLUDES = -I./include -I./interface


# Source files
SRCS = core_mqtt_serializer.c core_mqtt_state.c core_mqtt.c mqtt_demo_plaintext.c plaintext_posix.c backoff_algorithm.c sockets_posix.c clock_posix.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = my_program

# Build rule
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

# Compile rule
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)
