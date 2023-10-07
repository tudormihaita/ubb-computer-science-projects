#!/bin/bash

if [ ! $# -eq 1 ]; then
	echo "Numar invalid de argumente."
	echo "$0 fisier"
	exit 1
fi

COMMANDS=$1

cat $COMMANDS | while read LINE; do
	CMD=$(echo $LINE | awk '{print $1" "$2}')
	if [ "$CMD" = "CREATE DIR" ]; then
		DIRNAME=$(echo $LINE | awk '{print $3}')
		mkdir $DIRNAME
	elif [ "$CMD" = "CREATE FILE" ]; then
		FILENAME=$(echo $LINE | awk '{print $3}')
		touch $FILENAME
	elif [ "$CMD" = "MOVE DIR" ]; then
		OLD=$(echo $LINE | awk '{print $3}')
		NEW=$(echo $LINE | awk '{print $4}')
		mv $OLD $NEW
	elif [ "$CMD" = "SET PERM" ]; then
		FILENAME=$(echo $LINE | awk '{print $3}')
		PERM=$(echo $LINE | awk '{print $4}')
		chmod $PERM $FILENAME
	else
		echo "Comanda invalida!"
	fi
done
