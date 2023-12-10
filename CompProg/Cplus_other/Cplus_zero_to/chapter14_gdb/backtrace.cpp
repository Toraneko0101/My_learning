void f(){}

void apple(){ f(); }
void banana(){ f(); }
void cherry(){ apple(); }

int main(){
    f();
    apple();
    banana();
    cherry();
}

/**
 * (gdb) break f
 * (gdb) run
 * ⇒こうすると、関数fがどこから呼ばれたのか分からなくなる
 * 
 * <backtraceを用いる>
 * ※スタックフレーム：プログラムの実行中に関数呼び出しに関連する情報を格納するデータ構造
 * ※スタックという言葉に着目する。呼び出すたびに積み上げるので、topから　f -> apple -> mainという風に積んである感じ
 * (gdb) break f
 * (gdb) run
 * (gdb) backtrace
 * #0  f () at backtrace.cpp:1
 * #1  0x0000555555555171 in main () at backtrace.cpp:8
 * (gdb) c
 * //main() -> apple() -> f()と呼ばれていることが分かる
 * // #1が#0上のスタックフレームであることを意味する
 * #0  f () at backtrace.cpp:1
 * #1  0x0000555555555141 in apple () at backtrace.cpp:3
 * #2  0x0000555555555176 in main () at backtrace.cpp:9
*/