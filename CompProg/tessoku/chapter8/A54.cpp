#include <bits/stdc++.h>
using namespace std;

int main(){
    int Q;
    cin >> Q;
    unordered_map<string, int> scores;
    for(int i=0; i<Q; i++){
        int query;
        cin >> query;
        if(query == 1){
            string name;
            int score;
            cin >> name >> score;
            scores[name] = score;
        }
        else if(query == 2){
            string name;
            cin >> name;
            cout << scores[name] << endl;
        }
    }
    return 0;
}