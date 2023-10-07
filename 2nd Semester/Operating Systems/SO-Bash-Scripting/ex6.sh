#!/bin/bash

#PROBLEMA 9 LAB BOTA

if [ $# -lt 1 ]; then
	echo "Numar invalid de argumente."
	echo "Mod utilizare: $0 file1 file2 ..."
	exit 1
fi

echo "Liniile care apar de cele mai multe ori din fiecare fisier dat:"

for FILE in $@; do
	NR=$(awk 'NF' $FILE | sort | uniq -c | sort -n -r | head -n 1 | awk '{print $1}')
	LINE=$(awk 'NF' $FILE | sort | uniq -c | sort -n -r | head -n 1 | awk '{print $2}')
	echo "Fisierul $FILE: $LINE $NR"
done | \
sort -k 4 -r
