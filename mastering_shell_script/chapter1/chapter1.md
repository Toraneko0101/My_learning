:# 1.1 技術要件
- 概要
```
- Bash Debugをインストール
```

# 1.2 Linuxのシェルの種類
- 概要
```
・Linuxはカーネル,シェル,GUIインターフェースなどのパーツで構成される
・シェルはユーザの入力を受け取り、カーネルに渡す？
----------
sh
    別名Bourneシェル
    70年代に作成
bash
    Bourne againシェル
    shと互換性あり
    /bin/shとして実行、ないしは--posixオプションを付けて実行すると、POSIX互換モードで動作する
ksh
    Kornシェル
    Bourneを拡張したもの
    shやbashと互換性あり

csh,tcsh
    構文がC言語に似ているシェル(csh)
    その拡張版(tcsh)

zsh,fish
    ターミナル上で対話的に使用する際の補完機能が強力
    ログインシェルとして人気がある
--------------
POSIX
    異なるOS間でアプリケーション互換性をサポートするべく、OSの標準のインタフェースと環境を定義した規格

```

# 1.3 bashスクリプトとは何か?
- 概要
```
・複数のコマンドを実行し、特定の作業を自動化する
・例 ls; pwd
・bashでユーザが入力するキーワードはすべてコマンド
・シェルはコマンド同士を結合させているともいえる

```
# 1.4　bashコマンドの階層

## 1.4.1 コマンドの種類

- type(コマンドの種類を表示)
```
$ type ls
ls is aliased to `ls --color=auto'
```
- typeの実行順
```
1. エイリアス
2. 関数
3. シェルの組み込みコマンド
4. キーワード
5. ファイル

つまり、実行可能ファイルとしてのlsが検索されるのは最後。今回の場合、エイリアスで色を補正してから表示していた。
```
- 特定のコマンドにマッチするものをすべて表示
```
$ type -a ls
ls is aliased to `ls --color=auto'
ls is /usr/bin/ls
ls is /bin/ls
```
- 類だけが必要な場合
```
$ type -t ls
alias
```
- 複数の例
```
$ type ls quote pwd do id
ls is aliased to `ls --color=auto'
quote is a function
quote () 
{ 
    local quoted=${1//\'/\'\\\'\'};
    printf "'%s'" "$quoted"
}
pwd is a shell builtin
do is a shell keyword
id is /usr/bin/id

補足：
    関数の場合、その定義を出力する
```

## 1.4.2 コマンドのパス

- 概要
```
・Linuxはプログラムのフルパスor相対パスが指定されると、環境変数PATHの中で実行可能プログラムをチェックする
・カレントであっても、それがPATHの中にない限り、検索されない
```
- Pathにカレントを追加する
```

$ export PATH=$PATH:.

補足:
    ・PATHはコロンで区切って表示する
    ・そのため既存のPATHにカレントを追加していることになる
```

- スクリプトを一階層に整理する  
```
補足:
    1. 環境変数PATHに$HOME/binを追加
    2. スクリプトは$HOME/binに作成する
    3. これらのスクリプトはファイルパスを必要としなくなる

手順:
    1. $ export PATH=$PATH:$HOME/bin
        $HOME/binにpath追加

    2. $ test -d $HOME/bin || mkdir $HOME/bin
        ディレクトリが存在していないときのみ、作成する

説明
    1. test -d : fileがディレクトリであれば真
    2. 真であれば短絡評価で終了
    3. 偽ならmkdirが実行される

```

- PATHにカレントを置くのが望ましくない理由
```
1. 攻撃者がマシン内に侵入する
2. 権限昇格を行うような攻撃プログラムを/tmp/lsにおき、pathの先頭に追加する
3. ユーザがlsを実行したときに、/bin/lsよりも/tmp/lsが優先されて実行される
4. PATHの末尾であったとしても、tmp/ksという名前で攻撃プログラムを置いたとき、typoで実行される可能性がある
```
# 1.5 スクリプトのためのテキストエディタの準備

## 1.5.1 vimの設定
```
$HOME/.vimrcに設定を追加

set showmode
    挿入モードであると分かるように

set nohlsearch
    検索した単語を強調表示しない

set autoindent
    改行時にインデントをそろえる

set tabstop=4
    タブでスペース4個分

set expandtab
    タブをスペースに変換

syntax on
    構文の強調表示を行う
```

## 1.5.2 nanoの設定
```
$HOME/.nanorcに以下を記載

set autoindent
set tabsize 4
include /usr/share/nano/sh.nanorc

補足
    最終行はシェルスクリプトにおける構文の強調表示
```

## 1.5.3 gedit
```
wsl2であり、使用する予定がないので略
```

# 1.6　スクリプトの作成と実行
```
自分はbinディレクトリをPATHに追加した
以降、説明がない限り、スクリプトはbinディレクトリに置く
```
## 1.6.1 Hello World!
- code
```bash
#!/bin/bash
echo "Hello World"
exit 0
```
- 説明
```
#/bin/bash
    ・シバン(shebang)と呼ばれる
    ・常にスクリプトの最初の行となる
    ・システムのインタプリタに対してスクリプトを実行するように指示する
    ・この行を書かないと、現在のシェルの中でコマンドが実行

    ※bashが/bin/bash以外にある時は#!/usr/bin/env bash等と書くことでインストール場所の違いを吸収できる

echo "Hello World"
    ・echoはシェルの組み込みコマンド
    ・標準出力STDOUTに書きだす
    ・STDOUT：標準ではディスプレイ画面

exit 0
    ・exitはシェルの組み込みコマンド
    ・スクリプトを終了するために使用
    ・終了ステータスが0でないときは、スクリプト実行時のエラーを意味する
```

## 1.6.2 スクリプトを事項する
- bashで直接実行
```
$ bash hello1.sh
```
- それ以外の場合は、実行権限を与える必要がある
```
$ chmod +x ./bin/hello1.sh
$ hello1.sh
```

## 1.6.3 終了ステータスをチェックする
- 概要
```
$ command1 || command2
-> command1の終了ステータスが0以外の時にcommand2を実行

$ command1 && command2
-> command1のstatusが0の時の未実行

```
- $? 変数で終了ステータスを明示可能
```
$ hello1.sh && echo $?
Hello World
0
```

## 1.6.4 一意の名前を確保する
```
・プログラム名ではなく、既存のエイリアスや関数キーワードなどと衝突していないか確かめること
・Linuxでは、拡張子はファイル名の一部になるため、独自性が高まる

$ type -a hello1.shなどで、コマンドが重複していない確認

```

## 1.6.5 Hello Dolly!
- 概要
```
・位置パラメータについて説明
```
- 引数を付けてスクリプトを実行
```
・スクリプトが引数を利用しない場合、引数は単に無視される
・エラーにはならない

$ hello1.sh fred
```
- 引数の識別子について
```
$0      スクリプトそのもの
$1      最初の引数
${10}   2桁以上の場合
$#      引数の数
$*      全ての引数
```
- 使用例(hello2.sh)
```bash
#!/bin/bash
echo "Hello $*"
exit 0
```
```
$ hello2.sh neko inu lion
Hello neko inu lion
```
- 正しい引用符について
```
echo "Hello $1" -> 変数に保管されている値を展開
echo 'Hello $1' -> $記号の値を展開しない

\$ -> 展開する必要のある変数と、文字通りの$を一緒に使いたい場合

ex)
    echo "Hello \$1"

バッククォート -> 後ほど
```

## 1.6.6 スクリプト名を表示する
- 完全なパスを表示
```bash
#!/bin/bash
echo "You are using $0"
echo "Hello $*"
exit 0
```
- スクリプトの名前だけを表示
```bash
#!/bin/bash
echo "You are using $(basename $0)"
echo "Hello $*"
exit 0
```
- 説明
```
echo "You are using $(basename $0)"

1. $(...)は内側のコマンドの結果を評価するために用いる
2. そのためまず、basename $0を実行する
3. basenameコマンド: パスから名前を抽出する
4. 無名の変数に結果を代入
5. ""で囲まれているため、変数の値が展開され、echoで表示される
```
- バッククォートでも同じことができる
```bash
#問題点は読みにくいこと
echo "You are using `basename $0`"
```

# 1.7 変数の宣言
```
スクリプト内で宣言できる変数
    ユーザ定義変数
    環境変数
```

## 1.7.1 ユーザ定義変数
- 変数宣言(code)
```bash
#!/bin/bash
name="Nekotarou"
age=9
total=13.4
echo $name
echo $age
echo $total
```
- 変数宣言(説明)
```
・間にスペースを入れない(シェルが変数をコマンドであると勘違いする)
・使用時は$がいる
```
- 配列(code)
```bash
#!/bin/bash
myarr=(one two three four five)
unset myarr[1]
echo ${myarr[*]}
#unset myarr
```
```
one three four five
```

- 配列(説明)
```
echo ${myarr[*]}
    全ての要素を表示
echo ${myarr[2]}
    3番目の要素を表示

unset myarr
    全ての要素を削除
unset myarr[1]
    2番目の要素を削除

・dashとashでは配列を使用できない
```

## 1.7.2 環境変数
- 概要
```
・$HOMEや$PATH,$USER等の変数はどこから来ているのか
・シェルが定義しており、環境変数と呼ばれる
・printenvでそれらを表示可能
・printenvに特定の環境変数を指定すると個別に表示可能
・環境変数は大文字で、ユーザ定義変数は小文字で宣言するのが慣習
・全ての環境変数はbashスクリプトの中で使用可能
```
- 例
```
$ printenv SHELL
/bin/bash
```

# 1.8 変数のスコープ
- 概要
```
・配列でない変数にunsetコマンドを使うと、素の変数は未定義になる
・変数のスコープは変数を作成したプロセスだけに限られる
・他のプロセスから変数にアクセスできるようにするにはexportコマンドを使用する
```
- exportコマンド(code)
```bash

#script1.sh
#!/bin/bash
name="Neko"
export name
./script2.sh
echo "script1:${name}"

#script2.sh
#!/bin/bash
name="Another name"
echo "script2:${name}"
```
```
script2:Another name
script1:Neko
```
- exportコマンド(説明)
```
script2.shで変数を変化させたとしても、元の変数には影響を及ぼさない
```

# 1.9 コマンド置換
- 概要
```
コマンド置換
    コマンドの実行結果を変数内に保管
方法
    バッククォート
    $()
```
- コマンド置換(code)
```bash
#!/bin/bash
cur_dir=`pwd`
echo $cur_dir
cur_dir=$(pwd)
echo $cur_dir
```

# 1.10 スクリプトのデバッグ
- 概要
```
bashに用意されているオプション
    -v スクリプトを1行ずつ評価
    -x コマンド実行時にコマンドを表示(条件分岐の選択を知るために役立つ)
```
- 実行例(-v)
```
#!/bin/bash
echo "You are using $(basename $0)"
You are using hello2.sh
echo "Hello $*"
Hello neko
exit 0
```
- 実行例(x)
```
++ basename hello2.sh
+ echo 'You are using hello2.sh'
You are using hello2.sh
+ echo 'Hello neko'
Hello neko
+ exit 0
```
- vscodeでデバッグ
```
・bash-debugという拡張機能を入れる
・launch.jsonを作成

・breakpointを作成
・F5        デバッグ開始
・F10       ステップオーバー
・F11       ステップイン
・Shift+F11 ステップアウト
・F6        一時停止
・Shift+F5  停止
・F5        再開
```

# 1.12 練習問題

```
1-1
A. var1と=の間のスペースをなくす

A. 1-2
STDOUTにTuesdayと出力

1-3
A. クォートを$()にしてコマンドを解釈させる。スペースをなくす

1-4
A. b=15, c=15
```