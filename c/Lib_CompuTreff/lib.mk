all:
	gcc -fPIC -c all.h *.c
	gcc -shared -o liball.so *.o 
clean:
	rm *.o *.so *.gch
