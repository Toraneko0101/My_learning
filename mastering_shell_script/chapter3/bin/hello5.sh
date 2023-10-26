#!/bin/bash
#引数が0である場合、終了ステータスを1とする
if [ "$#" -lt 1 ] ; then
    echo "Usage: $0 <name>"
    exit 1
fi
echo "Hello $1"
exit 0