#!/bin/bash

#学生の成績を評価するスクリプト

if [ ! "$#" -eq 2 ]; then
    echo "<学生名> <成績>を指定してください"
    exit 2
fi

case "${2^^}" in #パラメータ展開を用いて、入力$2を大文字にする
    [A-C]) echo "$1 は優れた生徒です"
    ;;
    [D]) echo "$1 はもう少し頑張る必要があります"
    ;;
    [E-F]) echo "$1 は来年もっと頑張りましょう"
    ;;
    *) echo "$1 $2 について成績を評価することができません"
    ;;
esac
