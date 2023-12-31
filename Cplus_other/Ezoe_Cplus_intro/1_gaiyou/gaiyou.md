## C++の概要
```
・Cはハードウェアがサポートする命令にまでマッピング可能
・GC(ガベージコレクション)を持っていないので、定期的に全メモリを調べるという、GCのコストを払う必要がない。
・メモリレイアウト(コンピュータのメモリ内のデータがどのように配置され、動アクセスされるか定義するもの)
を実行時に判定する必要がないため、実行時にその分のコストがかからない
・下位互換性が残される
```

## C++の実行
```
・コンパイルやコード生成がプログラマの意識する形で行われるのがC++の特徴
```

## コンパイラオプション
```
-std=
    ・Cの規格を選択する

- Wall
    警告メッセージのほとんどを有効にする

--pedantic-errors
    ・C++の規格を厳格に守る
    ・規格に違反しているコードはコンパイルエラーとなる

・man gccで多くのオプションが見られる
⇒理解するたびに後記する
```

## ヘッダファイルの省略
```
・簡単のため、標準ライブラリのheaderファイルを
すべて#includeしたヘッダファイルを作成し、それを#includ3する

#if __has_include(<custom_header>)
    ・includeファイルが存在する場合は1として評価される
    ・C++17より

-include all.h
    all.hを常に#includeした扱いにする
```

## コンパイル済みヘッダー
```
・precompiled header

//どれだけ時間がかかっているか調べる
$ time g++ -std=c++20 -Wall --pedantic-errors -include all.h -o sample sample.cpp

real    0m1.427s
user    0m1.431s
sys     0m0.052s

real -> プログラムの呼び出しから終了までにかかった時間
user -> プログラム自体の処理時間
sys -> プログラムを処理するために、OSが処理をした時間
-----------------------------

・長いので短縮する
//コンパイル済みヘッダーファイルの作成

1. ヘッダーファイルがC++で書かれていることを示すオプション-x c++-headerを与えて、コンパイル済みヘッダーファイルall.h.gchを生成。

$ g++ -std=c++20 -Wall --pedantic-errors -x c++-header -o all.h.gch all.h

2. GCCはヘッダーファイルを用いる際、同名の.gchファイルが存在する場合は、そちらをコンパイル済みヘッダーファイルとして使うことで、ヘッダーファイルの処理を省略する。

$ g++ -std=c++20 -Wall --pedantic-errors -include all.h -o sample sample.cpp
real    0m0.486s
user    0m0.390s
sys     0m0.074s

3. 簡単のため上の階層に保存するので以下の様にする
$ time g++ -std=c++20 -Wall --pedantic-errors -include 
../all.h -o sample sample.cpp
```