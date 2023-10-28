# 5. 代替構文

# 5.1 testコマンドの要約
```
testをほかのオプションとともに使うと、その戻り値を調べ、状態を判断可能
```

## 5.1.1 ファイルのテスト
```
・3章の復習
・存在をテスト
    $ test -e /etc/hosts
・通常のファイルかテスト
    $ test -f /etc/hosts
```

## 5.1.2 ロジックの追加
```
通常のファイルであり、かつ読み取り権限が設定されているかテスト(-aや-oで繋ぐ)
    $ test -f /etc/hosts -a -r /etc/hosts
```

## 5.1.3 角括弧の詳細
- 概要
```
testコマンドの終了ステータスを表示する
    $ test; echo $?

testコマンドそのものを省略する
    $ [ -f /etc/hosts -a -r /etc/hosts ]

```
- [は組み込みコマンド
```
$ type -a [
[ is a shell builtin
[ is /usr/bin/[
[ is /bin/[

・組み込みコマンドの[はtestコマンドを模倣したものだが、閉じかっこの]を必要とする。
・typeの-aは、指定した名前のコマンドが存在する場所をすべて表示する
```
- 堅牢なスクリプトを作る。
```
・ファイルの内容を表示する前に、通常ファイルであることと、読み取り可能であることをテストする
・省略と、理解しやすさのバランスをとることが重要

$ FILE=/etc/hosts
$ [ -f $FILE -a -r $FILE ] && cat $FILE
```

# 5.2 パラメータのデフォルト値の設定
- 概要
```
・bashのパラメータ内部では、名前が付けられた領域がメモリー内にある
・そこに保管された値に我々はアクセスしている
・パラメータには変数と特殊パラメータの2種類がある
```

## 5.2.1 変数
- 概要
```
・等号で代入できる
```

## 5.2.2 特殊パラメータ
- 概要
```
・シェルそのものが管理しており、読み取り専用
・例として$0などがある
```

- $-
```
$ echo "My shell is $0 and the sell options are: $-"
My shell is /bin/bash and the sell options are: himBHs

$-パラメータは、設定されているシェルオプションを表す

set -o:
    設定されているシェルオプションを表す
$-:
    設定されているシェルオプションをプログラムで読み取る

himBHs:
    h: 
        hashall。PATHパラメータを使ってプログラムが検索されるようにする
    i:
        対話的(インタラクティブ)なシェル
    m:
        monitorの略で、bgやfgを用いて、コマンドをバックグランドに移したり、戻したりできる
    B:
        プレース展開を可能にする。
        たとえばmkdir dir{1,2}でdir1,dir2が作成される
        $ dir chapter{1,2}
        chapter1:
        bin  chapter1.md

        chapter2:
        bin  chapter2.md
    
    H:
        履歴からコマンドを繰り返すために、実行するコマンドの履歴展開を可能にする
        1438  dir chapter{1,2}
        1439  history
        $ !1438
        dir chapter{1,2}
        chapter1:
        bin  chapter1.md

        chapter2:
        bin  chapter2.md
    
    s:
        コマンドを標準入力から読み込む
        対話的なシェルを起動するときに、位置パラメータの設定を可能とする( >= version 4.4)
```

# 5.2.3 デフォルト値の設定
- 概要
```
・testコマンドや角かっこを使う場合、変数やコマンドラインパラメータにデフォルト値を与えられる
・これはコードに簡潔さを保つ
```
- パラメータ置換(コード)
```bash
#!/bin/bash
name=${1-"Anonymous"}
echo "Hello $name"
exit 0
```
- パラメータ置換(説明)
```
構文
    var_name=${parameter-default}
例
    name=${1-"Anonymous"}

・変数が宣言されておらず、その値がNULLである場合にはデフォルト値が使われる
・NULLを持つパラメータが明示的に宣言されている場合は以下を用いる。
parameter=
${parameter:-default}
```

# 5.3 疑わしい時は......引用符を!
- 概要
```
・変数はパラメータの一種であることを念頭に置いておく
・パラメータについて言及するときには変数も含まれる
```
- パラメータを引用符で囲むことが望ましい理由
```
パラメータ展開:
    変数の値の読み取り

$ name=fred
$ echo "The value is: $name"
    ・fredという値をnameパラメータに代入
    ・パラメータ展開を用いて、保管された値をメモリから表示
    ※$記号はパラメータ展開を可能にするために使う

・スペースは多くのシェルでデフォルトの区切り文字として扱われる
```
- 一見、スペースで区切られていないように見えてもダメ
```
$ FILE="my file"
$ [ -f $FILE -a -r $FILE ] && cat $FILE

・二行目は一見動きそうだが、$記号でパラメータを展開した結果以下のようになる
・$ [ -f my file -a -r my file ] && cat my file

・$ [ -f "$FILE" -a -r "$FILE" ] && cat "$FILE"
・上記のようにパラメータ展開を引用符で囲むことで展開しても意図しないスペースのせいで失敗することがなくなる
・$はパラメータを展開するだけで、他には何もしてくれない
・・$ [ -f "my file" -a -r "my file" ] && cat "my file"
```
- 取り返しがつかないことも
```
$ FILE="my file"
$ rm $FILE
⇒この場合、 $ rm my fileとなり、myやfileというファイルがあると消滅する。

※ShellCheckを用いると、引用符を使用すべき楷書での不使用などの問題点をチェックして修正案を示してくれる
sudo apt install shellcheck
```

# 5.4 [[を使った高度なテスト
- 概要
```
$ type [[
[[ is a shell keyword

・単一の角括弧と異なり、二重角括弧はキーワード
・キーワードは、Bashの解析の非常に早い段階でスキャンされ、解釈される。組み込みの場合は変数の展開や引用符の削除、パス名の展開、単語分割が発生する
```

## 5.4.1 空白文字
- 概要
```
・[[はその引数がbashによって展開される前にそれらを解析する

$ echo "The File Contents" > "my file"
$ FILE="my file"
$ [[ -f $FILE && -r $FILE ]] && cat "$FILE"

・[[を用いた場合、-aや-oの代わりに&&や||、<や>も使える
・ほかに==や!=も使える。
・[[は単語分割を許可しない
・つまり、$FILEがスペースによりmyとfileとして解釈されることはない
```

## 5.4.2 その他の高度な機能

- パターンマッチング
```
・二重角括弧はBourneシェルでは実行できないことだけ注意

・pythonファイルだけをscripts/フォルダの中にコピーする
$ [[ $FILE = *.py ]] && cp "$FILE" scripts/
```
- 正規表現
```
※拡張正規表現を使う場合は、=~
$ [[ $FILE =~ \.pl$ ]] cp "$FILE" scripts/

・エスケープしているので、.plで終わるファイルにマッチする
```

- 正規表現スクリプト
```
・colorとcolour両方に対応する

if [[ $REPLY =~ colou?r ]]; then
・?は直前の文字が0~1回の繰り返しなので

・大文字と小文字の区別をなくす
shopt -s:
    指定したシェルオプションをonにする
shopt -u:
    指定したシェルオプションをoffにする

shopt -s nocasematch
shopt -u nocasematch
    正規表現で指定する際に役立つ
```
- 正規表現スクリプト（コード）
```bash
#!/bin/bash

shopt -s nocasematch

read -p "Type color or mono for script output:"
if [[ $REPLY =~ colou?r ]]; then
    source $HOME/program_file/my_learning/mastering_shell_script/snippets/color
fi
a
# paramが設定されていない場合は、モノクロ表示
echo -e "${RED}This is $0 $RESET"
shopt -u nocasematch
exit 0
```

# 5.5 ((を使った算術演算

## 5.5.1 単純な計算
```
・二重丸括弧は、組み込みコマンドletの代わりになる

$ (( a = 2 + 3 ))
$ let a=2+3

・算術展開の結果をパラメータに代入する場合や、算術展開の結果をコマンドの引数に使いたい場合は、丸括弧の前にドル記号がいる
```
- コード
```bash
#!/bin/bash
a=$(( 2 + 3 ))
echo $a
echo $(( 2 + 3 ))
let b=2+3
echo $b
```

## 5.5.2
```
・二重丸括弧を使うと、C言語スタイルのパラメータ操作が可能
```
- コード
```bash
#!/bin/bash
COUNT=1
(( COUNT++ ))
(( COUNT-- ))
(( COUNT+=10 ))
(( COUNT*=10 ))
echo $COUNT

# ※丸括弧の中で$は必要ない。
#   二重丸括弧はパラメータ操作のために使うもので、明示的な展開は必要ないので
```

## 5.5.3 標準的な算術テスト
```bash
#!/bin/bash
COUNT=10
(( COUNT > 1 )) && echo "Count is greater than 1"

# -gtを使う理由がなくなるのは便利
```

# 5.6
```
・[はコマンドであるため、空白文字の影響を受けないようにするため、引用符で囲む必要がある
・[[はキーワードなので、先に解釈され、結果としてこの内部の変数は単語分割されない
・更に、正規表現などのテストも行える
・二重丸括弧は、C言語のような操作を可能にする

```

# 5.7　練習問題
- 5-1
```bash
#!/bin/bash

COUNT=25
echo $(( COUNT -= 8 ))
```
- 5-2
```
$ rm "my file"
```
- 5-3
```
aに代入する際に、パラメータ展開が必要。
```