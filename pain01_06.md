# 1章
## プログラムについて
```
自然言語：曖昧さがある
プログラミング言語：意味が明確。記憶,判断,演算
```

## Code-Runner
```
Ctrl+Alt+N : 実行
```

## gccのインストール
```
Ubuntuで試している
$ sudo apt-get install gcc
```

## 高級言語までの流れ
```
1. 最初は0,1でやり取りしていた
2. 16進数を使うことを考えた
3. 人間がわかりやすいように16進数を記号化して考えるようになった=アセンブラ
4. FORTRANが生まれ、人間の言葉に近い高級言語の時代が始まった
```

## コンパイラ
```
C言語（高級言語）で書かれた文字列ファイルを、マシン後に翻訳するもの
1. プリプロセッサで文字列を調整（空行や改行の結合、記号の置き換え,#define等を処理）
2. コンパイラが、高速動作を実現するため最適化を行って翻訳する
3. 翻訳した機械語プログラムをリンカで結合（リンク）する
4. リンクすることで、マシン語のデータは実行可能ファイルとなる
5. アプリとして実行

ビルド: プリプロセス->コンパイル->リンク->実行可能ファイルの作成
```

## 練習問題

### 1-1
```
Q. C言語のプログラムはある物の集合として作られる。
ある物とは何か。
A. 関数
```
### 1-2
```
Q. 上記のある物の構造は、4つの機能の組み合わせになっている。
その4つの機能とは何か。順番、区切りの記号まで正しく答えよ。

A. 型名 関数名(引数){
    処理
}

```
### 1-3
```
Q. C言語は人間向きの言語であり、コンピュータには理解できないため、
C言語をコンピュータ向きの言語に翻訳するソフトがある。
そのようなソフトをなんと呼ぶか。

A. コンパイラ
```

### 2-1
```
Q. 何も行わないmain関数だけのプログラムを作成せよ。
```
```c
int main(void){
    return 0;
}
```

### 3-1
```
Q. C言語では、関数には自由な名前を付けることができるが、
必ず一つはmainという名前の関数がなくてはならない。
その理由を簡潔に述べよ。

A. mainはエントリーポイント(1番初めに動作する関数)であるため
```

# 2章

## プログラムの最小単位
```
・C言語の最小単位はトークン(単語)
・以下より細かくは分解できない
・トークンをつなげたり、分解しなければどのような記法でも動く(Cの場合)
int 
main
(
void
)
{
return
0
;
}
```

## そのほかのルール
```
・大文字と小文字は区別される
・セミコロンを忘れない
・全角スペースはIDEの拡張機能などで発見した方がよさそう
```

## 書き方の慣習
```
/**/ コメント
Tabによるインデント
```

## 練習問題

### 1-1
```
Q. C言語の文法上の最小単位は何か。
A. トークン
```

### 1-2
```
Q. C言語のプログラムは自由な書き方で書くことができる。
この特徴をなんと呼ぶか。
A. 自由書式
```

### 1-3
```
Q. C言語では大文字と小文字は区別するかどうか。
A. する
```

### 1-4
```
Q. 行の先頭にタブ文字や空白文字を入れることで、
階層を表現する書き方をなんと呼ぶか。
A. インデント
```

### 1-5
```
Q. プログラム中に説明文を書き込むことができるが、
この説明文のことをなんと呼ぶか。
A. コメント
```

### 2-1
```
Q. 何も行わないmain関数だけのプログラムを作成せよ。
ただし、慣習に従った書き方にし、インデントも行うこと。
```
```c
int main(void){
    /*何もしない*/
    return 0;
}
```

### 3-1
```
Q. C言語のプログラムは自由な書き方ができるので、
インデントを付けたり、コメントを付けたりしても動作には影響がないのに、
それらを付けることが一般的であるのはなぜか簡潔に説明せよ。

A. コードの意図をわかりやすく保つため
```

# 3章

## 処理の内容をディスプレイに表示するには？
```c

//文字列表示
int main(void){
    printf("Hello C!");
    return 0;
}
```
## printfについてコンパイラに理解させる(理論)
```
・#include <stdio.h>で括られている場合は、標準ディレクトリから探す
・#include "stdio.h"で括られている場合は、current->標準の順で探す

1. Preprocessing
・プリプロセサで、#includeを処理し、ソースコードを変換
・指定されたヘッダファイル(stdio.h)の内容をソースコードに挿入し、プロトタイプ宣言を展開

2. Compile
・プリプロセサ済みのコードをコンパイルする
・コンパイラは関数のプロトタイプ宣言を確認する
・そのため関数名や引数と戻り値の型が不正であればコンパイルエラーを出すが、関数の実装はまだ把握していないため、実装がなくとも通過する
・この段階でアセンブリ言語のソースコードに変換する(hello.s)

3. Assembly
・アセンブリファイルを機械語に変換し、オブジェクトファイルを生成(hello.o)
・まだ未解決のシンボルがあるので、実行可能ファイルではない

4. Link
・アセンブリ済みのオブジェクトファイルをリンカで結合
・関数の実装はこの段階で取り込まれる
・printfの実装はライブラリファイルにあり、これは機械語で書かれている
・したがって、リンクプロセスでオブジェクトファイルと結合され、取り込まれる
・すべてが結合されると実行可能ファイルとなる
・プログラム内の関数や変数が宣言されていない。実装が提供されていない等の場合、リンクエラーを輩出する


```

## プリプロセス->コンパイル->アセンブリ->リンク
```
0-1. gcc print.c -> 実行可能ファイル(ELF)を作ってくれる
0-2. ターゲットを指定していないので、a.outが作成される
```
1. プリプロセス(前処理を行う)
- `gcc -E print.c > print.i `
- 以下、print.i
```c
# 0 "print.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2

・・・

# 2 "print.c" 2


# 3 "print.c"
int main(void){
    printf("Windows\tMicrosoft\n");
    printf("MacOS\tApple\n");
    return 0;
}
```
2. コンパイル
- `gcc -S print.i`
- 以下、print.s
```nasm

	.file	"print.c"
	.text
	.section	.rodata
.LC0:
	.string	"Windows\tMicrosoft"
.LC1:
	.string	"MacOS\tApple"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
```
3. アセンブル
- `gcc -c print.s`
- 以下、print.o(stringsコマンドで可読部分を閲覧)
```
Windows	Microsoft
MacOS	Apple
GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0
print.c
main
puts
.symtab
.strtab
.shstrtab
.rela.text
.data
.bss
.rodata
.comment
.note.GNU-stack
.note.gnu.property
.rela.eh_frame

```
- odコマンドでバイナリファイルを閲覧
- なお、出力はaオプションを付けて文字に直した
```
0000000 del   E   L   F stx soh soh nul nul nul nul nul nul nul nul nul
0000020 soh nul   > nul soh nul nul nul nul nul nul nul nul nul nul nul
0000040 nul nul nul nul nul nul nul nul   ( stx nul nul nul nul nul nul
0000060 nul nul nul nul   @ nul nul nul nul nul   @ nul  so nul  cr nul
0000100   s  si  rs   z   U   H  ht   e   H  cr enq nul nul nul nul   H
0000120  ht   G   h nul nul nul nul   H  cr enq nul nul nul nul   H  ht
0000140   G   h nul nul nul nul   8 nul nul nul nul   ]   C   W   i   n
0000160   d   o   w   s  ht   M   i   c   r   o   s   o   f   t nul   M
0000200   a   c   O   S  ht   A   p   p   l   e nul nul   G   C   C   :
0000220  sp   (   U   b   u   n   t   u  sp   1   1   .   4   .   0   -
0000240   1   u   b   u   n   t   u   1   ~   2   2   .   0   4   )  sp
0000260   1   1   .   4   .   0 nul nul eot nul nul nul dle nul nul nul
0000300 enq nul nul nul   G   N   U nul stx nul nul   @ eot nul nul nul
0000320 etx nul nul nul nul nul nul nul dc4 nul nul nul nul nul nul nul
0000340 soh   z   R nul soh   x dle soh esc  ff bel  bs dle soh nul nul
0000360  fs nul nul nul  fs nul nul nul nul nul nul nul   - nul nul nul
0000400 nul   E  so dle ack stx   C  cr ack   d  ff bel  bs nul nul nul
0000420 nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul
0000440 nul nul nul nul nul nul nul nul soh nul nul nul eot nul   q del
0000460 nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul
0000500 nul nul nul nul etx nul soh nul nul nul nul nul nul nul nul nul
0000520 nul nul nul nul nul nul nul nul nul nul nul nul etx nul enq nul
0000540 nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul
0000560  ht nul nul nul dc2 nul soh nul nul nul nul nul nul nul nul nul
0000600   - nul nul nul nul nul nul nul  so nul nul nul dle nul nul nul
0000620 nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul
0000640 nul   p   r   i   n   t   .   c nul   m   a   i   n nul   p   u
0000660   t   s nul nul nul nul nul nul  vt nul nul nul nul nul nul nul
0000700 stx nul nul nul etx nul nul nul   | del del del del del del del
0000720 dc3 nul nul nul nul nul nul nul eot nul nul nul enq nul nul nul
0000740   | del del del del del del del sub nul nul nul nul nul nul nul
0000760 stx nul nul nul etx nul nul nul  so nul nul nul nul nul nul nul
0001000   " nul nul nul nul nul nul nul eot nul nul nul enq nul nul nul
0001020   | del del del del del del del  sp nul nul nul nul nul nul nul
0001040 stx nul nul nul stx nul nul nul nul nul nul nul nul nul nul nul
0001060 nul   .   s   y   m   t   a   b nul   .   s   t   r   t   a   b
0001100 nul   .   s   h   s   t   r   t   a   b nul   .   r   e   l   a
0001120   .   t   e   x   t nul   .   d   a   t   a nul   .   b   s   s
0001140 nul   .   r   o   d   a   t   a nul   .   c   o   m   m   e   n
0001160   t nul   .   n   o   t   e   .   G   N   U   -   s   t   a   c
0001200   k nul   .   n   o   t   e   .   g   n   u   .   p   r   o   p
0001220   e   r   t   y nul   .   r   e   l   a   .   e   h   _   f   r
0001240   a   m   e nul nul nul nul nul nul nul nul nul nul nul nul nul
0001260 nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul
*
0001340 nul nul nul nul nul nul nul nul  sp nul nul nul soh nul nul nul
0001360 ack nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul
0001400   @ nul nul nul nul nul nul nul   - nul nul nul nul nul nul nul
0001420 nul nul nul nul nul nul nul nul soh nul nul nul nul nul nul nul
0001440 nul nul nul nul nul nul nul nul esc nul nul nul eot nul nul nul
0001460   @ nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul
0001500   8 soh nul nul nul nul nul nul   ` nul nul nul nul nul nul nul
0001520  vt nul nul nul soh nul nul nul  bs nul nul nul nul nul nul nul
0001540 can nul nul nul nul nul nul nul   & nul nul nul soh nul nul nul
0001560 etx nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul
0001600   m nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul
0001620 nul nul nul nul nul nul nul nul soh nul nul nul nul nul nul nul
0001640 nul nul nul nul nul nul nul nul   , nul nul nul  bs nul nul nul
0001660 etx nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul
0001700   m nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul
0001720 nul nul nul nul nul nul nul nul soh nul nul nul nul nul nul nul
0001740 nul nul nul nul nul nul nul nul   1 nul nul nul soh nul nul nul
0001760 stx nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul
0002000   m nul nul nul nul nul nul nul  rs nul nul nul nul nul nul nul
0002020 nul nul nul nul nul nul nul nul soh nul nul nul nul nul nul nul
0002040 nul nul nul nul nul nul nul nul   9 nul nul nul soh nul nul nul
0002060   0 nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul
0002100  vt nul nul nul nul nul nul nul   , nul nul nul nul nul nul nul
0002120 nul nul nul nul nul nul nul nul soh nul nul nul nul nul nul nul
0002140 soh nul nul nul nul nul nul nul   B nul nul nul soh nul nul nul
0002160 nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul
0002200   7 nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul
0002220 nul nul nul nul nul nul nul nul soh nul nul nul nul nul nul nul
0002240 nul nul nul nul nul nul nul nul   R nul nul nul bel nul nul nul
0002260 stx nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul
0002300   8 nul nul nul nul nul nul nul  sp nul nul nul nul nul nul nul
0002320 nul nul nul nul nul nul nul nul  bs nul nul nul nul nul nul nul
0002340 nul nul nul nul nul nul nul nul   j nul nul nul soh nul nul nul
0002360 stx nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul
0002400   X nul nul nul nul nul nul nul   8 nul nul nul nul nul nul nul
0002420 nul nul nul nul nul nul nul nul  bs nul nul nul nul nul nul nul
0002440 nul nul nul nul nul nul nul nul   e nul nul nul eot nul nul nul
0002460   @ nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul
0002500 can stx nul nul nul nul nul nul can nul nul nul nul nul nul nul
0002520  vt nul nul nul  ht nul nul nul  bs nul nul nul nul nul nul nul
0002540 can nul nul nul nul nul nul nul soh nul nul nul stx nul nul nul
0002560 nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul
0002600 dle soh nul nul nul nul nul nul dle nul nul nul nul nul nul nul
0002620  ff nul nul nul eot nul nul nul  bs nul nul nul nul nul nul nul
0002640 can nul nul nul nul nul nul nul  ht nul nul nul etx nul nul nul
0002660 nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul
0002700  sp soh nul nul nul nul nul nul dc3 nul nul nul nul nul nul nul
0002720 nul nul nul nul nul nul nul nul soh nul nul nul nul nul nul nul
0002740 nul nul nul nul nul nul nul nul dc1 nul nul nul etx nul nul nul
0002760 nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul nul
0003000   0 stx nul nul nul nul nul nul   t nul nul nul nul nul nul nul
0003020 nul nul nul nul nul nul nul nul soh nul nul nul nul nul nul nul
0003040 nul nul nul nul nul nul nul nul
0003050

```
1. unixならprint。windowsならprint.exeが生成される

2. 実行権限を確認して実行

3. なお、現代のプログラマが書くのはこれだけでいい
```c
#include <stdio.h>

int main(void){
    printf("Hello C!");
    return 0;
}
```

## 改行文字
```
エスケープシーケンス: 制御文字
\n: 改行文字
\t: タブ
```
```c
#include <stdio.h>

int main(void){
    printf("Windows\tMicrosoft\n");
    printf("MacOS\tApple\n");
    return 0;
}
```

## 練習問題3

### 1-1
```
Q. C言語で画面に文字列を表示するのに何という関数を使うか。
A. printf
```

### 1-2
```
Q. 上記の関数を使うには、コンパイラに説明書を渡さなくてはならない。
そのための疑似命令と、渡す説明書のファイル名を答えよ。
A. include, stdio.h
```

### 1-3
```
Q. 上記の関数で文字列を表示するときに改行するには記号を書く。
その記号全般のことをなんと呼ぶか。
A. \n, エスケープシーケンス
```

### 2-1
```c
#include <stdio.h>

int main(void)
{
    printf("The pen is mightier\n than the sword\n");
    return 0;
    printf("Time is money\n");
}
```
```
A. 
The pen is mightier
than the sword
```

### 3-1
```
Q.画面に次のように表示するプログラムを作成せよ。
なお、2つ目の文字の頭が揃えられていれば、空白の数は問わない。

Intel : Pentium4
AMD 　: Athlon64
```
```c
#include <stdio.h>
int main(void){
    printf("Intel\t: Pentium4\n");
    printf("AMD\t: Athlon64\n");
    return 0;
}
```

# 4章
- printfで文字列を表示
```
文字数リテラル: プログラム内に埋め込まれるクォートで囲まれた文字
printfで数値を表示：出力変換して数値を使用する
もともとprintfは文字列を表示する関数なので、%dなどで整数を文字列に変換して表示する

```
```c
# include <stdio.h>

int main(void){
    printf("%d", 100);
    return 0;
}
```
`gcc digit.c -o digit`

- 浮動小数点の計算
```
浮動小数点：仮数部と、指数部で実数を表現する
実数値を文字列に変換する場合は、%f指定子を使用する
```
```c
#include <stdio.h>

int main(void){
    printf("%f\n",  10.0 / 3.0);
    return 0;
}
```
## 練習問題4

### 1-1
```
Q. ""で囲まれた文字列のことをなんと呼ぶか。
A. 文字式リテラル
```

### 1-2
```
Q. 数学で×の記号の代わりに、C言語ではどの記号を使用するか。
A. *
```

### 1-3
```
Q. 数学で÷の記号の代わりに、C言語ではどの記号を使用するか。
A. /
```

### 1-4
```
Q. C言語では実数を表現するのになんと呼ばれる方式を使っているか。
A. 浮動小数点
```

### 2-1
```c
#include <stdio.h>

int main(void)
{
    printf("%d\n", 20 / 7);
    printf("%f\n", 20.0 / 7.0);
    return 0;
}
```
```
A. 
2
2.857...
```

### 3-1
```
Q. 40÷13を計算し、式と商と余りを表示するプログラムを作成せよ。
```
```c
#include <stdio.h>

int main(void){
    printf("%d / %d = %d ... %d", 40, 13, 40/13, 40%13);
    return 0;
}
```

### 4-1
```
Q. C言語では、整数で割り算を行った場合、
割り切れないときには結果を切り捨てるが、
それはなぜか簡潔に説明せよ。
A.結果の予測が容易になるため。
```

# 5章
- 概要
```
・変数:数値を記憶するメモリ領域の位置に名前を付けて管理する方法
・Cの場合、変数の宣言は関数の先頭でしか行えない
・ただし多くのコンパイラはC++をサポートしているため動く
・変数名＝数値
・これは、右側の数値を左側の変数（メモリ位置）に記憶させることを意味する
・変数が覚えている値に対して操作することも可能
```
- code
```c
#include <stdio.h>

int main(void){
    int value = 10;
    printf("%d\n", value);
    value++;
    printf("%d\n", value);
    value--;
    printf("%d\n", value);
}
```
- 型の変換
```c
#include <stdio.h>

int main(void){
    //整数->実数
    printf("%f\n", 1.03 * 9);
    //キャスト(強制的に型変換)
    printf("%d\n", (int)(1.03 * 9));
    return 0;
}
```
- formatの指定
```c
#include <stdio.h>

/*
注意点
    マイナス記号も1桁として取り扱われる
    %05dで0-padding
    %5dで空白-padding
    %全体桁数.小数桁数f
    
    ※全体桁数は少数の桁数と小数点を含む
    %06.2fで3.2を表示したいと思った場合
    003.20と表示される
    小数部分が2桁,整数部分が6-2-小数点の桁=3なので
*/
int main(void){
    int a = 10000, b = 500, c = 3;

    printf("Aは %5d です。\n", a);
    printf("Bは %5d です。\n", b);
    printf("Cは %5d です。\n", c);
    printf("小数は %06.2fです。\n", 3.2);
    return 0;
}
```

## 練習問題5

### 1-1
```
Q. 数値を記憶するメモリに名前を付けることをなんと呼ぶか。
A. 宣言
```

### 1-2
```
Q. 上記の場所に数値を記憶することをなんと呼ぶか。
A. 代入
```

### 1-3
```
Q. 上記の場所の数値を1だけ増やすことをなんと呼ぶか。
A. インクリメント
```

### 2-1
```c
#include <stdio.h>

int main(void)
{
    int x, y;

    x = 10;
    y = x * 10 + 20;
    printf("%5d\n", y);

    return 0;
}
```
```
A.
00120
```

### 3-1
```
1本198円の清涼飲料水1本と、1本138円の牛乳2本を購入し、
千円札で払った場合のお釣りを求めよ。
ただし、5%の消費税を追加し、お釣りの額は整数とする。
なお、消費税を四捨五入するかどうかは自由とする。
```
```c
#include <stdio.h>

int main(void){
    int water, milk, ans, money;
    double tax;
    water = 198;
    milk = 138;
    money = 1000;
    tax = 1.05;
    ans = money - (int)((water + milk * 2) * tax);

    printf("%d\n", ans);
}
```

### 4-1
```
Q. 3.14 * 12 のように、実数と整数による計算を行うと、答えは実数として扱われるが、その理由を簡潔に述べよ。

A. 小数点以下の値が切り捨てられるのを防ぐため
```

# 6章
- キーボードから入力を行う
```
・scanf("書式指定文字列", &変数名);
・書式指定文字列：入力された値をprintfのように文字列に変換
・&変数名: 入力されたデータを記憶しておく変数名を参照する
・※変数の型がstrなら、&は要らない
・実数の場合、%lfであることに注意
```
- code
```c
#include <stdio.h>

int main(void){
    double data;
    scanf("%lf", &data);
    printf("%f\n", data);
    return 0;
}
```
- 複数値の入力
- 入力時は、スペース、タブ、改行などで区切って入力
- 2つの指定子の間に区切る記号を指定する
```c
#include <stdio.h>

int main(void){
    int data1, data2;
    scanf("%d-%d", &data1, &data2);
    printf("%d, %d\n", data1, data2);
    return 0;
}
```
- 簡易Σ
```c
#include <stdio.h>

int main(void){
    /*宣言*/
    int min, max, sum;

    /*入力*/
    printf("最小値と、最大値を,で区切って入力");
    scanf("%d, %d", &min, &max);

    /*計算*/
    sum = (min + max)* (max - min + 1) / 2;

    /*表示*/
    printf("%d ~ %d の合計は %dです\n", min, max, sum); 

    return 0;
}   
```

- scanfは良くない?
```
・区切り記号を打ち間違えると実行結果が異なる
・たとえばintの範囲を超えるとオーバーフローを起こす
・他の型を入力して、挙動を狂わせることができてしまう
```

## 練習問題6

### 1-1
```
Q. キーボードから数値を入力するために使う関数は？
A. scanf
```

### 1-2
```
Q. 上記の関数を使うとき、変数名の前に付ける記号は？
A. アンパサンド
```

### 2-1
```c
#include <stdio.h>

int main(void)
{
    int side, high, square;

    scanf("%d,%d", &side, &high);
    square = side * high / 2;
    printf("%d\n", square);

    return 0;
}
```
```
A. 三角形の面積
```
### 3-1
```
Q. 定価を入力すると、1割引、3割引、5割引、8割引の値段を、一覧表示するプログラムを作成せよ。なお、結果の金額は整数値での表示が望ましいが、実数でもかまわない。
```

### 4-1
```
Q. 実は、scanf関数は、信頼性が必要なプログラムではほとんど使われない。
それはなぜか、簡潔に説明せよ。
A. 想定外の入力やバッファオーバーフローの危険性があるため
```