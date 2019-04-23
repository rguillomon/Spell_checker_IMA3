exe: main.o annexe.o tree.o
	gcc -g -o exe main.o annexe.o tree.o

annexe.o: annexe.c annexe.h
	gcc -c -g -O0 -Wall -Wextra annexe.c

tree.o: tree.c tree.h
	gcc -c -g -O0 -Wall -Wextra tree.c

main.o: main.c
	gcc -c -g -O0 -Wall -Wextra main.c

clean:
	rm -rf *.o
	rm exe
