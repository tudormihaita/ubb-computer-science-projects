#!/bin/bash

for X in `find dir -type f -perm -o=w -printf '%M %p\n' | awk '{print $1":"$2}'`; do
	F=`echo $X|cut -d: -f2`
	P=`echo $X|cut -d: -f1`
	echo $P $F
	chmod o-w $F
	newP=`find dir -wholename "$F" -printf '%M\n' | awk '{print $1}'`
	echo $newP $F
done
