#!/bin/bash

for arg in $@; do
	if test -f $arg; then
		lines=`cat $arg | wc -l`
		chars=`cat $arg | wc -m`
		echo $arg $chars $lines
	elif test -d $arg; then
		files=`find $arg | wc -l`
		echo $arg $files
	fi
done
