## CloudComputing
# Assignment 2 -- forksum benchmark

**Objective:**
a parallel computation of an integer range sum

**List of files**
** forksum.c: **
a start and end value of an integer range and prints the sum of allnumbers
in that range on stdout. Unless start and end are equal your program should fork twice, with each child computing a subrange and the parent process reading the results from a pipe.

** forksum_para.c: **
The same function as ``forksum.c`` below, but allows more paralelle processes, however both the running time and allowed integer range are worse than the first one

** measure-forksum.sh **
Shell file which executes the c program and put the execution real time as result in csv file. *Default running with forksum.c with range 1-10000*

*Remarque: from a google instance, the max range of ``forksum.c`` is up to 1-1000000, the max range for ``forksum_para.c`` is around 1-6000.*