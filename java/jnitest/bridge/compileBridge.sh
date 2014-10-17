#!/bin/bash

#Kompiliert die gegebene c datei in zwei
#Schritten
#Erst ohne Linken, dann linken zu einer dylib...

if [ "$1" = "" ]; then
	echo usage: name.c ...
	exit
fi

gcc -c $1 sqlite3.c -I /System/Library/Frameworks/JavaVM.framework/Headers
gcc -dynamiclib -o lib$(echo $1 | sed s/".c"/""/g).dylib sqlite3.o $(echo $1 | sed s/".c"/""/g).o -I /System/Library/Frameworks/JavaVM.framework/Headers

rm *.o
