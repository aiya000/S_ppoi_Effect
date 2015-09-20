#!/bin/sh
if [ ${#1} -gt 0 ] ; then
	if [ "$1" = "-d" ] ; then
		echo "debug build"
		gcc -g -O0 -I/usr/include/ncurses sound_ppoino.c -o s_ppoino -lncurses -lpthread
	elif [ "$1" = "-r" ] ; then
		echo "release build and run"
		gcc -g -O0 -I/usr/include/ncurses sound_ppoino.c -o s_ppoino -lncurses -lpthread ; wait
		./s_ppoino
	fi
else
	echo "release build"
	gcc -I/usr/include/ncurses sound_ppoino.c -o s_ppoino -lncurses -lpthread
fi
