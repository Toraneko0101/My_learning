#include <bits/stdc++.h>
using namespace std;

int N, A, B;


int main(){
    cin >> N >> A >> B;
    //(2)なら[0,0]
    //{2}なら[2]
    //(3,4)なら[4,4,4]
    //{3,4}なら{3,4}
    vector<string> S(N);
    for(auto &str: S) cin >> str;

    if(S[A][B] == 'o') cout << "Yes" << endl;
    else cout << "No" << endl;

    return 0;
}