#!/bin/bash

re='^[0-9]+$'

if [[ -z  $1 ]] 
then 
	echo parametrs not found
elif [[ $1 =~ $re ]];
then 
	ppid=$(ps -o ppid= -p $1)
	name=$(ps -p $1 -o comm=)
	echo "Name: "$name
	echo "Pid:  "$1
	echo PPid: $ppid

	if [[ "fd" == $2 ]]
	then
		while read -r line
		do
			echo fd = $line
		done <<< $(ls -l/proc/$1/fd/)
	fi
else
	echo pid=$1 process not found
fi

