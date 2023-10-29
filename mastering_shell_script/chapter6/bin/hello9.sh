#!/bin/bash

for f in /home/toraneko/*; do
    [ -d "$f" ] || continue
    dir_name="$dir_name $f"
done
echo $dir_name
