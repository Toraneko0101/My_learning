/**
 * debugの行い方
 * gccの場合は、gdb
 * 
 * 通常のビルド⇒リリースビルド
 * :実行時に不要な情報を省いて最適化を行い、performanceを高めている
 * 
 * そのため-gオプションを付け、デバッグビルドを行う
 * $ g++ -std=c++20 -g program.cpp program
 * $ gdb program
 * 
 * (gdb) quit(or q) :終了
 * (gdb) run(or r) :開始
 * ⇒オプションを指定したい場合、たとえば標準出力をリダイレクトしたいときは以下
 * (gdb) run > out.txt
 * ※breakpointが設定されていないと終了まで到達する
 * 
 * <breakpointの設定方法>
 * (gdb) break ファイル:行番号
 * (gdb) break 関数名
 * 
 * 例)
 * (gdb) b main.cpp:6
 * 
 * <breakpointの確認>
 * (gdb) info breakpoints
 * (gdb) i b
 * 
 * Num: breakpointのidx
 * Type: 種類
 * Disp: 中断後の処理
 * Enb: 有効 or 無効
 * Address: アドレス
 * What: 内容
 * 
 * <Enbの切り替え>
 * (gdb) disable 1
 * (gdb) enable 1
 * //breakpointのnum1が10回発動したら自動的に無効化
 * (gdb) enable 1 count 10
 * 
 * ★<条件分岐>
 * (gdb) break 7 if val == 10
 * ⇒変数valが10であり、かつ7行目が実行されるタイミングでbreakpointが発動
 * 
 * <関数に関して>
 * (gdb) break func
 * ⇒関数内のすべての行にbreakpointが降られる
 * 3行とすると、1.1 1.2 1.3という風になり、
 * 大本の1をdeleteすると、子供はすべて削除される
 * 
 * <breakpointの削除>
 * (gdb) d 1
 * (gdb) delete 1
 * ⇒1というのはinfoで確認したnum。
 * 数値を指定しないとすべてのbreakpointsを削除する
 * 
 * <プログラムの再開>
 * (gdb) continue(or c)
 * 
 * <現在の変数の値を確かめる>
 * ※実行する前に留まるので表示されている行の一行前までの結果になっていることに注意
 * (gdb) print val
 * (gdb) p val
 * 
 * <printした結果の再利用>
 * ※値を確認すると
 * $n = 値
 * という風に出力されるので、
 * (gdb) print $1
 * という風に結果を再利用可能
 * 
 * <list>
 * 現在のソースファイルの前後10行を表示する
 * 
 * <step実行>
 * (gdb) stepで1行分の実行を行い続ける
 * <複数行step>
 * (gdb) step 3: 3行分実行される
 * 
 * <next実行>
 * stepは関数内の1行も1行とカウントする
 * nextは関数内の呼び出しをすべて実行して1行とみなす
 * 
 * <finish>
 * 現在の関数からrtnするまで実行
 * 
 * next = step_over
 * step = step_in
 * finish = step_out
 * 
 * <ポインタに対する操作>
 * (gdb) print &a
 * (gdb) print *a
*/

/**
 * その他
 * 
 * <バックトレース>
 * =>backtrace.cppに記載。どこから呼ばれたか確認するためのもの
 * <関数とbreakpoint(オーバーロード編)>
 * ⇒overload.cppに記載
 * 
 * <printの注意点>
 * print Test(b,a)という風に関数を呼べる
 * print val++ともできてしまう
 * ⇒副作用があるので注意する事
 * 
 * <signalによるプログラムの中断>
 * ⇒signal.cppに
 * 
 * <その他便利な機能>
 * set pretty print on
 * ⇒クラスや構造体を表示する際に見やすくなる
 * 
 * set pagination off
 * ⇒ページ送りをしない
 * ⇒そのままコピーする際に便利かも
*/