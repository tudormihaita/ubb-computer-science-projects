#!/bin/bash

N=$1
X=1
while [ $X -le $N ]; do
	nr=`expr $X + 5`
	touch file_$X.txt | sed -n "$X,$nr p" passwd > file_$X.txt
	X=`expr $X + 1`
done
