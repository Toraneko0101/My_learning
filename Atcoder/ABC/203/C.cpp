#include <bits/stdc++.h>
using namespace std;
using Int = long long;

int main(){
    Int N, K;
    cin >> N >> K;
    vector<pair<Int, Int>> vec;
    for(int i=0; i<N; i++){
        Int A, B;
        cin >> A >> B;
        vec.emplace_back(A,B);
    }

    //sort
    std::ranges::sort(vec, {}, &pair<Int,Int>::first);
    deque<pair<Int, Int>> friends(vec.begin(), vec.end());
    Int now_money = K;
    Int now_place = 0;
    while(!empty(friends)){
        Int next_place = friends.front().first;
        Int money = friends.front().second;

        Int kyori = next_place - now_place;
        if(now_money < kyori) break;
        else{
            now_money += (money - kyori);
            now_place = next_place;
        }
        friends.pop_front();        
    }

    cout << now_place + now_money << endl;
}