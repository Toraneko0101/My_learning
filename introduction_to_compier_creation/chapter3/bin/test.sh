#!/bin/bash
assert(){
    compiler="$1"
    expected="$2"
    input="$3"

    "$compiler" "$input" > tmp.s
    cc -o tmp tmp.s
    ./tmp
    actual="$?"

    if [[ "$actual" == "$expected" ]]; then
        echo "$input => $actual"
    else
        echo "$input => $expected expected, but got $actual"
        exit 1
    fi
}

file=""
if [[ -z $1 || ! -f $1 ]]; then
    read -p "please enter object file: " file
else
    file="$1"
fi
assert "$file" 0 0
assert "$file" 42 42

echo OK