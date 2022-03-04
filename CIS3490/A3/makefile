all: P11 P12 P21 P22 P23

P11.o: P11.c
	gcc -std=gnu99 -Wall -pedantic -c P11.c -o P11.o

P11: P11.o
	gcc -std=gnu99 -Wall -pedantic P11.o -o P11
	
P12.o: P12.c
	gcc -std=gnu99 -Wall -pedantic -c P12.c -o P12.o

P12: P12.o
	gcc -std=gnu99 -Wall -pedantic P12.o -o P12
	
P21.o: P21.c
	gcc -std=gnu99 -Wall -pedantic -c P21.c -o P21.o

P21: P21.o
	gcc -std=gnu99 -Wall -pedantic P21.o -o P21

P22.o: P22.c
	gcc -std=gnu99 -Wall -pedantic -c P22.c -o P22.o

P22: P22.o
	gcc -std=gnu99 -Wall -pedantic P22.o -o P22

P23.o: P23.c
	gcc -std=gnu99 -Wall -pedantic -c P23.c -o P23.o

P23: P23.o
	gcc -std=gnu99 -Wall -pedantic P23.o -o P23

clean:
	rm -i *.o P11 P12 P21 P22 P23