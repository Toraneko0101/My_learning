#include <bits/stdc++.h>
using namespace std;
//区間スケジューリング問題
int N;
int L[300009];
int R[300009];
vector<pair<int, int>> tmp;

int main(){
    cin >> N;
    for(int i=1; i<=N; i++){
        cin >> L[i] >> R[i];
        //pairの作成
        tmp.push_back(make_pair(R[i], L[i]));
    }

    sort(tmp.begin(), tmp.end());
    //戻す
    for(int i=1; i<=N; i++){
        R[i] = tmp[i-1].first;
        L[i] = tmp[i-1].second;
    }

    //計算
    int Answer = 0;
    int end_time = 0;
    for(int i=1; i<=N; i++){
        if(end_time <= L[i]){
            Answer++;
            end_time = R[i];
        }
    }
    cout << Answer << endl;
    return 0;

}