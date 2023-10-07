#!/bin/bash

for file in `find dir -name "*.log"`; do
	cat $file | sort > temp.txt | mv temp.txt $file
	cat $file
done
