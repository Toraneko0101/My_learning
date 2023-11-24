#include <bits/stdc++.h>
using namespace std;

//多次元配列

int main(){
    int x, y;
    x = 9, y = 10;
    //初期値を省略した場合、intなら0, strなら空文字
    //縦の要素数は変数名.size():1次元目の要素数が取得可能
    //横の要素数は変数名.at(0).size()
    //arrayや配列は要素数に変数を使えないので簡潔だが不便
    vector<vector<int>> data(y, vector<int>(x));
    for(int i=0; i < data.size(); i++){
        for(int j=0; j < data.at(0).size(); j++ ) data.at(i).at(j) = i * j;
    }

    for(const auto& row : data){
        for(const auto& point : row){
            printf("%3d", point);
        }
        cout << endl;
    }

    //長方形にならない二次元配列：ジャグ配列
    vector<vector<int>> data1(2);
    vector<int> data_child = {1,2,3};
    data.at(0).push_back(1);
    data.at(0).push_back(2);
    data.at(1) = data_child;
    cout << data.at(1).at(2) << "\n";

    //1次元の配列を多次元配列として使う
    int H = 3, W = 4;
    vector<int> data2(H * W);
    for(int i=0; i<H; i++){
        for(int j=0; j<W; j++){
            data2.at(i*H + j) = i*H + j;
        }
    }
}