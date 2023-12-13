void f(){}
void f(int){}
void f(double){}

int main(){
    f();
    f(0);
    f(0.0);
}
/**
 * fに対してbreakpointを適用したい
 * (gdb) break fとすると
 * 関数名fに該当するすべての関数にbreakpoint1としてbreakpointが設定されてしまう
 * 
 * これを解決したい
 * (gdb) set multiple-symbols ask
 * (gdb) break f
 * 
 * //オプションが表示される
 * [0] cancel
 * [1] all
 * [2] test1.cpp:f()
 * [3] test1.cpp:f(double)
 * [4] test1.cpp:f(int)
 * 
 * //適用したい番号を選択
 * > 2 4
 * Breakpoint 2 at 0x1131: file test1.cpp, line 1.
 * Breakpoint 3 at 0x113f: file test1.cpp, line 2.
*/