#!/bin/bash

for user in `cat who.fake | awk '{print $1}'`; do
	nr=`cat ps.fake | grep -E "^$user" | wc -l`
	echo $user $nr
done
