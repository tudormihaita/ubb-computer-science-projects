#!/bin/bash

if [ ! $# -eq 1 ]; then
	echo "Numar invalid de argumente."
	exit 1
fi

DIR=$1

for FILE in $(find $DIR -type f -name "*.log"); do
	ERRORNR=$(cat $FILE | grep -E "error" | wc -l)
	WARNINGNR=$(cat $FILE | grep -E "warning" | wc -l)
	echo "$FILE errorNR:$ERRORNR warningNr:$WARNINGNR"
done

echo

for D in $(find $DIR -maxdepth 1 -type d); do
	FILES=$(ls -l $D | grep -v "^d" | wc -l)
	NAME=$(basename $D)
	echo "$NAME $FILES"
done
