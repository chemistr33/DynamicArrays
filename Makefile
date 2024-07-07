# libvector & Demonstration Makefile
CC = gcc
CFLAGS = -g -Wall -fPIC
LDFLAGS = -shared
TARGET_LIB = libvector.so

# Source Files
VECLIB_SRC = vector.c
VECLIB_OBJ = vector.o

# Header File
VECLIB_HEADER = vector.h

# Demo Files
DEMO_SRC = demo.c
DEMO_BIN = demo

# Top Level Library Build Rule
library: $(TARGET_LIB)

# Build libvector dynamic library
$(TARGET_LIB): $(VECLIB_OBJ)
	$(CC) $(LDFLAGS) $(VECLIB_OBJ) -o $(TARGET_LIB)

# Compile the libvector object file
$(VECLIB_OBJ): $(VECLIB_SRC) $(VECLIB_HEADER)
	$(CC) $(CFLAGS) -c $(VECLIB_SRC)

# Top Level Demo Build Rule
dem: $(DEMO_BIN)

# Compile demo binary & link against libvector library
$(DEMO_BIN): $(DEMO_SRC) $(TARGET_LIB)
	$(CC) -L. -o $(DEMO_BIN) $(DEMO_SRC) -lvector

clean:
	rm -f $(VECLIB_OBJ) $(TARGET_LIB) $(DEMO_BIN)