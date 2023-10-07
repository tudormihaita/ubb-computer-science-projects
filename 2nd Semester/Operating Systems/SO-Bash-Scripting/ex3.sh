#!/bin/bash

if [ $# -lt 1 ]; then
	echo "Invalid number of arguments provided!"
	exit 1
fi

touch out

for FILE in $@; do
	file $FILE | grep -q "ASCII text"
	if [ $? -eq 0 ]; then
		cat $FILE | head -n 1 >> out
	fi
done
