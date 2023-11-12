#include <bits/stdc++.h>
using namespace std;

int N;
int A[100009], B[100009];
int main(){
    cin >> N;
    for (int i=1; i<=N; i++) cin >> A[i];

    //座標圧縮: Tはsortして重複を取ったarray
    vector<int> T;
    for(int i=1; i<=N; i++) T.push_back(A[i]);
    //重複削除
    sort(T.begin(), T.end());
    //.unique():重複を削除し、削除した末尾の次を指すiteratorを返す。コンテナサイズは変わらない
    //.erase(): コンテナサイズを削減
    T.erase(unique(T.begin(), T.end()), T.end());

    for(int i=1; i<=N; i++){
        //最小が0になっているので1足す
        B[i] = lower_bound(T.begin(), T.end(), A[i]) - T.begin() + 1;
    }
    for(int i=1; i<=N; i++){
        if(i >=2) cout << " ";
        cout << B[i];
    }
    cout << endl;
    return 0;
}