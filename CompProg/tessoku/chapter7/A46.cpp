#include <bits/stdc++.h>
using namespace std;

//貪欲法
int N;
double X[159], Y[159];
bool visited[159];
vector<int> keiro;

double getDistance(int a, int b){
    return sqrt(pow(X[a]-X[b], 2) + pow(Y[a]-Y[b],2));
}

int main(){
    cin >> N;
    for(int i=1; i<=N; i++) cin >> X[i] >> Y[i];
    for(int i=1; i<=N; i++) visited[i] = false;

    //最初は1からスタート
    keiro.push_back(1);
    visited[1] = true;
    int now_target = 1; //今の位置
    int next_target = -1; //次の位置

    //N+1-2回
    for(int i=1; i<N; i++){
        double now_distance = 0.0;
        double min_distance = 100000; //現在位置からの最短距離

        for(int j=1; j<=N; j++){
            if(visited[j] == true) continue;
            now_distance = getDistance(now_target, j); //距離
            if(now_distance < min_distance){
                min_distance = now_distance;
                next_target = j;
            }
        }
        //現代位置を更新
        now_target = next_target;
        visited[next_target] = true;
        keiro.push_back(next_target);
    }

    //出発点に戻る
    keiro.push_back(1);

    //出力
    for(int row : keiro){
        cout << row << endl;
    }
    return 0;
}