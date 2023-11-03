# はじめに

- 目標
```
目標
    ・C言語のソースコードをアセンブリ言語に変換するプログラムを作成
    ・コンパイラそのものもCを使って開発
    ・自作コンパイラでコンパイルすることが目標

流れ
    ・最初は独自言語を実装する
    ・機能を追加していきCと一致するものとする
    ・初期からコンパイルできるんどえモチベを保ちやすい
    ・まんべんなく学んでいく
    ・大きなプログラムを作る知識も学べる
    ・コラムなども解説されているとのこと

想定読者
    ・Cの標準的なプログラマ

```
- なぜC言語なのか
```
インタプリタ形式の言語
    低レイヤについて学びにくい
C
    アセンブリにコンパイルするので学びやすい
    言語使用が標準として与えられているので実装から逃れられない

コンパイラが動くようになったら
    curl -Oでコードをdownloadしてきてコンパイルして遊ぼう！
    完成度が高ければLinuxカーネルすらコンパイルできるとのこと

C++は?
    言語使用が巨大で自作コンパイラは作りにくい
```

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

- パターンルール
```makefile
favorite-ex: favorite-ex.o myfood.o
	gcc $^ -o $@

%.o: %.c
	gcc $< -c -o $@

favorite-ex.o: favorite-ex.c
myfood.o: myfood.c myfood.h
```

# 表記法について