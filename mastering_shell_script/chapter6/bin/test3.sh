#!/bin/bash

while true; do
    clear
    echo "Choose an item: a, b or c"
    echo "a: Backup"
    echo "b: Display Calendar"
    echo "c: Exit"
    #-s 標準入力から変数に代入する
    read -sn1

    case "$REPLY" in
        a) tar -czvf ../backup.tgz ../bin;;
        b) cal;;
        c) exit 0;;
    esac
    read -n1 -p "Press any key to continue"
done
