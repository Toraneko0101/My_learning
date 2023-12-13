#include <bits/stdc++.h>
using namespace std;

int main(){
    /**
     * 0,1,6,8,9
    */
    string S; cin >> S;
    for(auto &s: S){
        if(s == '6'){
            s = '9';
            continue;
        }
        if(s == '9'){
            s = '6';
        }
    }

    std::ranges::reverse(S);
    cout << S << endl;
}