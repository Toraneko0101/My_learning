/**
 * 範囲に対する検索
*/
#include <bits/stdc++.h>
using namespace std;

int main(){
    //全ての要素が条件を満たすか
    //std::ranges::all_of(inFirst, inFast, unaryPred);
    //std::ranges::all_of(ranges, unaryPred);
    //戻り値はbool型で,空の場合はtrue
    //unaryPredは関数や関数オブジェクト
    //計算量はO(N)
    std::vector<double> v = { 36.2, 36.6, 36.9, 40.1, 37.2 };
    cout << boolalpha << ranges::all_of(v, [](double t){return t < 40.0; }) << endl;

    //反対にany_ofは一つでも要素を満たせばいい
    //範囲が空の場合はfalse
    cout << ranges::any_of(v, [](double t){return t < 36.3;}) << endl;

    //none_ofは条件を満たす要素が存在しないかを調べる
    //範囲が空の場合はtrue
    cout << ranges::none_of(v.begin() + 1, v.end(), [](double t){return t < 36.3;}) << endl;

    //指定した値と等しい要素の個数を数える
    //std::ranges::count
    cout << ranges::count(v, 36.9) << endl;

    //条件を満たす要素の個数を数えたい場合はcount_if
    cout << ranges::count_if(v | views::take(3), [](double t){return t >= 37.0;}) << "\n";

    //指定した値と等しい要素が最初に現れる位置を調べる
    //std::ranges::find (iteratorを返す)
    //そのためdistanceでアクセス
    cout << ranges::distance(v.begin(), ranges::find(v, 36.9)) << "\n"; //2

    //条件を満たす要素が最初に現れる位置を調べる
    //std::ranges::find_if
}
