#include <bits/stdc++.h>
using namespace std;

/**
 * ビームサーチ
 * 貪欲法の場合は、一手先までしか求まらない
 * ビームサーチはスコアが上位k個となるものを残して探索を進める
 * 定数kはビーム幅と呼ばれる
 * ビーム幅が多ければいい値も残りやすくなるが、計算量が増える感じか
 * 具体的な操作手順は、辺を逆走することで得られる
 * 
 * ★i手目の終了時点での、第j位の盤面を保存する必要がある
 * C++のオブジェクトの代入は、深いコピーを行う
*/

struct State{
    int score;
    int X[29]; //長さ20の配列
    char LastMove; //最後の動きA or B
    int LastPos; //Beam[i-1][j]
};

//構造体の比較関数: スコアが大きい == operator>
bool operator>(const State& a1, const State& a2){
    if(a1.score > a2.score) return true;
    else return false;
}

//必要な変数、配列
// WIDTH:ビーム幅, NumState[i]:i手目時点での状態数
const int WIDTH = 10000;
const int N = 20;
int T, P[109], Q[109], R[109];
int NumState[109];
State Beam[109][WIDTH];
char Answer[109];

//ビームサーチを行う
void BeamSearch(){
    //0手目の状態数を設定
    NumState[0] = 1;
    Beam[0][0].score = 0;
    //配列の状態
    for(int i=1; i<=N; i++) Beam[0][0].X[i] = 0;

    //ビームサーチ: iはi手目
    for(int i=1; i<=T; i++){
        vector<State> Candidate;
        //前回の状態数分
        for(int j=0; j<NumState[i-1]; j++){
            //操作Aの場合
            State SousaA = Beam[i-1][j];
            SousaA.LastMove = 'A';
            SousaA.LastPos = j;
            SousaA.X[P[i]] += 1;
            SousaA.X[Q[i]] += 1;
            SousaA.X[R[i]] += 1;
            for(int k = 1; k<=N; k++){
                if (SousaA.X[k] == 0) SousaA.score += 1;
            }

            //操作Bの場合
            State SousaB = Beam[i-1][j];
            SousaB.LastMove = 'B';
            SousaB.LastPos = j;
            SousaB.X[P[i]] -= 1;
            SousaB.X[Q[i]] -= 1;
            SousaB.X[R[i]] -= 1;
            for(int k = 1; k<=N; k++){
                if (SousaB.X[k] == 0) SousaB.score += 1;
            }

            //候補に追加
            Candidate.push_back(SousaA);
            Candidate.push_back(SousaB);
        }
        //sortしてBeam[i]の結果を大きい順にする(比較対象は上で記述済み)
        sort(Candidate.begin(), Candidate.end(), greater<State>());
        NumState[i] = min(WIDTH, (int)Candidate.size()); //戻り値の型が違うのでキャスト, 最大WIDTHだけ残す
        for(int j = 0; j<NumState[i]; j++) Beam[i][j] = Candidate[j];
    }
}

int main(){
    cin >> T;
    for(int i=1; i<=T; i++) cin >> P[i] >> Q[i] >> R[i];

    //ビームサーチ
    BeamSearch();

    //ビームサーチの復元
    int CurrentPlace = 0; //配列Beamのどの位置を見ているか
    for(int i=T; i>=1; i--){
        Answer[i] = Beam[i][CurrentPlace].LastMove; //Lastに行った手順(Lastはスコアが1番いいものを選択するので)
        CurrentPlace = Beam[i][CurrentPlace].LastPos;
    }

    for(int i=1; i<=T; i++) cout << Answer[i] << endl;
    return 0;


}