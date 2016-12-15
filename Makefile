CC=clang
CFLAGS= -g -Wall
LFLAGS = -lMipsMachine.h

TARGET = mips
all: $(TARGET)
$(TARGET):$(TARGET).c
	$(CC) $(CLFAGS) -o $(TARGET) $(TARGET).c $(LFLAGS)
