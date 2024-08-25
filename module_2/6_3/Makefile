all: main

main: libsum.so libsubtract.so libmultiply.so libdivide.so task_6_3.c
	gcc task_6_3.c -o main -ldl

libsum.so: sum.c
	gcc -fPIC -shared sum.c -o libsum.so

libsubtract.so: subtract.c
	gcc -fPIC -shared subtract.c -o libsubtract.so

libmultiply.so: multiply.c
	gcc -fPIC -shared multiply.c -o libmultiply.so

libdivide.so: divide.c
	gcc -fPIC -shared divide.c -o libdivide.so