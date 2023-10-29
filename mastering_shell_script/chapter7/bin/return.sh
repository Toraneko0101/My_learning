#!/bin/bash

check_file(){
    if [ -f "$1" ]; then
        return 0
    elif [ -d "$1" ]; then
        return 1 #directory
    else
        return 2 #deviceファイル
    fi
}

if [ -z "$1" ]; then
    echo "Usage: $0 file"
    exit 1
fi

check_file "$1"
status=$?
if [ $status = 0 ]; then
    echo "$1 is a regular file"
elif [ $status = 1 ]; then
    echo "$1 is a directory"
else
    echo "$1 is a device file"
fi