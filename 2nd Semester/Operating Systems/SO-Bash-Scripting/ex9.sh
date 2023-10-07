#!/bin/bash

if [ ! $# -eq 1 ]; then
	echo "Numar invalid de argumente."
	echo "Utilizare: $0 dir"
	exit 1
fi

DIR=$1
for FILE in `find $DIR -type f -name "*.log"`; do
	NAME=`basename $FILE`
	echo "$NAME are extensia .log"
	LINES=`cat $FILE | grep -o -E "system" | grep -o -E "\broot\b" | wc -l`
	echo "Fisierul $NAME contine $LINES linii cu cuvintele error si warning"
done

for D in `find $DIR -maxdepth 1 -type d`; do
	FILES=`find $D -type f | wc -l`
	echo "Directorul $D contine $FILES fisiere"
done
