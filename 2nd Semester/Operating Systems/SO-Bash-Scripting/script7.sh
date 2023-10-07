#!/bin/bash

string=""
for file in $@; do
	email=""
	email+=$file
	email+="@cs.ubbcluj.ro"
	string+=$email
	string+=","
done
echo $string | sed -E "s/,$//"
