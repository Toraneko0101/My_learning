#!/usr/bin/python3

import sys
cnt = len(sys.argv)
name = ""

if cnt == 1:
    name = input("Enter the name: ")
else:
    name = sys.argv[1]

with open("./script.log", "a") as f:
    f.write(f"Hello {name} \n")
    