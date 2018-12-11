#!/bin/bash


EXECUTABLE="forksum"
if [ ! -e $EXECUTABLE ] ; then
	echo "Compiling forksum.c"
	gcc -O -o forksum forksum.c -lm
fi


MOREF=(time ./${EXECUTABLE} 1 10) |& awk '$1=="real"{print $2}'

echo $2
#echo "The running time is $MOREF."
#echo "`date +%s,` $result" >> /home/ccbenchmark/mem.csv
