#!/bin/bash
read -p "May I ask your name:" name
echo "Hello $name"
read -sn1 -p "Press any to exit"
echo
echo $REPLY
exit 0
