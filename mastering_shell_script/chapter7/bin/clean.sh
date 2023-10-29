#!/bin/bash

is_file(){
    if [ ! -f "$1" ]; then
        echo "$1 does not seem to be a file"
        exit 2
    fi
}

clean_file(){
    is_file "$1"
    #実行結果をBEFOREに代入
    BEFORE=$(wc -l "$1")
    echo "The file $1 starts with $BEFORE"
    sed -i.bak '/^\s*#/d;/^$/d' "$1"
    AFTER=$(wc -l "$1")
    echo "The file $1 is now $AFTER"
}

read -p "Enter a file to clean:"
#第一引数に代入
clean_file "$REPLY"
exit 1


# Enter a file to clean:ntp.conf
# The file ntp.conf starts with 60 ntp.conf
# The file ntp.conf is now 16 ntp.conf
