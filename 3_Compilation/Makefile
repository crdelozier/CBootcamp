CFLAGS += -O2

all: prog

prog: multi_cu1.o multi_cu2.o
	$(CC) multi_cu1.o multi_cu2.o -o prog $(CFLAGS)

multi_cu1.o:
	$(CC) -c multi_cu1.c $(CFLAGS)

multi_cu2.o:
	$(CC) -c multi_cu2.c $(CFLAGS)

clean:
	rm *.o prog
