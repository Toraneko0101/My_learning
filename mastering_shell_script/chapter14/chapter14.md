#　bashスクリプトの代わりとしてのPython

- 補足
```
code <file_name>でterminalからfileが開ける
```
```
REPL: read-eval-print loopと呼ばれるコンソールにアクセス
    そこにPythonのコードを入力し、システムと対話する

Python
    interpreter
    RAD:rapid application development:高速アプリ開発が目的
    そのため構文が明解
```
- version表示
```
>>> import sys
>>> sys.version
'3.10.12 (main, Jun 11 2023, 05:26:28) [GCC 11.4.0]'
```
- ありがた～い教えの表示
```
>>> import this
```

# 14.2 Hello World
```py
#!/usr/bin/python3

print("Hello World")
```

# 14.3 Pythonでの引数
```
sys.argv[0]:
    スクリプト名
引数の数は常に1以上になる
```
# 14.4 引数の引き渡し
```py
#!/usr/bin/python3

import sys
if len(sys.argv) > 1:
    print(f"Hello {sys.argv[1]}")
```

# 14.6 重要な空白
```
インデントの話をしている
```

# 14.7 ユーザ入力の読み取り
```
input()
int(input())
map(int, input().split())
list(map(int, input().split()))
```

# 14.8 Pythonを使ってファイルに書き出す
```py
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
```

# 14.9 文字列の操作
```py
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
```

# 14.11 練習問題
- 14-1
```
8
```

- 14-2
```
importする
```

- 14-3
```
2つ
```