#include <bits/stdc++.h>
using namespace std;

int main(){
    int N;
    cin >> N;
    vector<pair<string, int>> Mt;

    for(int i=0; i<N; i++){
        //入力
        string S;
        int T;
        cin >> S >> T;
        Mt.emplace_back(S,T);
    }

    //sort(target, comp, projection)
    std::ranges::sort(Mt, std::greater{}, &pair<string,int>::second);

    cout << Mt.at(1).first << endl;
}