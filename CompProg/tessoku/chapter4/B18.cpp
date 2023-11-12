#include <bits/stdc++.h>
using namespace std;

//n枚の時、この値になるものは存在するか。復元しないなら1次元で行ける
int N, S, A[69];
bool dp[69][10009];

int main(){
    cin >> N >> S;
    for(int i=1; i<=N; i++) cin >> A[i];
    //dp
    dp[0][0] = true;
    for(int i=1; i<=S; i++) dp[0][i] = false;

    for(int i=1; i<=N; i++){
        for(int j=0; j<=S; j++){
            if(j >= A[i]){
                if(dp[i-1][j] == true || dp[i-1][j - A[i]] == true) dp[i][j] = true;
                else dp[i][j] = false;
            }else{
                if(dp[i-1][j] == true) dp[i][j] = true;
                else dp[i][j] = false;
            }
        }
    }

    if(dp[N][S] == false){
        cout << -1 << endl;
        return 0;
    }
    //復元
    int yPlace = N;
    int xPlace = S;
    vector<int> ans;
    while(true){
        //現在のカードを使ったかどうか判定。使った場合はdp[N-1][S - A[N]]がtrueなはず
        if(xPlace == 0 || yPlace == 0) break;
        if(dp[yPlace-1][xPlace - A[yPlace]] == true){
            ans.push_back(yPlace);
            xPlace -= A[yPlace];
            yPlace -= 1;
        }else{
            yPlace -= 1;
        }
    } 

    reverse(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for(int i=0; i<ans.size(); i++){
        if(i>=1) cout << " ";
        cout << ans[i];
    }
    cout << endl;
    return 0;

    return 0;
}
