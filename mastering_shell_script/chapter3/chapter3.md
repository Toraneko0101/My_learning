# 0. 条件の付加

# 3.1 コマンドラインリストを用いたシンプルな決定回路
- 概要
```
test: 終了ステータスで真偽値を返すコマンド
コマンドラインリスト: ANDまたはORの表記法を使って結合された2つ以上の文
```
- 例1(コード)
```
$ test $PWD == $HOME || cd $HOME
```
- 例1(説明)
```
カレントがユーザのホームディレクトリでなければ、ホームに移動する
```
- 例2(コード)
```
$ who | grep miss > /dev/null 2>&1 && write miss $(tty) < message.txt
```

- 例2(説明)
```
who : 
    ログインしているユーザをリスト表示
who | grep miss :
    whoの結果をgrepに渡し、目的ユーザ(今回の場合miss)がログインしていれば、真を返す。結果は/dev/nullで捨てる
 write user [ttyname]:
    特定の端末にメッセージを送信
    ttynameを指定しなくとも、該当ユーザの端末デバイスにメッセージは送信される
tty:
    ・標準入出力となっている端末デバイス
    ・オプションだが、明示すると送信先を制御できる（複数の端末で作業を行っているときなど）
・送信する内容については、ファイルからリダイレクトしている

※wsl2上でwhoは解釈されないようだ
    https://askubuntu.com/questions/1365678/who-command-produces-no-output-on-wsl2
```

# 3.2 リストを用いてユーザ入力を検証する

- コード
```bash
#!/bin/bash
echo "You are using $(basename $0)"
test -z "$1" || echo "Hello $1"
exit 0
```
- 説明
```
testは$1変数が0バイトか調べ、0でなければ入力値を表示する

test -z:
    -z STRING
            the length of STRING is zero
```

# 3.3 シェル組み込みコマンドのtestの使用
- testについて
```
・実行可能ファイルでもあるが、組み込みコマンドが先にヒットする
・常にtrue(0) or false(1)の終了ステータスを返す。評価すべき式を指定せずにtestコマンドを実行すると偽を返す

例)
    $ test || echo "Neko"
    Neko
```
- testの基本的な構文
```
基本: 
    test EXPRESSION
反転: 
    test ! EXPRESSION 
and:
    test EXPRESSION -a EXPRESSION
or:
    test EXPRESSION -o EXPRESSION

testは角括弧に置き換えられる

例)
$ [ 3 = 3 ] && echo "Neko"
Neko
```
## 3.3.1 文字列のテスト
- rootかどうかをテストする
```
$ test "$USER" = root
$ [ "$USER" = root ]

※角括弧の場合は、スペースに注意
・$USERも、=もrootもtestコマンドの引数なので、各々の間にスペースが必要なのだ。
・変数を""で囲んでいるのは、$USERが未定義の場合、test = rootとなってしまい、エラーが発生するから。囲むと空文字とは扱われない
```

- nオプション
```
-n: 文字列が値を持っているかどうかを調べられる
・2章で出てきた、while [ -n "$1" ]は、while test -n "$1"の省略形だったことがわかる。

※zオプションとの違い
    -z: 文字列の長さが0なら真(zero)
    -n: 文字列の長さが0より大きければ真
```
## 3.3.2 整数のテスト
```
例)
    $ test "$#" -gt 0

-eq 等しいか否か
-ge >=
-gt >
-le <=
-lt <
-ne 等しくないか
```
## 3.3.3 ファイルの種類のテスト
- 概要
```
例) test -e hello4.sh || touch hello4.sh

-d: ディレクトリであるかどうかテスト
-e: ファイルが存在するかテスト
-x: ファイルが実行可能かテスト
-f: ファイルが通常のファイルかテスト
-r: ファイルが読み取り可能かテスト
-p: ファイルが名前付きパイプであるかテスト
-b: ファイルがブロックデバイス(ハードデバイス,USBメモリ,etc...)であるかテスト

file1 -nt file2
    1が2より新しいかテスト(newer than)
file1 -ot file2
    1が2より古いかテスト
-c: ファイルがキャラクターデバイス(キーボードやマウス)かどうかテスト
-h(-L): ファイルがシンボリックリンクであるか
-O: ファイルの所有者がログイン中のユーザかどうか
```
- manとhelpについて
```
・manは外部コマンドの使い方を表示
・helpはbash組み込みコマンドの使い方を表示
    man mv -> 表示可能
    help mv -> 表示不可
    これはmvが外部コマンドだから

・どうしてシェルにコマンドを組み込まない（全てをビルトインコマンドにしない）のか
    ・シェルを小さくシンプルに保つため
    ・起動速度の観点で優先されると思われるものは組み込んだ

・注意点
    外部コマンドのパスは環境に依存するのでPATHから探す
```
# 3.4 ifを使って条件文を作成
- コード
```bash
#!/bin/bash
# 引数が0である場合、終了ステータスを1とする
if [ "$#" -lt 1 ] ; then
    echo "Usage: $0 <name>"
    exit 1
fi
echo "Hello $1"
exit 0
```
# 3.5 elseを用いてifを拡張
- コード
```bash
#!/bin/bash
#引数が0である場合、名前をプロンプトを通して入力させる
if [ "$#" -lt 1 ] ; then
    read -p "Enter the name: "
    name=$REPLY
else
    name=$1
fi

echo "Hello $name"
exit 0
```

# 3.6 testコマンドを伴うif文

## 3.6.1 文字列のチェック
```
※エスケープしているのはリダイレクトを防ぐため
※大小は文字コード依存
※スペースを含んだ文字列を使う場合は、コマンドと勘違いされないよう引用符で囲む必要がある
否定:if [ "$str1" != "$str2" ]
小さい:if [ "$str1" \< "$str2" ]
大きい:if [ "$str1" \> "$str2" ]
not Zero: if [ -n "$str1" ]
Zero: if [ -z "$str1" ]
```
## 3.6.2 ファイルやディレクトリのチェック
- コード
```bash
#!/bin/bash

if [ "$#" -lt 1 ] ; then
    read -p "Enter the directory: "
    mydir=$REPLY
else
    mydir=$1
fi

if [ -d "$mydir" ]
then
    echo "$mydirというディレクトリは存在します"
else
    echo "$mydirというディレクトリは存在しません"
fi

exit 0
```

## 3.6.3 数値のチェック
```
上記の例と同一なので略
```

## 3.6.4 テストの結合
```
&&や||を使う
```
- コード
```bash
#!/bin/bash

if [ 12 -lt 21 ] && [ -n "Neko" ]; then
    echo "テスト成功"
else
    echo "テスト失敗"
fi
```

# 3.7 elifで条件に対応する
```
ユーザが複雑な操作をコマンドから簡単に実行できるようにするために、スクリプトを複雑に書く。
```
## 3.7.1 elifを用いてbackup2.shを作成
- 方針
```
tarコマンドを用いる
圧縮レベルをオペレータに選択させる
H -> bzi2
M -> gzip
L -> 圧縮せずにtarアーカイブを作成
```
- コード
```bash
#!/bin/bash
# Author: Toraneko0101

read -p "Choose H,M or L compression " file_compression
read -p "Which directory do you want to back up " dir_name

test -d "./$dir_name" || mkdir -m 700 "./$dir_name"
backup_dir="./$dir_name"

#圧縮方法
tar_l="-cvf $backup_dir/b.tar --exclude $backup_dir ./"
tar_m="-czvf $backup_dir/b.tar.gz --exclude $backup_dir ./"
tar_h="-cjvf $backup_dir/b.tar.bzip2 --exclude $backup_dir ./"

if [ "$file_compression" = "L" ]; then
    tar_opt=$tar_l
elif [ "$file_compression" = "M" ]; then
    tar_opt=$tar_m
else
    tar_opt=$tar_h
fi
tar $tar_opt
exit 0
```
- 説明
```
tar -c [-f ARCHIVE] [OPTIONS] c
-c 新しいアーカイブを作成
-v verbose
[-f ARCHIVE ]アーカイブファイルの名前を指定
--exclude 特定のファイルやディレクリをアーカイブから除外(今回はbackup自身)
[FILE...] アーカイブ対象のファイルを指定
-z gzip形式で圧縮
-j bzip2形式で圧縮
```

# 3.8 case文の使用
- 概要
```
[a-f]: 文字の範囲は扱える
3: 整数の範囲は扱えない
;;: マッチするものが見つかると、;;までのすべての文を実行する
```
- 学生の成績を評価するスクリプト(コード)
```bash
#!/bin/bash

#学生の成績を評価するスクリプト

if [ ! "$#" -eq 2 ]; then
    echo "<学生名> <成績>を指定してください"
    exit 2
fi

case "${2^^}" in #パラメータ展開を用いて、入力$2を大文字にする
    [A-C]) echo "$1 は優れた生徒です"
    ;;
    [D]) echo "$1 はもう少し頑張る必要があります"
    ;;
    [E-F]) echo "$1 は来年もっと頑張りましょう"
    ;;
    *) echo "$1 $2 について成績を評価することができません"
    ;;
esac
```
- 学生の成績を評価するスクリプト(説明)
```
${2,,}: $2の値を小文字にする
${neko^^}: $nekoの値を大文字にする
```
- caseの補足
```bash
#以下のような指定・判断も可能
# パターンは変数に入れて使用することもできる。その際は変数を引用符で囲むか否かで動作が異なってくる

pattern="*day"
case "$1" in
    orange)
        ;;
    apple | banana)
        ;;
    ?AT)
        #任意の1文字の後にATが続くもの
        ;;
    "*day")
        #引用符で囲むと文字列自体にマッチする
        ;;
    [A-Z]*)
        #先頭が大文字で始まる任意の文字列
        ;;
    [!0-9]*)
        #先頭が数字で始まらない任意の文字列
        ;;
    $pattern)
        #任意の長さで末尾がdayで終わる文字列にマッチ
        ;;
    "$pattern")
        #*dayという文字列にマッチ
        ;;
    '$pattern')
        #$patternという文字列にマッチ
        ;;
    *)
        ;;
esac
```

# 3.9 レシピ：grepのフロントエンドを作成する

# 3.11
```
3-1
A. False

3-2
どちらも正しいように見える

3-3
-gt -ge -ne

3-4
True
```