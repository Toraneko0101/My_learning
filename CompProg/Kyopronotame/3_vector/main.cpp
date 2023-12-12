#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<int> num;
    for(auto n : std::views::iota(0,10)){
        num.emplace_back(n);
    }
    cout << size(num) << "\n";

    vector<int> vec(100,5); //100個の5

    //template引数の省略:型推論できる場合
    vector num1 = {1,2,3};
    //size, capasity,emptyなどはstrと同一
    //アクセスについても同一

    //要素数が異なるリストの代入
    //⇒変換できる型ならいい
    vector<double> vec1 = {10.1, 20.2, 30.3, 40.4};
    vec1 = {10,20,30};

    //vectorからvectorへの代入
    //型は一致している必要がある
    vector<int> vec2 = {10,20,30};
    vector<double> vec3;
    //vec1 = vec2; //error
    for(auto v : vec2) vec3.emplace_back((double)v);
    vec1 = vec3;

    //末尾に配列を追加
    vector<int> a = {1,2,3,4};
    vector<int> other = {5,6,7};
    a.insert(a.end(), other.begin(), other.end());
    //末尾に配列を追加(C++23)
    //a.append_range(other);

    //削除や、メモリ占有の削除に関してはstrと同一
    a.erase(a.begin() + 3, a.begin() + 5);
    copy(a.begin(), a.end(), ostream_iterator<int>(cout, ", "));
    cout << endl;

    /**
     * std::vector<bool>について
     * 1byteにbool型の値を8個分記録している
     * 上記は個別の要素への参照やポインタを取得できない
     * front, back, atなどは、プロキシと呼ばれる特殊なオブジェクトを返す
     * 
    */
    vector<bool> booleans = {false, false, false};
    auto b = booleans.front();
    b = true;
    //booleans[0]が変更できている。これはbool型のvecだけ
    cout << boolalpha << booleans.front() << "\n";
    //.flip():配列内のfalse,trueをすべて反転
    booleans.flip();

    /**
     * std::vector<bool>の特殊な挙動を回避したい場合
     * cha⇒bool型の値を代入できる
     * basic_string<bool> ⇒要素の個数のみでの構築ができない
     * std::basic_string<bool> booleans(100, false);ならOK
     * 
     * std::deque<bool>
     * ⇒要素がメモリ連続で配置されないので、使用法によっては実行時性能が低下する
    */
}