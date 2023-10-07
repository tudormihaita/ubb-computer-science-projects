#!/bin/bash

nr=0
for file in `find dir -name "*.c"`; do
	lines=`cat $file | wc -l`
	if [ $lines -gt 500 ]; then
		nr=`expr $nr + 1`
		echo $file
		if [ $nr -eq 2 ]; then
			break
		fi
	fi
done
