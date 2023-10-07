#!/bin/bash

#PROBLEMA 11 LAB BOTA

if [ $# -lt 1 ]; then
	echo "Numar invalid de argumente."
	echo "Utilizare: $0 file1 file2 ..."
	exit 1
fi


for FILE in $@; do
	if test -f $FILE; then
		PERMS=$(stat -c '%a' $FILE)
		if [ "$PERMS" = "755" ]; then
			echo "$FILE are permisiunile 755"
			read -p "Doriti modificarea permisiunilor fisierului in 744?[Y/N]" CONFIRM
			if [ "$CONFIRM" = "Y" ]; then
				chmod 744 $FILE
				echo "Permisiuni modificate cu succes!"
			else
				echo "Ati refuzat modificarea permisiunilor!"
			fi
		fi
	else
		echo "$FILE nu este fisier!"
	fi
done
