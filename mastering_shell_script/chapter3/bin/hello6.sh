#!/bin/bash
#引数が0である場合、名前をプロンプトを通して入力させる
if [ "$#" -lt 1 ] ; then
    read -p "Enter the name: "
    name=$REPLY
else
    name=$1
fi

echo "Hello $name"
exit 0