#!/usr/bin/python3

str = "Welcome to python scripting world python"
print(str.find("scripting")) #検索
print(str[::2]) #部分文字列の取得
str2 = str.replace("python", "shell")
str3 = str.upper()
str4 = str2.title()
print(str2)
print(str3)
print(str4)