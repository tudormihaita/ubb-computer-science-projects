#!/bin/bash

#cmd=`cat df.fake | awk '{print $2, $5, $6}'`
#echo $cmd

cat df.fake | \
grep -v "Filesystem" | \
awk '{print $2, $5, $6}' | \
sed 's/%//' | \
sed 's/M//' | \
while read dim use mnt; do
	#if [ ${#dim} -le 4 ] || [ $use -gt 80 ] ;  then
	if [ $dim -lt 1024 ] || [ $use -gt 80 ] ; then
		echo $mnt
	fi

done
