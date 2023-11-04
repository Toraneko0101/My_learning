# 電卓レベルの言語の生成
- 目標
```
以下のような式をコンパイルできるようにする
30 + (4 - 2) * -5

・括弧の中の式が優先される
・掛け算が足し算より優先される
⇒文字の並びを解析して、その隠れた構造を導かなければならない
```
- 構文解析
```
・昔は難しい問題だと考えられていた
・今はやり方さえ分かっていればいける
・再帰下降構文解析法
    ・今回使う構文解析
    ・GCCやClang等も用いている
・このテクニックは構造のあるテキストを読む際にも使える
```

# Step1 : 整数1個をコンパイルする言語の作成
```
最もシンプルなのは整数1つだけからなる言語
```
- 目標
```
・1個の数を入力から読んで、その数をプログラムの終了コードとして終了するアセンブリを出力するコンパイラ
・これも定義からいうと立派なコンパイラ
・このステップではMakefile(ビルドfile)、自動テストの作成、git-repoのセットアップも行う
入力
    42

出力
.intel_syntax noprefix
.globl main

main:
    mov rax, 42
    ret
```

- Intel記法とAT&T記法
```
gccやobjdump
    ・デフォルトではAT&T記法でアセンブリを出力
    ・AT&Tでは結果レジスタが第2引数に来るので、2引数の命令では引数を逆順に書く。なんで？
    ・レジスタ名には%というprefixをつける
    ・だから%rbpや％rspだったのか
    ・で、数値には$というprefixを付け、$42みたいな感じにする
    ・またメモリ参照時には、[]の代わりに()を使う

Intel
    mov rbp, rsp
    mov rax, 8
    mov [rbp + rsx * 4 - 8], rax
AT&T
    mov %rsp , %rbp
    mov $8, %rax
    mov %rax, -8(rbp, rcx, 4)

・Intel記法を使う理由
    ・読みやすさを考慮するため
    ・Intelの命令セットマニュアルのコードを流用できるのがいい
    ・表現力は同じ
    ・AT&T記法はUnixの初期の設計に影響を受けており、Unix System Vなどで使用された

AT&T
    ソースオペランド, 宛先オペランド
Intel
    宛先オペランド, ソースオペランド
```

## コンパイラ本体の作成
```
・コンパイラは通常ファイルとして入力を与える
・今回はコマンドの第1引数に直接コードを与える
・第1引数を数値として読み込み、アセンブリの中に読み込むCプログラムを作成
```
- ./test1.c
```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    if (argc != 2){
        //fprintf: pritnfの出力先が指定できる拡張版
        fprintf(stderr, "引数の個数が正しくありません\n");
        return 1;
    }

    printf(".intel_syntax noprefix\n");
    printf(".global main\n");
    printf("main:\n");
    printf("    mov rax, %d\n", atoi(argv[1]));
    printf("    ret\n");
    return 0;
}
```
- assemply
```
$ cc -o test1 test1.c
$ ./test1 123 > tmp.s
```
- ./tmp.s
```
.inital_syntax noprefix
.global main
main:
    mov rax, 123
    ret
```
- 実行
```
$ cc -o tmp tmp.s
$ ./tmp
$ echo $?
123
```
- 補足
```
・Unixにおいて、ccやgccは、多くの言語のフロントエンドになっており、与えられたファイルの拡張子で言語を判定し、コンパイラやアセンブラを起動する。
・.sという拡張子のファイルを渡すとアセンブルが行われるのはそのため
```

## 自動テスト
- 概要
```
・テストはshellで書く
・assertは入力値と期待される出力値を受け取り、実際に結果をアセンブルし、実際の結果と期待値が同一か調べる
```
- テストコード(test.sh)
```sh
#!/bin/bash

# コンパイルされたobjectファイルを第1引数に受け取り
# 実際の結果と期待値が同一か調べる

assert(){
    compiler="$1"
    expected="$2"
    input="$3"

    "$compiler" "$input" > tmp.s
    cc -o tmp tmp.s
    ./tmp
    actual="$?"

    if [[ "$actual" == "$expected" ]]; then
        echo "$input => $actual"
    else
        echo "$input => $expected expected, but got $actual"
        exit 1
    fi
}

file=""
if [[ -z $1 || ! -f $1 ]]; then
    read -p "please enter object file: " file
else
    file="$1"
fi
assert "$file" 0 0
assert "$file" 42 42

echo OK
```
- ファイルはgitで管理するとのことなので、別フォルダで管理する
```
・コンパイラ名はひとまる9ccで統一
・作成ファイルもtmpで統一
・テストファイルはtest.shで統一
・そのためファイル名をコード中に直接書いてよし
```
- 変更後のtestスクリプト
```sh
#!/bin/bash
assert() {
  expected="$1"
  input="$2"

  ./9cc "$input" > tmp.s
  cc -o tmp tmp.s
  ./tmp
  actual="$?"

  if [ "$actual" = "$expected" ]; then
    echo "$input => $actual"
  else
    echo "$input => $expected expected, but got $actual"
    exit 1
  fi
}

assert 0 0
assert 42 42

echo OK
```
- testスクリプトをデバッグしたいとき
```
$ bash -x ./test.sh
+ assert 0 0
+ expected=0
+ input=0
+ ./9cc 0
+ cc -o tmp tmp.s
+ ./tmp
+ actual=0
+ '[' 0 = 0 ']'
+ echo '0 => 0'
0 => 0
+ assert 42 42
+ expected=42
+ input=42
+ ./9cc 42
+ cc -o tmp tmp.s
+ ./tmp
+ actual=42
+ '[' 42 = 42 ']'
+ echo '42 => 42'
42 => 42
+ echo OK
OK
```

## makeによるビルド
```
makeの詳細はchapter1のmake.mdを参照のこと
```
- Makefile
```makefile
CFLAGS=-std=c11 -g -static

9cc: 9cc.c

test: 9cc
		./test.sh

clean:
		rm -f 9cc *.o *~ tmp*

.PHONY: test clean
```
- Makefileの説明
```
・makeで9ccの実行ファイルが作られる。
・コマンドについては省略
・CFLAGSオプションを渡す
・makeの後にターゲットを指定しないと、1番上のターゲット（この場合だと9cc）が自動的に指定されたことになる

・CFLAGS=-std=c11 -g -static
    C11標準に準拠。
    -g:デバッグ情報を生成
    -static:生成される実行ファイルに必要なライブラリをすべて組み込む。静的リンクを行うオプション

・make test
    ・コマンドとして./test.shが実行される
    ・9ccがない場合は、Makefileの中から探索され、9cc.cから9ccが作成される

・make clean
    ・ビルド中に作成された不要なファイルを削除する役目
    ・rm -f: 存在しないファイルを削除。確認も行わない
    ・~で終わる一時ファイルやtmpから始まる一時ファイル。9ccというオブジェクトファイルを削除する

.PHONY: test clean
    ・testとcleanターゲットを実行する
    ・現在のディレクトリ以下に同じファイル名(たとえばclean)が存在する場合、make cleanとすると、cleanというファイルをビルドするターゲットだと認識してしまう。
    ・その場合、ダミーターゲットである.PHONYが役に立つ

```

## gitによるバージョン管理
```
.gitignoreで一時ファイルを除外する(compiler以下のfileだけ)
・chapter*で作成した場合は、管理下に入れる。


/*.gitignore*/
*~
*.o
tmp*
a.out
9cc

※repoごとにuser.nameを設定したい場合は
git config --local user.name "HOGEHOGE"
のようにする
```
- Git管理について
```
既にrepoを作成しているので略
```
