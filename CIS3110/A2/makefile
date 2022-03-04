all: simcpu

simcpu: simcpu.o
	gcc -std=c99 -Wall -pedantic simcpu.o -o simcpu

simcpu.o: simcpu.c
	gcc -std=c99 -Wall -pedantic -c simcpu.c -o simcpu.o

clean: 
	rm -i *.o simcpu