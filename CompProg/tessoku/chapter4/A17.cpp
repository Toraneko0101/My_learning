#include <bits/stdc++.h>
using namespace std;

int N;
int A[100009], B[100009];
int dp[100009];
vector<int> Ans;
int main(){
    cin >> N;
    for(int i=2; i<=N; i++) cin >> A[i];
    for(int i=3; i<=N; i++) cin >> B[i];
    dp[1] = 0;
    dp[2] = A[2];
    for(int i=3; i<=N; i++){
        dp[i] = min(dp[i-1]+A[i], dp[i-2]+B[i]);
    }

    //答えの復元
    //どこから移動してきたのか調べる
    int Place = N; //現在位置
    while(true){
        Ans.push_back(Place);
        if(Place == 1) break;
        //現在位置-1から移動してきた場合、合致するはず
        if(dp[Place - 1] + A[Place] == dp[Place]) Place -= 1;
        else Place -= 2;

    }

    //スタートからの経路にするため反転
    reverse(Ans.begin(), Ans.end());

    //答えを出力
    cout << Ans.size() << endl;
    for (int i=0; i<Ans.size(); i++){
        if(i >= 1) cout << " ";
        cout << Ans[i];
    }
    cout << endl;
    return 0;

}