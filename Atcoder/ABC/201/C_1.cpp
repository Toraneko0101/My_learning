//もう少しスマートに書く

#include <bits/stdc++.h>
using namespace std;

int main(){
    std::string s; cin >> s;
    int ans = 0;
    for(int i=0; i<10000; i++){
        vector<bool> flag(10); //0~9
        int x = i;
        //1回以上登場するか
        for(int j=0; j<4; j++){
            flag.at(x % 10) = true;
            x /= 10;
        }

        bool flag2 = true;
        for(int j=0; j<10; j++){
            if(s[j]=='o' && !flag[j]) flag2 = false;
            if(s[j]=='x' && flag[j]) flag2 = false;
        }
        ans += flag2;
    }
    cout << ans << "\n";

}