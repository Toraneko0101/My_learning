#include <bits/stdc++.h>
using namespace std;

int main(){
    //型の省略
    vector<int> c  = {1,2,3};
    for(auto elem : c) cout << elem << "\n";

    //endl vs \n
    //endlは\nしてから、出力ストリームをflushする
    //\nの場合は、データはまだバッファにあり、出力装置に送り出されてはいない
    //ただし出力先がterminalなどの対話的なデバイスである場合は、\nでバッファは自動的にフラッシュされる
    //また、プログラムの終了時(0,1)には、バッファは自動的にフラッシュされる。
    //つまり、terminalに標準出力したい場合は、endlを使う必要はない。遅くなるだけだし。でも可読性は上がりそう
}   