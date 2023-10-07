#!/bin/bash

#PROBLEMA 10 LAB BOTA

if [ ! $# -eq 1 ]; then
	echo "Numar invalid de argumente."
	echo "Utilizare: $0 dir"
	exit 1
fi

DIR=$1
for FILE in `find $DIR -type f`; do
	NAME=$(echo $FILE | sed -E "s/(.*\/)(.*)/\2/")
	LEN=${#NAME}
	if [ $LEN -lt 8 ]; then
		echo "$NAME are numele mai scurt de 8 caractere"
		if file $FILE | grep -q "ASCII text$"; then
			echo "Primele 10 linii ale fisierului text $NAME:"
			cat $FILE | head -n 10
			echo
		fi
	fi
done
