#!/bin/bash

: << "COMMENT"
Author: @Toraneko0101
Web: https://github.com/Toraneko0101

バックアップするファイルと場所を入力するよう促すスクリプト
ファイルはカレントの指定したディレクトリにバックアップする

Last Edited: 25/10/2015

COMMENT

read -p "Which file types do you want to backup " file_suffix
read -p "Which directory do you want to backup to " dir_name
#指定したディレクトリが存在していなければ作成
#-m <permission> : permissonを指定
test -d ./$dir_name || mkdir -m 700 ./$dir_name

# findは検索基準にマッチするカレントのファイルをコピーする
# -path, -prune -oでバックアップディレクトリをバックアップから除外している

find ./ -path ./$dir_name -prune -o \
 -name "*$fine_suffix" -exec cp {} ./$dir_name/ \;

exit 0