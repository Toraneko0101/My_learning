# 7. 関数の作成

# 7.1 関数の導入
- 概要
```
・関数は名前付きの要素としてメモリ内に存在するコードのブロック
・関数はシェルの環境内でも作成可能
・declare -Fでシェル環境内の関数を表示可能
・type <funcname>で関数の定義が閲覧可能
```
- 説明
```
declare
    変数の値や属性を設定したり表示するコマンド
    typesetがbashではdeclareの別名

```
- 補足
```
// 例えばtype quoteで以下の様に表示される
//　渡された入力パラメータを単一引用符で囲んでいる
quote () 
{ 
    local quoted=${1//\'/\'\\\'\'};
    printf "'%s'" "$quoted"
}

------
local quoted
    quotedというローカル変数を宣言
${1//\'/\'\\\'\'}:
    これはbashのパラメータ拡張
    // 置換対象の文字列全てを置換する
    \': 置換対象
    \'\\\'\': つまるところ'が'\''に置換される
printf "'%s'" "$quoted"
    quotedに''を付け加える

quote "Neko'suki"
'Neko'\''suki'
```
- 関数の構文
```
function-name(){
    <code>
}

/*duplicate*/
function <function-name>{
    <code>
}

※6章の最後でやった、{}はコードブロックであり、まとめて実行できることを思い出す
```

- システム情報を表示するための簡単な関数(コード)
```bash
#!/bin/bash

show_system(){
    echo "The uptime is:"
    uptime
    echo
    echo "CPU Detail:"
    lscpu
    echo
    echo "User"
    whoami
}

show_system > login.txt
```
- システム情報を表示するための簡単な関数(説明)
```
・unsetやシェルを閉じると消える。
・関数を持続させるためには自分のユーザアカウントのログインスクリプトに追加する
・関数を実行するには、単に関数名を入力する
・ファイルを実行した場合は、別プロセスでシェルが開き、終わると閉じるので、typeコマンドで関数名を押しても一覧にない
```

# 7.2 関数へのパラメータの引き渡し
```
sed
    設定ファイルを編集して、コメント行や空の行を削除可能
    上書き保存は以下のコマンド
        $ sed -i.bak '/^\s*#/d;/^$/d' <filename>

    sed i.bak
        ファイルを編集し、.bakという拡張子を持つバックアップファイルを作成。元ファイルは<filename>.bakでアクセス可能
    
    /^
        行の先頭にマッチ
    \s*
        任意の数の空白文字
    #/
        通常の#記号
    ^\s*#
        コメントで始まる行、または空白文字とコメントで始まる行
    d
        マッチする行を削除する
    ;
        行の区切り目
    ^$/d
        空の行を削除。$は行末なので
    
```
- 今回はntp.confをcopyして実行した
```bash
#!/bin/bash

is_file(){
    if [ ! -f "$1" ]; then
        echo "$1 does not seem to be a file"
        exit 2
    fi
}

clean_file(){
    is_file "$1"
    #実行結果をBEFOREに代入
    BEFORE=$(wc -l "$1")
    echo "The file $1 starts with $BEFORE"
    sed -i.bak '/^\s*#/d;/^$/d' "$1"
    AFTER=$(wc -l "$1")
    echo "The file $1 is now $AFTER"
}

read -p "Enter a file to clean:"
#第一引数に代入
clean_file "$REPLY"
exit 1


# Enter a file to clean:ntp.conf
# The file ntp.conf starts with 60 ntp.conf
# The file ntp.conf is now 16 ntp.conf

```
- 説明
```
wc -l
    改行の数を表示する(line)
-m
    文字数
-c(--bytes)
    バイト数
-w
    単語数
-L
    最も長い行の長さ
```

## 7.2.1 配列の引き渡し
- コード
```bash
#!/bin/bash

myfunc(){
    # ()は配列の記号。サブシェルではない。
    arr=("$@") #これを$1とすると、最初の要素だけが返される
    echo "The array from inside the function: ${arr[*]}"
}

test_arr=(1 2 3)
echo "THe original array is: ${test_arr[*]}"
myfunc "${test_arr[@]}"
```
- 説明
```
・引数を配列として使うために("$@")を使っている
・関数の引数を指定する際に、[@]を指定したうえで、二重引用符で囲んでいる
・[*]で全体参照している。配列の要素を1つで扱うのが@と違う点
・forループなどで参照すると違いが分かる
```

# 7.3 変数のスコープ
```
デフォルトでは、関数内で宣言した変数はグローバル変数
localコマンドを使うことで、ローカル変数を宣言できる

※ローカル変数のスコープはローカル変数を宣言した関数以外に、素の関数から呼び出した関数も含まれる
※つまり、呼び出された関数から呼び出し元の関数のローカル変数の値を参照したり変更したりできる。入れ子にする際は注意。つまり、ブロックの中から外を参照できるわけか
```
- コード
```bash
#!/bin/bash

myvar=30
myfunc(){
    local myvar=10
}
myfunc
echo $myvar
```

# 7.4 関数から値を返す
```
return:
    ・終了ステータスを返す(0~255)
    ・引数を省略すると、returnの直前に実行されたコマンドの終了ステータスが使われる
    ・関数の呼び出し側は$?で終了ステータスを受け取る
    ・if文でtestコマンドの引数に$?を使う場合は、$?の値が上書きされるのを防ぐため、あらかじめ別のパラメータに代入すること。
echo:
    標準出力に出力する
```
- コード
```bash
#!/bin/bash

check_file(){
    if [ -f "$1" ]; then
        return 0
    elif [ -d "$1" ]; then
        return 1 #directory
    else
        return 2 #deviceファイル
    fi
}

if [ -z "$1" ]; then
    echo "Usage: $0 file"
    exit 1
fi

check_file "$1"
status=$?
if [ $status = 0 ]; then
    echo "$1 is a regular file"
elif [ $status = 1 ]; then
    echo "$1 is a directory"
else
    echo "$1 is a device file"
fi
```
- 大文字小文字変換(コード)
```bash
#!/bin/bash

to_lower(){
    input="$1"
    output=$( echo $input | tr [A-Z] [a-z])
    echo $output
}

while true; do
    read -p "Enter c to continue or q to exit:"
    REPLY=$(to_lower "$REPLY")
    if [ $REPLY = "q" ]; then
        break
    fi
done

echo "Finished"
```
- 大文字小文字変換(説明)
```
tr [A-Z] [a-z]
    第一引数から第二引数へ変換
REPLY=$(to_lower "$REPLY")
    ・関数から戻ってきた標準出力を、受け取り、REPLYに代入
    ・代入しているので出力は行われない
    ・コマンド置換
```

# 7.5 再帰関数
- コード
```bash
#!/bin/bash

calc_factorial(){
    if [ $1 -eq 1 ]; then
        echo 1
    else
        local var=$(( $1 - 1 ))
        #標準出力が$()に返る
        local res=$(calc_factorial $var)
        echo $(( $res * $1 ))
    fi
}

read -p "Enter a numer: " val
factorial=$(calc_factorial $val)
echo "The factorial of $val is : $factorial"
```
- 参考(pythonの再帰)
```bash
#!/usr/bin/env python3

def gcd(x,y):
    if y==0:
        return x
    else:
        return gcd(y, x%y)

print(gcd(3,24))
```

# 7.6 メニューでの関数の使用
- 6章で書いたもの
```bash
#!/bin/bash

while true; do
    clear
    echo "Choose an item: a, b or c"
    echo "a: Backup"
    echo "b: Display Calendar"
    echo "c: Exit"
    #-s 標準入力から変数に代入する
    read -sn1

    case "$REPLY" in
        a) tar -czvf ../backup.tgz ../bin;;
        b) cal;;
        c) exit 0;;
    esac
    read -n1 -p "Press any key to continue"
done

```
- 書き換えたもの
```bash
#!/bin/bash

to_lower(){
    input="$1"
    output=$( echo $input | tr [A-Z] [a-z])
    echo $output
}

do_backup(){
    tar -czvf ../backup.tgz ../bin
}

show_cal(){
    #ncalが利用可能なら-wで週番号を表示する
    if [ -x /usr/bin/ncal ]; then
        command="/usr/bin/ncal -w -3"
    else
        command="/usr/bin/cal -3"
    fi
    $command
}

while true
do
    clear #画面をclear
    echo "Choose an item: a, b or c"
    echo "a: Backup"
    echo "b: Display Calender"
    echo "c: Exit"
    read -sn1 #標準入力から代入し、入力文字を表示しない
    REPLY=$(to_lower "$REPLY")
    case "$REPLY" in
        a) do_backup;;
        b) show_cal;;
        c) exit 0;;
    esac
    read -n1 -p "Press any key to continue"
done
```
- アイデア
```
read -tで制限時間つけれるなら、タイピングゲームとかできそう
```

# 7.7 まとめ
```
次章はsedについて
```

# 7.8 練習問題
- 7-1
```
1
$1は1番目の引数
$0はファイル自体
```
- 7-2
```
50
100
```
- 7-3
```
clean_file()
function clean_file
```

- 7-4
```
最終行に()は要らない
${}は参照。単純な参照の場合は、必ずしも囲む必要はないが、わかりやすい

echo ${array_name}でも最初の要素を返す
```

- 補足
```
Count
    ${#var}で変数の文字数カウント
    ${#list[*]}でlistの要素カウント

Slice
    ${var: 2}で2文字目までを除いで抜き出す
    ${var:0:3}で0文字目から3文字分を抜き出す

定義されている変数名を探す
    echo ${!h*}
    hoge

連想配列のキーと値を見る
    ※!を付ければkey,つけなければvalが見れる
    declare -A test_hash
    test_hash["hoge"]="hoge-val"
    test_hash["fuga"]="fuga-val"

    echo ${test_hash[*]}
    fuga-val hoge-val

    echo ${test_hash[*]}
    fuga-val hoge-val

文字列置換 ${param/pattern/replace}
    echo ${hoge}
    neko-mochi
    echo ${hoge/o/--}
    nek---mochi
文字列置換(replace_all) ${param//pattern/replace}
    echo ${hoge//o/--}
    nek---m--chi

※ #,%を使うことで、先頭や末尾以外は置換しないということもできる

その他
    ${param:-default} 変数本体には代入されない
        $ echo ${hoge}
        neko-neko-mochi
        $ echo ${hoge:-"hoge-default"}
        neko-neko-mochi
        $ unset hoge
        $ echo ${hoge:-"hoge-default"}
        hoge-default
        $ echo ${hoge}
    ${param:=default}
        デフォルト値が参照されると変数本体にも代入される
    ${param-default}
        unsetなどで変数未定義にするとデフォルト値
        空文字なら何も出ない
    ${param=default}
        unsetなどで変数未定義にするとデフォルト値
        空文字なら何も出ない
        デフォルト値が参照されると変数本体にも代入される
    ${param:?default}
        変数未定義時にエラー出力
    ${param:+default}
        変数定義時のみ代入
    ${param+default}
        変数定義時の未代入。本体には代入されない
        



大文字化 ^なら1文字目だけ。^^なら全て
    $ echo ${hoge^^} 
小文字化 ,なら1文字目だけ。,,なら全て
    $ echo ${hoge,,} 
反転
    ${var~}で先頭文字を反転(upper,lower)
    ${var~~}で全てを反転

strip(最短一致)
    hoge=neko-neko-mochi
    echo ${hoge#ne*-}
    neko-mochi
strip(最長一致)
    echo ${hoge##ne*-}
    mochi
※後方の場合は#が%になる

※配列にも適用可能
$ list=("hoge-value" "fuga-value")
$ echo ${list[@]%-value}
hoge fuga

```

- 補足2
```
・shell-scriptは途中のコマンドでエラーが送出されても、そのまま動き続ける

set -e
    終了ステータスによって中断処理を行う
set -u
    未定義の変数を使おうとしたときに中断
set +e
    一時的にset -eを無効

・行単位で、最後に実行したコマンドの終了ステータスのみが意味を持つので以下の様に書く
name="$(get_name)"
echo "Hello ${name}"
・条件文の場合は、set -eではなく、returnから終了ステータスを返すようにする。

```