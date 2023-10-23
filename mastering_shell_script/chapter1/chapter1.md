# 1.1 技術要件
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

## 1.4.1 vimの設定
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

