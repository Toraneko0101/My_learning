#include <bits/stdc++.h>
using namespace std;
/**
 * std::ranges名前空間のものを使うことで
 * より便利でわかりやすいエラーメッセージを得られる
*/

int main(){
    //min(a,b) : a,bのうち小さい値へのconst参照を返す
    cout << ranges::min(10,8) << endl;
    cout << ranges::max(10,8) << endl;
    //std::minの場合、std::min<Type>(a,b)と明示することで、一方がTypeに変換
    cout << max<double>(8,1.2) << endl;
    //std::ranges::minの場合、static_castでそろえる
    cout << ranges::min(8.2, static_cast<double>(9)) << "\n";

    //3つ以上
    cout << min({3,4,5}) << endl;

    //空でない範囲から最小、最大の要素を得る
    vector<int> v = {70,60,50,90};
    cout << ranges::min(v) << "\n";
    cout << ranges::min(v | views::take(2)) << "\n";

    //配列の中から最小の要素とその位置を求める(最大も同様)
    /**
     * std::min_element(inFirst, inLast)　: O(N)
     * std::ranges::min_element(inFirst, inLast)
     * std::ranges::min_element(range)
     * ⇒最小の要素の位置を指すイテレータを返す
     * ⇒範囲の要素数が0の場合、範囲の終端イテレータを返す
     * 
     * //配列の何番目にあるかを得る
     * std::distance(inFirst, inLast) : ランダムアクセスイテレータでない限り、O(1)
     * 
    */
    vector<int> v1 = {-5, 10, 40, -20, 50, 0};
    auto it = std::ranges::min_element(v1);
    cout << *it << endl;
    cout << std::ranges::distance(v1.begin(), it) << "\n";

    /**
     * 小さい方と大きい方の値を同時に得る
     * std::minmax(a,b)
     * ⇒const参照を組にしたstd::pairをrtn
     * std::ranges::minmax(a,b)
     * ⇒std::ranges::min_max_resultを返す .min, .max
     * 
     * ⇒比較の回数を減らせるメリットがあり
     * ⇒戻り値は構造化束縛で受け取れる
    */

    int a1 = 30, a2 = 60;
    auto minmax = std::ranges::minmax(a1, a2);
    cout << "min: " << minmax.min << ", max: " << minmax.max << "\n";
    auto [min, max] = std::minmax(a1, a2);
    cout << min << " " << max << "\n";

    /**
     * 3つ以上の値から、最小値と最大値を一度に得る
    */
    vector<int> v2 = {30,60,50,70};
    auto minmax1 = std::ranges::minmax(v2);
    cout << minmax1.min << " " << minmax1.max << "\n";
    int a3 = 30, a4 = 60, a5=7;
    auto [min1, max1] = std::minmax({a3,a4,a5});
    cout << min1 << " " << max1 << "\n";

    //配列の中から最小の要素と最大の要素、およびそれらの位置を一度に得る
    /**
     * std::ranges::minmax_element(itFirst, itLast) //rangeでも可
     * 
    */
    vector<int> v3 = v2;
    auto minmax2 = ranges::minmax_element(v3);
    cout << "min: " << *minmax2.min << ", max: " << *minmax2.max << "\n";
    cout << "min_at: " << std::ranges::distance(v3.begin(), minmax2.min) << "\n"; 
    cout << "max_at: " << std::ranges::distance(v3.begin(), minmax2.max) << "\n"; 

    //ある値を指定した最小値と最大値の範囲に収める
    //std::ranges::clamp(val, min, max);

    cout << ranges::clamp(20,0,10) << "\n";
}   
