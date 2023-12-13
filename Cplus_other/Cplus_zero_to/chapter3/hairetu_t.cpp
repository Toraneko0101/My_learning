#include <bits/stdc++.h>
using namespace std;

//3-1
/**
 * 配列を参照した際、先頭を指し示すポインタが取得できるのは
 * 配列が幾つかの例外を除いてポインタ型に暗黙変換されるから
 * 
 * 関数の引数宣言で配列型を使うと、ポインタ型として解釈される
 * 関数に配列を渡すのは、配列の先頭要素へのポインタを渡す事
 * void PrintArray1(const int x[5])
 * void PrintArray2(const int *x)
 * 要素数の情報は欠落する -> sizeでよさそう
 * 要素数の情報が欠落するのが配列がCから受け継いだものだから
*/

//vectorの場合：要素数の情報取得は容易
void vec_func(vector<int> &v){
    cout << size(v) << "\n";
    for(int i = 0; auto val : v){
        v.at(i) = val * 2;
        i++;
    };
}

//要素数を持つ必要があり、不便
void array_func(int *v, int s){
    // cout << size(v) << "\n"; //できない
    for(int i=0; i<s; i++){
        cout << v[i] << " ";
    }cout << "\n"; 
}

int main(){
    int x[] = {1,2,3};
    int *p = x;
    cout << *(p+1) << endl; //2

    int b[] = {1,2,3};
    array_func(b, (int)size(b));

    vector<int> a = {1,2,3};
    vec_func(a);
    cout << a.at(0) << "\n";
}