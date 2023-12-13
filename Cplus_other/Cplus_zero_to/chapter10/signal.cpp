#include <bits/stdc++.h>
using namespace std;

/**
 * [シグナル]
 * プログラム実行中に外部から要求を通知する仕組み
 * OSからのエラー通知などで使用]
 * 
 * SIGABRT
 * std::abortの呼び出しによって発生
 * abortは異常終了した際のterminate等から呼び出される
 * 
 * SIGFPE
 * 整数の0除算などで発生
 * 
 * SIGSEGV
 * 無効なメモリアクセスで発生
 * 
 * ※詳しくないうちはハンドルすべきではないと思う
 * SIGINTをサンプルとして用いる分には問題ないと思うけど
 * 
*/

void signalHandler(int signum){
    cout << format("Interrupt signal({}) received.\n", signum);

    //プログラムを終了
    std::exit(signum);
}

int main(){
    //Ctrl + C
    //std::signal(int signal, handler);
    //信号sigをhandlerがさすハンドラに設定する
    std::signal(SIGINT, signalHandler);
    cout << "Running...\n";

    //待機用
    while(true){}

    return 0;
}

