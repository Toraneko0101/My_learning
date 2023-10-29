#!/bin/bash

for (( i=1; i<=3; i++)); do
    echo "First loop $i"
    for (( j=1; j<=3; j++)); do
        echo "Second loop $j"
    done
done