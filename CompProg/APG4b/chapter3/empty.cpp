#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
using namespace std;

//空のコンテナに対する操作
//空のqueueに対する.frontや
//空のsetに対する*変数.begin()の動作を実行時エラーにする

int main(){
    queue<int> a;
    a.push(3);
    a.pop();
    cout << a.front() << endl;
    return 0;
}

/**
 *  std::queue<_Tp, _Sequence>::reference 
 * std::queue<_Tp, _Sequence>::front()
 *  [with _Tp = int; _Sequence = 
 * std::__debug::deque<int, std::allocator<int> >; 
 * reference = int&]: Assertion '!this->empty()' failed.
*/