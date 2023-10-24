#!/bin/bash
myarr=(one two three four five)
unset myarr[1]
echo ${myarr[*]}
#unset myarr
