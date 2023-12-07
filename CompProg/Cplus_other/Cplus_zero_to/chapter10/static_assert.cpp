#include <bits/stdc++.h>
using namespace std;

/**
 * static_assert
 * コンパイル時に条件を満たさないとコンパイルエラーにする
 * 
 * 
*/

template <typename T, int N>
class Array{
    static_assert(N > 0, "サイズを0より大きくしてください");

public:
    int size() const {return N;}
    T data_[N];
};

int main(){
    Array<int, 9> a;
    cout << a.size() << endl;
    Array<int, 0> b;
    return 0;
    //error: static assertion failed: サイズを0より大きくしてください
}