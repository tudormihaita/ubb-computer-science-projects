#!/bin/bash

if [ ! $# -eq 1 ]; then
	echo "Numar invalid de argumente."
	echo "Utilizare: $0 dir"
	exit 1
fi

DIR=$1
LOG=$(find $DIR -type f -name "*.log" | wc -l)
TXT=$(find $DIR -type f -name "*.txt" | wc -l)
OTHER=$(find $DIR -type f | wc -l)
OTHER=`expr $OTHER - $LOG`
OTHER=`expr $OTHER - $TXT`
DIRS=$(find $DIR -type d | tail -n +2 | wc -l)

NLINES=0
for FILE in `find $DIR -type f -name "*.txt"`; do
	N=$(cat $FILE | wc -l)
	NLINES=`expr $NLINES + $N`
done

NMATCHES=0
for FILE in `find $DIR -type f -name "*.log"`; do
	N=$(grep -E "warning|error" $FILE | wc -l)
	NMATCHES=`expr $NMATCHES + $N`
done

echo "Numarul de fisiere cu extensia .txt: $TXT"
echo "Numarul de fisiere cu extensia .log: $LOG"
echo "Numarul de fisiere cu alte extensii: $OTHER"
echo "Numarul de directoare: $DIRS"
echo "Numarul liniilor din fisierele txt: $NLINES"
echo "Numarul liniilor care contin warning sau error din fisierele log: $NMATCHES"
