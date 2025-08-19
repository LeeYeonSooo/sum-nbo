#Makefile
all: sum-nbo

sum-nbo: sum-nbo.o
	gcc -o sum-nbo sum-nbo.o

sum-nbo.o: sum-nbo.c
	gcc -c -o sum-nbo.o sum-nbo.c

clean:
	rm -f sum-nbo
	rm -f *.o
