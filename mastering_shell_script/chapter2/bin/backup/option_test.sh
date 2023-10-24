#!/bin/bash

#option
while [ -n "$1" ]
do
    case "$1" in
        -a) echo "-a option used" ;;
        -b) param="$2"
            echo "-b option passed, with value $param"
            shift ;;
        -c) echo "-c option used" ;;
        --) shift
            break ;;
        *) echo "Option $1 not and option" ;;
    esac
    shift
done
#param
num=1
for param in $@
do
    echo "#$num: $param"
    num=$(( $num + 1 ))
done

