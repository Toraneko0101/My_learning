#!/bin/bash
OLDIFS="$IFS"
IFS="," #separator
#1行ごとにsep区切りで、product ,price, quantityに値を代入する
while read product price quantity; do
    #青色 4はitalic 47は背景白
    #
    echo -e "\e[4;34;47m$product \
            ========================\e[0m\n\
            Price : \t $price \n\
            Quantity : \t $quantity \n"
done < "$1"

IFS=$OLDIFS