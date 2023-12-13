#include <bits/stdc++.h>
using namespace std;

//型推論など
//decltypeは式から型を決めるもの
template <typename T, typename U>
auto sum(T a, U b) -> decltype(a + b){
    return a + b;
}

//定数template:コンパイル時に定まる
template <int N>
void test(){
    int a[N];
    if (N >= 1) a[0] = 9;
    cout << a[0] << "\n";
}


int main(){
    cout <<  sum(10, 1.2) << endl;
    test<10>();
}