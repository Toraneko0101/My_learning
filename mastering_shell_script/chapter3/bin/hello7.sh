#!/bin/bash

if [ "$#" -lt 1 ] ; then
    read -p "Enter the directory: " mydir
else
    mydir=$1
fi

if [ -d "$mydir" ]
then
    echo "$mydirというディレクトリは存在します"
else
    echo "$mydirというディレクトリは存在しません"
fi

exit 0