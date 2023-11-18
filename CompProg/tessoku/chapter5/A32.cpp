#include <bits/stdc++.h>
using namespace std;

int N, A, B;
bool dp[100'009];
int main(){
    //先手必勝の状態で手番が回れば勝利,0になれば負けではなく、取れない状態になったら負け　-> A未満にすれば勝ち
    
    /**
     *　例えば、min(A,B)が2の時、0,1で手番が回ってくると負け
     *  min(A,B)=2, max(A,B)=3なら、負けの状態+3までで回ってくれば、自分の手番で石を負けの状態にできるので勝ち
     *  さらに1つ前の手番を考えると、負けの状態+3で相手に回してしまうと負けになる。
     *  逆に言えば、負けの状態+3+(1,2)で回ってくると、相手に回すときに負けの状態+(2,3)にしてしまうので負けになる
     * 
     * つまり、勝ちの状態とは、負けの状態に遷移するような行動が存在する
     * 負けの状態とは、負けの状態に遷移するような行動が存在しない, or取れる行動がない
     * trueの状態に遷移すれば、次の手番で自分がfalseになるのでダメ
    */

   //A < B;
   cin >> N >> A >> B;
   for(int i=0; i<=N; i++){
        if(i>=A && dp[i-A] == false) dp[i] = true;
        else if(i >= B && dp[i-B] == false) dp[i] = true;
        else dp[i] = false;
   }

    //先手はNの状態で最初に手番が回る
    if(dp[N]) cout << "First" << endl;
    else cout << "Second" << endl;
}