all: q1 q2

q1.o: q1.c
	gcc -g -std=gnu99 -Wall -pedantic -c q1.c -o q1.o

q1: q1.o
	gcc -g -std=gnu99 -Wall -pedantic q1.o -o q1

q2.o: q2.c
	gcc -g -std=gnu99 -Wall -pedantic -c q2.c -o q2.o

q2: q2.o
	gcc -g -std=gnu99 -Wall -pedantic q2.o -o q2
	
clean:
	rm -i *.o q1 q2
