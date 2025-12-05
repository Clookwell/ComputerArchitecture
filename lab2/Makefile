lib:
	gcc -shared ./lib.h ./lib.c -o ./libmylib.so

obj:
	gcc -c -I. ./main.c -o ./main.o

link: lib obj
	gcc -L. -lmylib ./main.o -o ./main

build: link

run: build
	LD_LIBRARY_PATH=.:{$LD_LIBRARY_PATH} ./main

clean:
	rm *.o
	rm *.so
	rm ./main
