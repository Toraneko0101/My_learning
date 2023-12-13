/**
 * 
 * standard_layout
 * 
 * 型Tがstandard_layout型ならtrue_typeから派生
 * ちがえばfalse_typeから派生
 * 
 * standard_layout型は以下のすべてを満たす
 * ・非standard_layout型の非静的メンバ変数 or 参照を持たない
 * ・仮想関数を持たず、仮想基底関数を持たない
 * ・非standard_layout型の基底クラスを持たない
 * ・最派生クラスに非静的メンバ変数を持つ場合、基底に非静的メンバ変数を持たない
 * ・最初の非静的メンバ変数と同じ基底クラスを持たない
 * 
 * 組み込み型はすべてstandard_layout
*/

#include <bits/stdc++.h>
using namespace std;

struct X{
    int n;
    char C;
};

static_assert(
    std::is_standard_layout<int>::value == true,
    "int is standard_layout type"
);

static_assert(
    std::is_standard_layout<X>::value == true,
    "X is standard-layout type"
);

int main(){}