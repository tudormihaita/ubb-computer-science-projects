#!/bin/bash

if [ $# -lt 1 ]; then
	echo "Invalid number of arguments provided!"
	exit 1
fi

FILE=""
STOP="stop"
while true; do
	read -p "Enter the filename: " FILE
	FOUND="0"
	MATCH="$FILE conains: "
	for STRING in $@; do
		cat $FILE | grep -q "$STRING"
		if [ $? -eq 0 ]; then
			MATCH="$MATCH $STRING"
			FOUND="1"
		fi
	done

	if [ $FOUND = "1" ]; then
		echo $MATCH
		echo
	else
		echo "No strings matched for the file $FILE!"
	fi
done
