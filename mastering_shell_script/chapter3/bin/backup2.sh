#!/bin/bash
# Author: Toraneko0101

read -p "Choose H,M or L compression " file_compression
read -p "Which directory do you want to back up " dir_name

test -d "./$dir_name" || mkdir -m 700 "./$dir_name"
backup_dir="./$dir_name"

#圧縮方法
tar_l="-cvf $backup_dir/b.tar --exclude $backup_dir ./"
tar_m="-czvf $backup_dir/b.tar.gz --exclude $backup_dir ./"
tar_h="-cjvf $backup_dir/b.tar.bzip2 --exclude $backup_dir ./"

if [ "$file_compression" = "L" ]; then
    tar_opt=$tar_l
elif [ "$file_compression" = "M" ]; then
    tar_opt=$tar_m
else
    tar_opt=$tar_h
fi
tar $tar_opt
exit 0