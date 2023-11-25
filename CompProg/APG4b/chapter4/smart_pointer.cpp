#include <bits/stdc++.h>
using namespace std;
  /**
   * スマートポインタ
   * メモリ確保を安全に楽に行うためのもの
   * std::unique_ptr
   *    メモリの所有権をやり取りし、不要になったタイミングで自動的に開放する
   *    常に1つのunique_ptrが所有権を持っており、持っていないポインタからは対象のメモリ領域を触れない。
   * 
   * std::shared_ptr
   *    複数のshared_ptrが所有権を持っている。
   *    循環参照が生じた場合にメモリが回収できなくなる問題がある
   *    weak_ptrを用いることで循環参照は回避可能
   * 
  */

int main(){
    //unique_ptr
    unique_ptr<int> p1 = make_unique<int>(123);
    *p1 += 1;
    cout << *p1 << endl;

    unique_ptr<int> p2;
    p2 = move(p1); //メモリの所有権を移動
    //*p1 += 10; //所有権を失ったのでこれはエラー
    *p2 += 1;
    cout << *p2 << endl;

    //shared_ptr
    shared_ptr<int> s1;
    {
        shared_ptr<int> s2 = make_shared<int>(123);
        {
            shared_ptr<int> s3 = s2; //s3も所有権を共有
            *s3 += 1;
            s1 = s3; //s1も所有権を共有
        } //s3が所有権を手放す(s1, s2)
        *s2 += 1; 
    } //s2が所有権を手放す
    *s1 += 1;
    cout << *s1 << endl;
} //ここでp2の持っていた所有権が無効になり自動的にメモリを解放
//sharedの場合も所有者がいなくなり、メモリが解放。スコープの外側で定義したものは内側でも使える。逆は無理なので。