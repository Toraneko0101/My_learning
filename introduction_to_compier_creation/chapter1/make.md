# 補足(makeについて)
```
make
    ・CやC++等のコンパイル型の言語で記述されたプログラムを容易にビルドするためのもの
    ・毎回gccコマンドを記述しているのを不便だと思う時に便利
```
- gccのビルド
```
$ gcc hello.c -o hello -O3 -Wall -g
    ・生成されるファイルをhello
    ・O3で最適化により実行を高速化
    ・Wallでコンパイラによるチェックをすべて出力
    ・gでGDBを用いてデバックできるようにする

```
- ./hello.c
```c
#include <stdio.h>

int main(void){
    printf("Hello!");
}
```
- ./Makefile
```makefile
hello: hello.c
	gcc hello.c -o hello
```
```
$ make
gcc hello.c -o hello
$ LANG=C make
make: 'hello' is up to date.

必要な時だけビルドしてくれる
    ・鍵はファイルのtimestamp
    ・以前buildした時より後にhello.cが更新されていなければビルドしない
    ・大規模なプロジェクトでは全てのソースファイルをビルドしていたら日が暮れるので、makeは必要不可欠

touchでタイムスタンプを変更して、再度make
    ・そういえばtouchはもともとそんなコマンドだったな

$ touch hello.c && make
gcc hello.c -o hello
```

- Makefileの書式
```
作成するプログラム : ソースファイル
    ビルドのためのコマンドライン

※timestampが依存fileより古いか、targetが存在しない場合、2行目が実行される
```

## ヘッダファイルを使用する場合


```makefile
favorite: favorite.c favorite.h
	gcc favorite.c -o favorite
```
```
依存するファイルを右側にすべて記載
    少なくとも一つが変更されるとビルドが実行される
```

## ソースファイルが複数ある場合
```
・オブジェクトファイルをソースファイルごとに作成し、最後にリンクする
```
- ./myfood.c
```c
const char *my_favorite_food(void){
    //文字列を返す
    return "curry and rice.";
}
```
- ./myfood.h
```c
const char *my_favorite_food(void);
```

- ./favorite-ex.c
```c
#include <stdio.h>
#include "myfood.h"

int main(void){
    printf("My favorite food is %s\n", my_favorite_food());
}
```
- ./Makefile
```makefile
favorite-ex: favorite-ex.o myfood.o
	gcc favorite-ex.o myfood.o -o favorite-ex

favorite-ex.o: favorite-ex.c
	gcc favorite-ex.c -c -o favorite-ex.o

myfood.o: myfood.c myfood.h
	gcc myfood.c -c -o myfood.o
```

- 解説
```
-c
    コンパイルのみを行う(オブジェクトファイルを生成。リンkぅは行わない)
再帰的
    ・依存fileの作成方法をMakefile内から探す
    ・例えばmyfood.oが一番上にあると解決されてmakeは終了する
    ・今回はfavorite-ex.oがないので下のブロックに進む
    ・で、myfood.oもないので、下のブロックを実行し戻る
    ・たとえばmyfood.oが変更されていなければ3番目のブロックは実行されない

※makeには似たような機能を削減する機能もある
```

## マクロの使用
```makefile
hello: hello.c
    gcc $^ -o $@
```
- 説明
```
$^
    コロンの右側の依存fileに置き換えられる
$@
    ターゲットのファイル名

$<
    コロン右側の依存fileのうち、最初の一つのファイルに置き換えられる。ソースファイルだけを渡したいときに使う
```
- 複数ソースのMakefileを置き換える
```makefile
favorite-ex: favorite-ex.o myfood.o
    gcc $^ -o $@
favorite-ex.o: favorite-ex.c
    gcc $< -c -o $@
myfood.o: myfood.c myfood.h
    gcc $< -c -o $@
```

## パターンルール
```makefile
favorite-ex: favorite-ex.o myfood.o
	gcc $^ -o $@

%.o: %.c
	gcc $< -c -o $@

favorite-ex.o: favorite-ex.c
myfood.o: myfood.c myfood.h
```
- 解説
```
%.o: %.c
    ・.oという拡張子のファイルを拡張子以外が同じ名前で、拡張子が.cのファイルから作成するルールを定義する
    ・各オブジェクトの作成ルールについては依存関係のみの記述でよく、コマンド部は省略できる
```

## 組み込みルール
- 省略記法
```
・makeはn.oというファイルがn.cに依存していると仮定する
・つまり、これら(myfood.o : myfood.c)を明示的に記述する必要はない

favorite-ex.o: favorite.c
-> なし
myfood.o: myfood.c myfood.h
-> myfood.o: myfood.h
```
```makefile
favorite-ex: favorite-ex.o myfood.o
    gcc $^ -o $@

%.o: %.c
    gcc $< -c -o $@

myfood.o: myfood.h
```
- 実行するコマンドも省ける
```
・makeはn.cからn.oを作るルールを持っている
・そしてn.oから実行ファイルを作るルールも持っている

・つまり、コンパイルコマンドが指定されていない場合、Makeはビルドに使用できるデフォルトのルールを適用する
・.cから.oを生成する際、自動的にgcc $< -c -o $@を呼び出すコマンドを生成するというのがデフォルトルール
・.oから実行ファイルを生成する際も、自動的にgccを呼び出すコマンドを生成するというのがデフォルトルールgcc $^ -o $@

1. favorite-ex.oを再帰的に探索
2. patternルールより、favorite-ex.o : favorite.c
3. .c -> .o のデフォルトルールでfavorite-ex.oを生成
4. patternルールより、myfood.o:  myfood.c myfood.h
5. .c -> .o のデフォルトルールでmyfood.oを生成
6. .o -> 実行ファイル のデフォルトルールでfavorite-exを生成


%.o: %.c
    $(CC) $(CFLAGS) $< -c -o $@
%: %.o
    $(CC) $(CFLAGS) $^ -o $@
ちな、.c -> 実行ファイルの場合はこれ
%: %.c
    $(CC) $(CFLAGS) $< -o $@

$(CC)
    Cコンパイラを指定する環境変数。デフォルトgcc
$(CFLAGS)
    環境変数。追加オプション
つまり今回の場合は、
    gcc $< -o $@
```
```makefile
favorite-ex: favorite-ex.o myfood.o
myfood.o: myfood.h
```
- つまり、hello.cはこれだけでよかった
```makefile
hello:
```

## コンパイラオプションを渡すには？
```
・CFLAGSを使う
・CCもMakefile内の記述で変更可能
```
- コード
```makefile
CFLAGS = -O3 -Wall -g
hello:
```
- 特別な意味を持つ変数名
```
CFLAGS C言語のコンパイラオプション
CXXFLAGS C++言語のコンパイラオプション
LDFLAGS リンカオプション
```

# プログラミング以外の用途にmakeを使用
```makefile
chart.png: parsed.dat mkchart.gp
    gnuplot -e "load 'mychart.gp'"

parsed.dat: raw.log parse.py
    parse.py $< > $@

```

## makeのいいところ
```
/usr/bin/make
    ここにデフォルトで入っている
```
- 記法
```
<変数宣言>
<タスク名>:
    <実行したいshell>

・make <タスク名>で実行
・実行するshellを出力したくないなら@を先頭につける
・めんどくさいコマンドを省略できるようになるので使えるかも

compile: activator
    ・activatorというファイルが存在していないと失敗
    ・これはtarget : sourceと同じことをしているだけ

・@makeでファイル内で@makeを呼ぶと明示的にタスクを呼べる
```
- 例
```makefile
# make -s doit
# makefileがサブディレクトリ内で実行されているかのように見える場合、大量のメッセージ出力がある。-sを使うとサブディレクトリに移動するメッセージを残さないくなる。

MESSAGE = "Nekodayo"

show-ip:
	ip a
show-files:
	@ls -lh
show-message:
	@echo ${MESSAGE}
compile: activator
	@echo "Yey!"

task-a:
	@echo "A"
	@touch a.txt
	@make task-b

task-b: a.txt
	@echo "B"
	@touch b.txt
	@make task-c

task-c: b.txt
	@echo "C"
	@touch c.txt

clean: a.txt b.txt
	@rm a.txt b.txt c.txt
	@echo "complete!"

doit:
	@make task-a
	@make clean
```