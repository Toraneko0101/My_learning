#!/bin/bash
#Author: @Toraneko0101
usage="使用法: search.sh <ファイル> <検索文字列> <操作>"

if [ ! "$#" -eq 3 ]; then
    echo "$usage"
    exit 2
fi

[ ! -f "$1" ] && exit 3

case "$3" in
    [cC])
        mesg="$1 の中で $2 にマッチする行数を数える"
        opt="-c"
        ;;
    [pP])
        mesg="$1 の中で $2 にマッチする行を表示する"
        opt=""
        ;;
    [dD])
        mesg="$1 から $2 にマッチする行を除いてすべて表示"
        opt="-v"
        ;;
    *)
        echo "$1 $2 $3 を評価できません"
        exit 1
        ;;
esac

echo $mesg
#grep -c neko grade.sh
#grep neko grade.sh
grep $opt $2 $1
exit 0
