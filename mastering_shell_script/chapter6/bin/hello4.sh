#!/bin/bash

file="test.txt"
IFS=$'\n'
for var in $(cat $file); do
    echo " $var"
done