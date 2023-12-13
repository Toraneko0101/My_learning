#include <bits/stdc++.h>
using namespace std;

/**
 * 答えは4桁の文字列
 * 重複順列
*/

int main(){
    string zyouken;
    cin >> zyouken;

    //o,?,xのcnt
    int o_count = 0, q_count = 0, x_count = 0;
    unordered_set<int> o_set;
    unordered_set<int> x_set;
    for(int i = 0; auto s: zyouken){
        if (s == 'o'){
            o_count ++;
            o_set.insert(i); //oである番号をsetに追加
        }
        else if(s == '?') q_count++;
        else{
            x_count++;
            x_set.insert(i); //xである番号をsetに追加
        }
        i++;
    }

    //0~9999まで条件を満たしているかチェック
    int ans_cnt = 0;
    for(int i=0; i<10000; i++){
        int num = i;
        string str_num = std::to_string(num);
        //0-padding
        while(size(str_num) < 4) str_num = "0" + str_num;
        
        bool flag = true;
        for(auto o: o_set){
            auto it_o = std::ranges::find(str_num, (char)(o + '0'));
            if(it_o == str_num.end()) flag = false;
        }
        for(auto x: x_set){
            auto it_x = std::ranges::find(str_num, (char)(x + '0'));
            if(it_x != str_num.end()) flag = false;
        }

        if(flag) ans_cnt ++;

    }
    cout << ans_cnt << "\n";
}


