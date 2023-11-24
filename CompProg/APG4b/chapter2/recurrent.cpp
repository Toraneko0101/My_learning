#include <bits/stdc++.h>
using namespace std;

// //引数、返り値、処理内容を決める
// //ベースステップと再帰ステップを決める
// int test_gcc(int x, int y){
//     if(y == 0) return x;
//     return test_gcc(y, x%y);
// }

// int main(){
//     cout << test_gcc(78, 117) << "\n";
// }

int complete_time(vector<vector<int>> &children, int x){
    if(children.at(x).size() == 0) return 0;

    //再帰ステップ
    int max_receive_time = 0;
    //子要素のうち1つについて
    for(int c: children.at(x)){
        //子要素のもとに書類がそろった時間 +1: 0の子要素が1,2,4なら、それについて再帰する。
        int receive_time = complete_time(children, c) + 1;
        max_receive_time = max(max_receive_time, receive_time);
    }
    return max_receive_time;
}

int main(){
    int N;
    cin >> N;
    vector<int> p(N);
    p.at(0) = -1;
    for(int i=1; i<N; i++) cin >> p.at(i);

    //2次元配列
    vector<vector<int>> children(N); //親要素idxごとの子要素一覧
    for(int i=1; i<N; i++){
        int parent = p.at(i);
        children.at(parent).push_back(i); //子供を追加
    }
    //全ての親は0なので、
    cout << complete_time(children, 0) << endl;
}