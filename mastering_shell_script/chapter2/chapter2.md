# 0 インタラクティブなスクリプトの作成

# 2.1 オプション付きのechoの使用
- 概要
```
・echoコマンドは、ファイルのフルパスを指定しない限り、組み込みコマンドが使われる
・テキスト文字列を指定しない場合、echoはstdoutに改行だけを出力する
```
- ファイルのフルパスを指定する
```
$ which <command_name>
```
- 改行を抑制する
```
・echo -e "\x21" エスケープシーケンスを解釈する
・\c これ以降の文字を解釈しない

つまり、以下のようにすると改行は出力されなくなる

echo -e "neko\c"

※ -nで改行を防ぐこともできる
```

# 2.2 readを使った基本的なスクリプト
- 概要
```
・改行を抑制し、対話的なスクリプトを作成する
```
- 対話的なスクリプト(code)
```bash
#!/bin/bash
echo -n "Hello $(basename $0)! May I ask your name:"
read
echo "Hello $REPLY"
exit 0

```
- 対話的なスクリプト(説明)
```
read: stdinから受け取った内容を1行単位で変数に入れる
$REPLY: 変数名を省略した場合、readの出力はREPLYにsetされる
```

# 2.3 スクリプトのコメント
- 概要
```
・shebangも本来コメント。シェルによって評価されない
・Linuxカーネルがファイルの先頭を調べ、#!で判別
・スクリプトであると解釈すればshebang全体を読み取り、そのスクリプトをどのコマンドインタプリタに渡すべきかを理解する
```

- 疑似的に複数行のコメントのように記述(ヒアドキュメント)
```bash
#!/bin/bash

echo "複数行のコメント"

: <<"COMMENT"
Author: Toraneko
Date: 25/10/2023
overview: ヒアドキュメントを試している
COMMENT
```
- ヒアドキュメント(説明)
```
・ヒアドキュメント：コマンドに複数行の文字列を標準入力として与える
・上記はこれを転用したもの
・終端文字列までの行についてコマンドは読み込む
・終端文字列は行の先頭にある必要がある
・インデントをしたい場合は<<-を使用し、スペースではなくタブを用いる
・コロン(:)は何もしない組み込みコマンド
・:は省略もできるが、その場合はbash -xで、:コマンドが実行されたという履歴が送出されない
・ヒアドキュメントの<<の右にある文字列を引用符なしにすると変数の展開が行われるので注意
```

# 2.4 readプロンプトを用いてスクリプトを拡張する

- echoを使わずプロンプトを作成する(説明)
```
read -p <prompt> <val>
    -p 入力前に表示するプロンプトの文字を設定可能
    <val> 指定しないと値はREPLY変数に保存される
    readのプロンプトではメッセージ内のコマンドは評価されない

※ ksh93, mksh, zshでは-pの代わりに?を使用
```
- echoを使わずプロンプトを作成する(code)
```bash
#!/bin/bash
read -p "May I ask your name:" name
echo "Hello $name"
exit 0
```

# 2.5 入力文字数を制限する

- 説明
```
read -n2: 
    ・続行する前に受け付ける文字数を2文字に指定できる
    ・任意のキーを2回押すと、次の処理に移行する
    ・指定しない場合、Enterキーでしか次に行かない
```
- コード
```bash
#!/bin/bash
read -p "May I ask your name:" name
echo "Hello $name"
read -n2 -p "Press any key to exit"
echo
exit 0
```

# 2.6 入力テキストの可視性を制御する

- 画面上にテキストを表示したくないとき(説明)
```
-s : silentを意味する。テキスト非表示
```
- 画面上にテキストを表示したくないとき(コード)
```bash
#!/bin/bash
read -p "May I ask your name:" name
echo "Hello $name"
read -sn1 -p "Press any to exit"
echo
echo $REPLY
exit 0

```

# 2.7 オプションの受け渡し
- 概要
```
オプション：前に1つのハイフンが付いた文字。$1等で表示も可能
```
- オプションを正しく使う(code)
```bash
#!/bin/bash
while [ "$1" != "" ]
do
    case "$1" in
        -a) echo "-a option used" ;;
        -b) echo "-b option used" ;;
        -c) echo "-c option used" ;;
        *) echo "Option $1 not and option" ;;
    esac
    shift
done
```
- オプションを正しく使う(説明)
```
shift: 引数を左へ1つずらす
"$1" != "": $1に何も入力されていないなら終了
;; コマンドの終わりを意味する
```

## 2.7.1 オプションとパラメータを区別し、同時に渡す

- コード
```bash
#!/bin/bash

#option
while [ -n "$1" ]
do
    case "$1" in
        -a) echo "-a option used" ;;
        -b) echo "-b option used" ;;
        -c) echo "-c option used" ;;
        --) shift
            break ;;
        *) echo "Option $1 not and option" ;;
    esac
    shift
done

#param
num=1
for param in $@
do
    echo "#$num: $param"
    num=$(( $num + 1 ))
done


```

- 説明
```
・--と入力された場合、shiftで1つずらしてからbreakでwhileを抜ける
・shiftを行っても、$0はずれない
・$@: $*との相違点は、二重引用符で囲んだ場合の展開のされ方。$*の場合、"-a -b -c"となるが、$@なら"-a" "-b" "-c"と個別に展開される。
・shift後について評価しているので、$
・$(( num + 1 )): 変数に対する四則演算
while [ -n "$1" ]: $1が空でなければloopを続ける
```

## 2.7.2 オプションの値を読み取る

- 入力
```
$ ./option_test.sh -a -b 20 -c
```
- コード
```bash
#!/bin/bash

#オプションに紐づいて受け渡す数の分だけ、shiftで引数をずらしている
#option

while [ -n "$1" ]
do
    case "$1" in
        -a) echo "-a option used" ;;
        -b) param="$2"
            echo "-b option passed, with value $param"
            shift ;;
        -c) echo "-c option used" ;;
        --) shift
            break ;;
        *) echo "Option $1 not and option" ;;
    esac
    shift
done
#param
num=1
for param in $@
do
    echo "#$num: $param"
    num=$(( $num + 1 ))
done

```
- getoptsについて
```
・ユーザからoptionを取得するためのbashの組み込みコマンド
・2文字以上のoptionをサポートしていない
・getoptの場合は、2文字以上のoptionをサポートしているが、bashの組み込みコマンドではない
```

# 2.8 標準的であること
- 標準的なoption体系について
```
-a : 全ての項目をリスト表示(allから)
-c : 全ての項目の数を取得(countから)
-d : 出力ディレクトリを指定する(directoryから)
-e: 項目を展開する(expandから)
-f: ファイルを指定(fileから)
-h: ヘルプを表示(helpから)
-i: 大文字と小文字を区別しない(ignore caseから)
-l: テキストをリスト表示しない(listから)
-o: 出力をファイルに送る(outputから)
-q: サイレントモードにする。ユーザに尋ねない(quietから)
-r: 再帰的な処理を行う(recursionから)
-s: ステルスモードを使用(stealth)
-v: 冗長(詳細)モードを使用(verbose:詳細)
-x: 実行可能ファイルを指定(executeの2文字目)
-y: ユーザの確認なしに実行。(yes?)
```

# 2.9 簡単なスクリプトを使って理解を深める

## 2.9.1 スクリプトを用いたバックアップ
- コード
```bash
#!/bin/bash

: << "COMMENT"
Author: @Toraneko0101

バックアップするファイルと場所を入力するよう促すスクリプト
ファイルはカレントの指定したディレクトリにバックアップする

Last Edited: 25/10/2015

COMMENT

read -p "Which file types do you want to backup " file_suffix
read -p "Which directory do you want to backup to " dir_name
#指定したディレクトリが存在していなければ作成
#-m <permission> : permissonを指定
test -d ./$dir_name || mkdir -m 700 ./$dir_name

# findは検索基準にマッチするカレントのファイルをコピーする
# -path, -prune -oでバックアップディレクトリをバックアップから除外している

find ./ -path ./$dir_name -prune -o \
 -name "*$fine_suffix" -exec cp {} ./$dir_name/ \;

exit 0
```

- 補足
```
find :
     fileやdirを検索したいときに利用
-path : 
    ファイルのパスが一致しているファイルを検索
-prune: 
    条件に該当するものを見つけ、真を返す
-path ./$dir_name -prune: 
    指定されたディレクトリか否か評価。今回の場合、バックアップディレクトリが見つかったら真を返す
-o : 
    or。つまり、-pathの条件に当てはまる場合、短絡評価がなされ、-name以降が評価されない

-name : 
    ファイルの名前が一致しているファイルを検索
-exec : 
    findで見つかった各ファイルに対して実行するコマンドを指定
    (実行結果を他のコマンドに渡す -exec echo {}ならファイル名を表示)
{} : 
    findで見つかったファイルのパスに置き換え
cp {} ./$dir_name/: 
    見つかったファイルを指定したバックアップディレクトリにコピー
```

## 2.9.3 サーバへの接続(ping)
- 概要
```
・pingコマンドを3回だけ繰り返すように変更
・動作していなければServer Deadと報告
```
- コード
```bash
#!/bin/bash

: << "COMMENT"

Author: @Toraneko0101
指定したサーバにpingを送るスクリプト

Last Edited: 25/10/2015
COMMENT

read -p "Which server should be pinged " server_addr
ping -c3 $server_addr 2>&1 > /dev/null || echo "Server Dead"

```
- 説明
```
ping -c3: pingの回数を設定
2>&1 標準出力も標準エラー出力も区別しない
/dev/null: 投入された入力を捨て去る

pingが失敗したら、右式が実行される

※ 2>&1 > /dev/null
・リダイレクトを複数指定した場合、左から順番に評価される
・> /dev/null 2>&1にした場合、標準出力は捨てられ、標準エラー出力を、標準出力として出力しようとするが、標準出力の行き先が/dev/nullなので、結果として何も出力されなくなる
```

## 2.9.4 サーバへの接続(SSH)
- 概要
```
・サーバアドレスとユーザ名を入力するよう促す
・入力内容をSSHクライアントに渡す
```
- コード
```bash
#!/bin/bash

# Author: @Toraneko0101
# ssh接続のための情報を入力する
# Last Edited: 25/10/2023

read -p "Which server do you want to connect to: " server_name
read -p "Which username do you want to use: " user_name
ssh ${user_name}@server_name
```
- 説明
```
ssh ログイン名@接続先
```

## 2.9.5 サーバへの接続(MySQL/MariaDB)
- コード
```bash
#!/bin/bash

# Author: @Toraneko0101
# Last Edited: 25/10/2023

read -p "MySQL User: " user_name
read -sp "MySQL Password: " mysql_pwd
echo
read -p "MySQL Command: " mysql_cmd
read -p "MySQL Database: " mysql_db
mysql -u "$user_name" -p$mysql_pwd $mysql_db -Be"$mysql_cmd"
```
- 説明
```
mysql [OPTIONS] [database] [command]
-u : ユーザ名
-p : パスワード。パスワードは-pの直後にスペースなしで指定する。スペースを空けるとほかのコマンドかもしれないと思われる
データベース名: 単に記述。-Dがなくとも正しく解釈されるのは、位置引数として解釈されているため
-B: 結果をタブ区切りで表示
-e: 指定したクエリを実行。dbに対してクエリを実行するのでこの位置
```

## 2.9.6 ファイルの読み取り
- code
```bash
#!/bin/bash

while read line
do
    echo $line
done < "$1"
```
- 説明
```
1. 指定したファイルの内容をwhileコマンドにリダイレクト
2. readコマンドを用いて内容を1行ずつ読み取る
```

# 2.10 まとめ
```
・シェルスクリプト内で間接的に指定させると、パスワードがコマンドライン履歴に保存されるような事態を避けられる
・historyで見れるのは、実行ファイルだけ
```

# 2.11 練習問題

```
2-1
A. 3つ

2-2
A.
-a
-b50
-c

2-3
A.
1. 引数の数なので4つ
2. Mokhtar
※shiftを行っても、ファイル自身はずれない
```
