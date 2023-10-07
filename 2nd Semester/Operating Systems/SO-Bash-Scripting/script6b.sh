#!/bin/bash

for line in `find dir -type f -perm -o=w`; do
	ls -l $line | awk '{print $1, $NF}'
	chmod o-w $line
	ls -l $line | awk '{print $1, $NF}'
done
