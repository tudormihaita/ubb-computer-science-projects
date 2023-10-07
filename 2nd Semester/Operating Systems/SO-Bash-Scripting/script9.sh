#!/bin/bash

SUMS=""
for file in `find dir -type f`; do
	SUM=`md5sum $file | awk '{print $1}'`
	FILES="Checksum is: $SUM\n$file"
	PRINT_IT="0"
	echo -e $SUMS | grep -q $SUM
	if [ $? -ne 0 ]; then
		SUMS="$SUMS\n$SUM"
		for file2 in `find dir -type f | grep -v $file`; do
			SUM2=`md5sum $file2 | awk '{print $1}'`
			if [ $SUM = $SUM2 ]; then
				FILES="$FILES\n$file2"
				PRINT_IT="1"
			fi
		done
	if [ $PRINT_IT = "1" ]; then
		echo -e $FILES
		echo
	fi
	fi
done
