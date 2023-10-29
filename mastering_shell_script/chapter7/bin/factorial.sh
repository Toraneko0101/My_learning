#!/bin/bash

calc_factorial(){
    if [ $1 -eq 1 ]; then
        echo 1
    else
        local var=$(( $1 - 1 ))
        #標準出力が$()に返る
        local res=$(calc_factorial $var)
        echo $(( $res * $1 ))
    fi
}

read -p "Enter a numer: " val
factorial=$(calc_factorial $val)
echo "The factorial of $val is : $factorial"