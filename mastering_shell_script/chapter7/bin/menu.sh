#!/bin/bash

to_lower(){
    input="$1"
    output=$( echo $input | tr [A-Z] [a-z])
    echo $output
}

do_backup(){
    tar -czvf ../backup.tgz ../bin
}

show_cal(){
    #ncalが利用可能なら-wで週番号を表示する
    if [ -x /usr/bin/ncal ]; then
        command="/usr/bin/ncal -w"
    else
        command="/usr/bin/cal"
    fi
    $command
}

while true
do
    clear
    echo "Choose an item: a, b or c"
    echo "a: Backup"
    echo "b: Display Calender"
    echo "c: Exit"
    read -sn1
    REPLY=$(to_lower "$REPLY")
    case "$REPLY" in
        a) do_backup;;
        b) show_cal;;
        c) exit 0;;
    esac
    read -n1 -p "Press any key to continue"
done