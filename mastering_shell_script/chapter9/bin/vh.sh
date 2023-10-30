#!/bin/bash

read -p "target_file: " target


if [ ! -f "$target" ]; then
    echo "${target}は通常ファイルではありません"
    exit 1
fi

output="template.txt"

sed -E '/^(\s*#|$)/d;'  "$target" > "$output"
buf=$(sed -n '/^\s*#ServerName/p' "$target")
sed -i "1a\\${buf}" "$output"
sed -i "s/^\s#/\t/" "$output"