#!/bin/bash

IFS=$'\n'
if [ -z $1 ] || [ ! -f $1 ]; then
    echo "Neko"
else
    while read line; do
        echo "$line"
    done < "$1"

    for var in $(cat "$1"); do
        echo " $var"
    done
fi

