#!/bin/bash


EXECUTABLE="forksum"
if [ ! -e $EXECUTABLE ] ; then
	echo "Compiling forksum.c"
	gcc -O -o forksum forksum.c -lm
fi

TIMEFORMAT='%3R'
# do some stuff here

exec 3>&1 4>&2
foo=$( { time ./${EXECUTABLE} 1 10000 1>&3 2>&4; } 2>&1 ) # change some_command
exec 3>&- 4>&-

#echo "The running time is $MOREF."
echo "`date +%s,` $foo" >> forksum.csv
