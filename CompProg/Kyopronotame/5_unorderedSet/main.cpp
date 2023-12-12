#include <bits/stdc++.h>
using namespace std;

/**
 * setは大小関係を保持するので、<の定義が必要
 * unordered_setは要素のハッシュ関数と==が定義されている必要あり
 * ⇒ユーザ定義型をunordered_setの要素にするためには
 * ==を定義し、std::hash<Type>の特殊化が定義されている。
*/

int main(){
    //リストから構築
    unordered_set<int> num = {1,4,5,10,10,50};
    //vectorから構築
    vector<int> v(10);
    iota(v.begin(), v.end(), 1);
    unordered_set<int> num1(v.begin(), v.end());
    for(auto n : num1) cout << n << " ";
    cout << "\n";
    //別のusから構築
    unordered_set<int> num2 = num;
    //cinから構築することもできる
    unordered_set<int> num3; //値が追加されたときは.secondがfalseを返す
    // for(int i=0; i<3; i++){
    //     int n;
    //     cin >> n;
    //     num3.insert(n);
    // }
    // cout << size(num3) << "\n";

    //代入時はvecと同じで、
    //unordered_setなら型一致。listの代入なら型変換できればOK
    num = num2;

    //ハッシュテーブル同士を比較可能
    if(num == num2) cout << "Yes" << "\n";

    //C++20 containsで指定したキーがあるか調べられる
    if(num2.contains(4)) cout << "Yess\n";
    //追加はinsert,削除はerase, clearでhash
    //swapで交換。ranges::swapはC++20から

    /**
     * デフォルトのハッシュ関数について
     * ハッシュ関数の性質を逆手にとって
     * 最悪計算量O(N)の状態にさせられてしまうケースがある
     * その場合は、自分でhash関数を作らなければならない
     * 
    */

    /**
     * unordered_set<
     *  class Key,
     *  class Hash = std::hash<Key>,
     *  class Pred = std::equal_to<Key>,
     *  class Allocator = std::allocator<Key>
     * >
    */


    
}