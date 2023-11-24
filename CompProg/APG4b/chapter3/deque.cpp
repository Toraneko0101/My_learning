#include <bits/stdc++.h>
using namespace std;

int main(){
    deque<int> d;
    d.push_back(10); //10
    d.push_front(11); // 11, 10
    d.pop_front(); // 10
    cout << d.front() << "\n"; //10
    d.push_back(12); //10,12
    d.pop_back(); //10
    d.push_back(13); //10,13
    cout << d.at(1) << endl; //13 (おそらく計算量はN)
    cout << d.back() << endl; //13
    cout << d.size() << endl; //2

    /**
     * 空のdequeに対して,frontやbackを呼んだ際の動作は未定義
     * i番目の要素などの操作は遅いが、両端は早い
    */
}