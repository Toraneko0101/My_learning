/**
 * 動的ライブラリ
 * 静的リンクはリンク時にobjectファイルをまとめるようだったが、
 * 動的ライブラリは、実行に必要な処理の一部を分割した外部ファイルを指す
 * ⇒実行時に解決する。ビルド時には依存関係の設定だけを行う
 * 
 * 1. 動的ライブラリ libhoge.soの作成
 * -sharedで共有ライブラリを作成
 * 生成する動的ライブラリのファイル名は-oで指定(これは普段もa.out以外を生成する場合はそう)
 * $ g++ -std=c++20 -shared -o libhoge.so add.o sub.o
 * 
 * 2. 動的ライブラリの子依存関係はlddで確認可能
 * $ g++ -std=c++20 static_link.o libhoge.so
 * $ g++ -std=c++20 static_link.o libhoge_another.so
 * $ ldd a.out
 * libhoge.so => ./libhoge.so (0x00007ff7f3102000)
 * 
 * libhoge.so => not foundと出力される場合は
 * export LD_LIBRARY_PATH=.を実行する事
 * 
 * ※依存関係は動的ライブラリにも存在する
 * $ ldd /lib/x86_64-linux-gnu/libc.so.6
 *       /lib64/ld-linux-x86-64.so.2 (0x00007f7f38ed6000)
 *       linux-vdso.so.1 (0x00007ffd6af2d000)
 * 
 * ※依存関係は子依存だけでは完結せず、連鎖して発生する
 * 
 * 子依存がない場合は以下の様になる
 * $ ldd libhoge.so
 *      statically linked
 * 
 * ★静的ライブラリと動的ライブラリの使い分け
 * ・objファイルから作成するのは同一
 * ・静的⇒ビルド時にリンクする
 * ・動的⇒実行ファイルを起動したタイミングでリンクする 
 * 
 * 静的リンク⇒プログラムに必要なすべてのライブラリを、
 * リンカを介して実行ファイルに直接コピー
 * 動的リンク⇒実行時にライブラリを実行ファイルにコピー。依存関係だけ事前に整理しておく
 * つまり、プログラムの実行時にのみライブラリはメモリにロードする
 * ⇒★つまり、a.outを作成した後で、libhoge_another.soの中身を変えて、実行結果を変更することも可能ってことか
 * 
 * ⇒静的リンクと異なりまだライブラリはコピーされていないので以下が可能
 * 1. g++ -std=c++20 -c another_sub.cpp
 * 2. g++ -std=c++20 -shared -o libhoge.so add.o another_sub.o
 * 3. g++ -std=c++20 static_link.o libhoge.so(依存関係を整理)
 * 4. ./a.out 
 * 5. another_sub.cppの中身を変更
 * 6. g++ -std=c++20 -c another_sub.cpp
 * ※libhoge.soの中身を変更
 * 7. g++ -std=c++20 -shared -o libhoge.so add.o another_sub.o
 * 8. a.out (再コンパイルは行っていないが中身が変わっている)
 * 
*/

/**
 * 以下、phindに尋ねた内容
 * つまり、静的リンクの場合は、
 * g++ -std=c++20 static_link.o libhoge.a
 * のようにした場合、実行結果を変更したいなら再度、libhoge.aを変更し、
 * 再びg++ -std=c++20 static_link.o libhoge.aを実行しなくてはならないが、
 * 動的リンクの場合
 * 一度、g++ -std=c++20 dynamic_link.o libhoge.soとして依存関係を整理した実行ファイルを作成しておけば、libhoge.soの中身を変えるだけで、
 * 再度リンクしなくても実行結果を変えられるという理解でいいですか？
 * 
 * A. yes。
 * 動的リンクの場合は、ライブラリの中身を変更した場合でもライブラリを再度リンクする必要はない
 * これは実際のリンクが実行時に行われるため
 * ライブラリを再度ロードすればそれで事足りる。
 * 静的リンクは実行前にすでにリンクしているので、エラー発生時のデバッグなどが難しい
 * その分、静的リンクは、実行時にライブラリやオブジェクトファイルを読み込まないので実行速度が高速になる
*/


//lオプションについて
/**
 * -lオプションを使うとライブラリのプレフィックスlibと
 * サフィックス.soや.aを省略可能
 * ★ライブラリ名がlibから始まらない場合でも、指定は正しく機能する
 * /usr/libにあるなら(通常はカレントも) -lfooだけでコンパイラはfoo.soなどを確認可能
 * -L /path/to/Library -lfooとすればライブラリの検索パスも追加可能
 * 仮にカレントが、検索パスに含まれなくなっている場合 -L.とすればいい
 * 
 * 使用例)
 *  g++ -std=c++20 static_link.o libhoge.so
 *  g++ -std=c++20 static_link.o -L. -lhoge
*/

