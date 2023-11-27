#include <bits/stdc++.h>
using namespace std;

//最小、最大を取得するにはO(1)のset
int main(){
    int Q;
    cin >> Q;
    set<int> card;
    for(int i=0; i<Q; i++){
        int query;
        cin >> query;
        if(query == 1){
            int num;
            cin >> num;
            card.insert(num);
        }
        else if(query == 2){
            int num;
            cin >> num;
            card.erase(num);
        }
        else if(query == 3){
            int num;
            cin >> num;
            //setはlower_boundを行える。小さい順に並んでいるので
            //x以上のカードがない場合はendを指す
            auto itr = card.lower_bound(num);
            if(itr == card.end()) cout << "-1" << endl;
            else cout << (*itr) << endl; //iteratorの指す要素へアクセス
        }
    }
    return 0;
}
