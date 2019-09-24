CC=gcc
CFLAGS=-g -I. -Wall --std=c11
DEPS = cvm.h opcodes.h
OBJ = cvm.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cvm: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o cvm
