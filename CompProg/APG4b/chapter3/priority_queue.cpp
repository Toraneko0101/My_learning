#include <bits/stdc++.h>
using namespace std;

int main(){
    priority_queue<int> pq;
    pq.push(10);
    pq.push(19);
    pq.push(14);
    pq.push(18);
    while(!pq.empty()){
        cout << pq.top() << "\n";
        pq.pop();//最大の値を捨てる
    }
    /**
     * 要素の追加はlogN
     * 削除もlogN
     * 最大の取得はO(1)
    */

   //最小の要素を取り出す
   priority_queue<int, vector<int>, greater<int>> min_pq;
   min_pq.push(10);
   min_pq.push(19);
   min_pq.push(14);
   min_pq.push(18);
    while(!min_pq.empty()){
        cout << min_pq.top() << "\n";
        min_pq.pop();//最小の値を捨てる
    }   

}