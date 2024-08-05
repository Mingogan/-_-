all: main

phoneBook.o: phoneBook.c
	gcc -c phoneBook.c -o phoneBook.o

test.lib: phoneBook.o
	ar r test.lib phoneBook.o

main: task_6_1.c test.lib
	gcc task_6_1.c -o main  -L . test.lib