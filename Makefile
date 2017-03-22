CC=gcc
CFLAGS= -g -Wall
SRC = mips.c MipsMachine.c Opcodes.c VirtualMemory.c
OBJ = $(SRC: .c=.o)
OUT = mips

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(OUT)

.c.o: $(CC) $(CFLAGS) $< -o $@

clean:
	-@rm -rf $(OBJ) $(OUT)
