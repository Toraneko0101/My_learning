#include <bits/stdc++.h>
using namespace std;

#include "something.hpp"

/**
 * inline
 * 定義が同一である場合に限り、異なるソースファイルで
 * 同一の定義を行ってもいい
 * inlineは両方に書く必要がある
*/

inline void Hello(){
    cout << "Hello" << endl;
}

int main(){
    Hello();
    Something();
    return 0;
}