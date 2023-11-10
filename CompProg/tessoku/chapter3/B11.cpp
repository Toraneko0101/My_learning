#include <bits/stdc++.h>
using namespace std;

int N, Q;
int A[100009], X[100009];


int main(){
    cin >> N;
    for (int i=1; i<=N; i++) cin >> A[i];
    cin >> Q;
    for (int i=1; i<=Q; i++) cin >> X[i];

    sort(A + 1, A + N + 1);
    //lower_boundなら指定された要素以上。upper_boundなら指定された要素より上
    for (int i=1; i<=Q; i++){
        //配列の場合、ポインタを返すので注意する事
        int *pos = lower_bound(A + 1, A + N + 1, X[i]);
        //Aは0のidxからなので、余計に1つ引く
        cout << (int)(pos - A - 1) << endl;
    }
    return 0;
}