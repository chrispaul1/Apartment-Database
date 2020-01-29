CC = gcc
CFLAGS  = -g -Wall
	
TARGET = assign7
all: $(TARGET)
$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c
