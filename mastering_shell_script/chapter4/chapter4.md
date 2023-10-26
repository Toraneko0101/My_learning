# 0. コードスニペットの作成

## 0.1 nvimについて
- [nvim_practice.md](./nvim_practice.md)


# 4.1 短縮入力

- 概要
```
・スクリプトを書く時間を短縮したい
```
- abbrコマンド(~/.vimrcに記述する)
```
~/.vimrc
    ・vimテキストエディタのための実行制御メカニズムとして機能する
    ・古いディストリビューションの場合、viテキストエディタがあり、~/.exrcファイルが入っているかもしれない

例)
    abbr _sh #!/bin/bash
    abbr <ショートカット> <文字列>

C言語でいう#defineと似ているな

使い方)
    編集モード中に_shと押して、任意のキーを押すとショートカットが展開される

実際の設定例)
    abbr _py #!/usr/bin/env python
    ※たぶん、半角スペースが空いていてもその通りに認識される
    ※アンダーバーは必須ではないが、入力エラーをなくすために必要
    ※複数行の短縮入力を行う際は別のものを検討する
```

# 4.2 コードスニペットの使用
- 概要
```
コードスニペット: 現在作成中のスクリプトに読み込める事前に用意されたコード

使い方)
    :r <パスおよびファイル名>

具体例)
    :r $HOME/snippets/if

    ・$HOME/snippetsに存在しているifというファイルの内容を読み込みたい場合
    ・カーソル位置の下に、該当ファイルの内容が読み込まれる
    ・ディレクトリを共有する必要はないので、作成時にモードを700に設定しておくとユーザに対してプライベートになるので良い

    ※本来は、$HOME/snippets等に作成するのがいいと思われるが、今回は一例であるためmastering_shell_script内に作成する
```
- スニペットの作成
```bash
# $HOME/program_file/my_learning/mastering_shell_script/にifを作成した

# ~/.vimrcに
# abbr _sn $HOME/program_file/my_learning/mastering_shell_scriptと記載した

#インデント調整が要らないのは便利かも
if [ 1 = 1 ]; then
    echo
fi

```

## 4.2.1 ターミナルに色を導入する
- eオプションでエスケープシーケンスを解釈させる
```
赤色
    echo -e "\033[31mError\033[0m"
    echo -e "\e[31mError\e[0m"

\033[31m
    ・ANSIエスケープシーケンス
    ・\0は8進数
    ・\xで16進数
    ・\033 = \x1b はASCIIのESCを意味している
    ・\eでもESCを表現できる

・RED="\033[31m"
・GREEN="\033[32m"
・BLUE="\033[34m"
・RESET="\033[0m"

・変数を使う場合は以下のようにする。
・{}で変数と文字列の境目を区切る必要がある
※{}にはカレントシェルでプログラムをブロック処理かのように実行する意味合いもある

$ echo -e "${RED}Error${RESET}"
```
- 他のスクリプトから色を変える変数を利用する(設定)
```
source <ファイル名>
soruce: 変数定義を実行時にスクリプトに組み込む
```
- 他のスクリプトから色を変える変数を利用する(コード)
```bash
#!/bin/bash

#以下については _snで記載
source $HOME/program_file/my_learning/mastering_shell_script/snippets/color

if [ "$#" -lt 1 ]; then
    echo -e "${RED}Usage: $0 <name>$RESET"
    exit 1
fi
echo -e "${GREEN}Hello $1$RESET"
exit 0
```
- ANSIエスケープシーケンスについて理解する

# 4.3 VSCodeを用いたスニペットの作成