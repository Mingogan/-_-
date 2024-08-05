all: main

libphonebook.so: phoneBook.o
	gcc -shared phoneBook.o -o libphonebook.so

phoneBook.o: phoneBook.c
	gcc -fPIC -c phoneBook.c -o phoneBook.o

main: task_6_2.c libphonebook.so
	gcc task_6_2.c -L. -lphonebook -o main