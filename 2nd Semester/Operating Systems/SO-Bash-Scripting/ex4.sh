#!/bin/bash

if [ $# -lt 2 ]; then
	echo "Numar insuficient de argumente."
	exit 1
fi

CMD_FILE=$1
TEXT_FILE=$2
NL=$(cat $CMD_FILE | wc -l)

for L in $(seq 1 $NL); do
	#echo $L
	LINE=$(sed -n ''$L'p' $CMD_FILE)
	#echo $LINE
	CMD=$(echo $LINE | awk '{CMD=$1" "$2; print CMD}')
	#echo $CMD
	if [ "$CMD" = "INSERT LINE" ]; then
		ADDRESS=$(echo $LINE | awk '{print $3}')
		TEXT=$(echo $LINE | awk '{print $4}')
		#echo $ADDRESS
		#echo $TEXT
		sed -i "$ADDRESS i $TEXT" $TEXT_FILE
	elif [ "$CMD" = "APPEND LINE" ]; then
		TEXT=$(echo $LINE | awk '{print $3}')
		sed -i "$ a $TEXT" $TEXT_FILE
	elif [ "$CMD" = "REPLACE WORD" ]; then
		OLD=$(echo $LINE | awk '{print $3}')
		NEW=$(echo $LINE | awk '{print $4}')
		sed -i -E "s/$OLD/$NEW/g" $TEXT_FILE
	elif [ "$CMD" = "REPLACE CHAR" ]; then
 		OLD=$(echo $LINE | awk '{print $3}')
               	NEW=`echo $LINE | awk '{print $4}'`
		if [ "$NEW" = "" ]; then
			NEW=" "
		fi
                sed -i -E "s/$OLD/$NEW/g" $TEXT_FILE
	else
		echo "Comanda invalida!"
	fi
done
