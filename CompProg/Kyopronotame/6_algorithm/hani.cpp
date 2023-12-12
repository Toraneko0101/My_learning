
#include <bits/stdc++.h>
using namespace std;

void Print(auto &vec){
    for(auto v : vec) cout << v << " ";
    cout << "\n";
}

struct Person{
    string name;
    int age;
};

int main(){
    /**
     * 範囲に対する検索
     * rangesは範囲をそのまま扱える
    */
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
    auto it = ranges::find(v, 36.9);
    if(it != v.end())
        cout << ranges::distance(v.begin(), it) << "\n"; //2
    else
        cout << "Not found";
    
    //条件を満たす要素が最初に現れる位置を調べる
    //std::ranges::find_if
    auto it1 = ranges::find_if(v, [](int n){return n > 38;});
    cout << ranges::distance(v.begin(), it1) << "\n";

    /**
     * 範囲に対する操作
    */

    //範囲の要素を埋める
    //std::ranges::fill
    vector<int> vec = {1,2,3,4};
    ranges::fill(vec, 0);
    for(auto &v : vec) cout << v << " ";
    cout << "\n";
    vector<string> str = {"Hello", "Morning", "Good afternoon", "Good night"};
    ranges::fill(str | views::take(2), "Neko");
    for(auto &s : str) cout << s << " ";
    cout << "\n";

    //指定した値と等しい要素をすべて削除
    //eraseはidx指定よりこっちの方がよさそう
    vector<int> vec1 = {5,3,4,3,2,4,2,2,4,5,3,2,2};
    vector<int> vec2 = vec1;
    std::erase(vec1, 2);
    vec1.shrink_to_fit();
    cout << vec1.capacity() << endl; //13 
    //つまり無効化したが、メモリは確保されたまま

    //ranges::remove -> 無効範囲のサブレンジを返す
    //有効範囲に残る要素の前後関係は維持される
    //erase -> これのiteratorにおいて、remove()が返したものを使うことで、無効範囲を削除する
    auto subrange = ranges::remove(vec2, 2);
    vec2.erase(subrange.begin(), subrange.end());
    vec2.shrink_to_fit();
    cout << vec2.capacity() << endl;
    //removeについては使う利点はあまりなさそう?

    //条件を満たす要素をすべて削除
    //std::erase_if
    //コンテナに対して汎用的に適用できる
    vector<int> vec3 = {5,3,3,2,4,2,4,3,5,1};
    std::erase_if(vec3, [](int n){return n % 2 == 0;});
    for(auto v: vec3) cout << v << " ";
    cout << "\n";

    //逆順
    ranges::reverse(vec3);

    //指定した要素を置き換え
    ranges::replace(vec3, 3, 30);
    //条件で置き換え
    ranges::replace_if(vec3, [](int n){return n > 10;}, 0);
    for(auto v: vec3) cout << v << " ";
    cout << "\n";

    //等しい値が隣同士にならないよう要素を削除
    //std::ranges::unique ⇒これは重複しない要素を前に集めるだけ。よって、eraseで消す
    //setにすればよくね？という問題はあるけれど
    vector<int> vec4 = {1,4,5,1,3,2,4,1,4,11,7};
    vector<int> vec5 = vec4;
    std::ranges::sort(vec4);
    auto it2 = std::ranges::unique(vec4);
    vec4.erase(it2.begin(), it2.end());
    for(auto v: vec4) cout << v << " ";
    cout << "\n";    
    // unordered_set<int> set1(vec5.begin(), vec5.end());
    // vector<int> vec6(set1.begin(), set1.end());

    //要素の前半と後半を入れ替える
    //std::ranges::rotate(range, itMiddle)
    //※順番に注意
    //std::ranges::rotate(inFirst, inMiddle, inLast)
    //指定した要素の直前を区切り目とし、これ境に、前半と後半を入れ替える
    vector<int> vec7 = {1,2,3,4,5,6,7,8};
    ranges::rotate(vec7.begin(), vec7.begin() + 3, vec7.begin() + 5);
    Print(vec7);

    //範囲ソート
    vector<int> vec8 = {8,1,7,6,5,2,3,4};
    std::ranges::sort(vec8);
    //カスタムソート
    //std::ranges::greater{} 大きい方優先
    std::ranges::sort(vec8, std::greater{});
    //第二引数優先
    vector<pair<int, string>> vec9 = {
        {1, "neko"},
        {2, "inu"},
        {3, "tanuki"}
    };
    std::ranges::sort(vec9, [](auto a, auto b){
        if(a.second == b.second){
            return a.first < b.first;
        }
        return a.second < b.second;
    });
    for(auto [first, second] : vec9){
        cout << first << " " << second << "\n";
    }

    //projectionを用いたソート
    //projectionに要素を指定することで、特定のメンバ変数のみを用いてソートする
    //std::ranges::sort(range, comp, projection)
    //compに{}を使うことでデフォルトの比較関数を使う
    //projectionにメンバ変数を使う時は、参照指定
    vector<Person> vec10 = {
        {"Alice", 25},
        {"Bob", 30},
        {"Charlie", 18},
        {"Dave", 19},
        {"Eve",11},
    };
    ranges::sort(vec10, {}, &Person::age);
    for(const auto& p : vec10){
        cout << p.name << " " << p.age << "\n";
    }

    //先ほどのpairを簡単にする
    //降順でsecond優先
    //std::invokeでメンバポインタを使っている感じ
    std::ranges::sort(vec9, std::greater{}, &pair<int, string>::second);
    
    //全てに関数を適用
    vector<int> result;
    std::ranges::transform(vec8, std::back_inserter(result), [](int x){return x*2;});
    Print(result);
    //新たに配列を作らず、参照で処理する
    ranges::for_each(result, [](int &n){n *= 2;});
    Print(result);

    //配列がsortされているか調べる
    //std::ranges::is_sorted(range)
    //compとprojectionを渡すこともできる。compだけも可
    vector<pair<int,int>> v2 = {
        {5,2},
        {4,5},
        {3,6},
        {2,1},
    };
    cout << boolalpha << ranges::is_sorted(v2, std::greater{}, &pair<int, int>::second) << "\n";

    //配列の要素について上位N個までをソート
    //全体に対してNが大部分であるときsort()よりも効率が落ちることがある
    //std::ranges::partial_sort(inFirst, inMiddle, inLast)
    //計算量O(NlogM)
    vector<int> vec11 = {1,5,0,2,4,6,3,9,8,7};
    //上位4個まで昇順ソート
    ranges::partial_sort(vec11, vec11.begin() + 4);
    Print(vec11);
    string str1 = "deacbgf";
    ranges::partial_sort(str1, str1.begin() + 3);
    cout << str1 << "\n";
    //上位3個まで降順ソート
    ranges::partial_sort(str1, str1.begin() + 3, [](char x, char y){
        return x > y;
    });
    cout << str1 << "\n";

    //N番目に小さい要素を求める
    //partial_sortで効率が落ちている場合は、こっちの方が生産的
    //std::nth_element(itFirst, inNth, itLast)
    //それより前はその要素より小さく、それより後はその要素より大きい要素が並ぶことを保証する
    vector<int> vec12 = {1,5,0,2,4,6,3,9,8,7};
    //4番目に小さい要素
    //quick_sortの基準のようなことをしているのかな?
    //計算量はO(N)

    //以下の手順でcも、partial_sortのような真似ができる
    // K > 70000ではpartial_sortに勝つらしい
    // https://www.geeksforgeeks.org/sort-vs-partial_sort-vs-nth_element-sort-in-c-stl/
    ranges::nth_element(vec12, vec12.begin() + 3);
    ranges::sort(vec12.begin(), vec12.begin() + 2);
    Print(vec12);

    //ソート済みの範囲に対する二分探索
    //配列の何番目かを整数値で得るにはstd::distance
    //ランダムアクセスイテレータ以外をdistanceに渡すと
    //具体的にはstd::setやstd::multisetの場合、計算量はO(N)に悪化する。
    //※それぞれのコンテナのメンバ関数を使えばいい。set::set::lower_bound()
    //valを挿入するとして、ソートされた状態を壊さない最も左の位置のイテレータを返す
    {
        vector<int> vec = {50,100,10,1,5};
        ranges::sort(vec);
        auto it = ranges::lower_bound(vec, 5);
        cout << ranges::distance(vec.begin(), it) << "\n";
    }

    //...ソートされた状態を壊さない最も右の位置
    //std::distance vs std::ranges::distance
    //範囲がsizeを持つ場合、std::ranges::distanceは直接範囲のサイズを返すので
    //前者より効率が良くなる。範囲を持たない場合は同等?
    //iteratorの型に対する要件を満たす場合に、rangeの方はエラーを発生できる可能性あり
    //⇒エラーの早期検出を考えると、常にrangesの方を使うべきか
    /**
     * コード的によろしくないが、
     * using namespace std;
     * using namespace std::ranges;
     * としてdistance(ranges)とすると、より具体的である
     * std::ranges::distanceの方が使われるはず
     * 上の方で使うものだけusingしておいてもいいかも
     * using namespace std::ranges::distanceみたいに
    */
    {
        vector<int> vec = {50,100,10,1,5};
        std::ranges::sort(vec);
        auto it = std::ranges::upper_bound(vec, 5);
        cout << std::ranges::distance(vec.begin(), it) << "\n";
    }

    //lower_boundとupper_boundの結果を同時取得する
    //std::equal_range -> pairを返す
    //std::ranges::equal_range -> sub_rangeを返す
    {
        vector<int> vec = {50,100,10,1,5};
        std::ranges::sort(vec);
        auto p = std::ranges::equal_range(vec, 5);
        cout << ranges::distance(vec.begin(), p.begin())
        << " " << ranges::distance(vec.begin(), p.end()) << "\n";   
    }

    //指定した値と等しい要素が存在するか調べる
    //std::ranges::binary_search
    {
        vector<int> vec = {0,1,5,10,50,100};
        cout << std::ranges::binary_search(vec, 80) << endl;
    }

    //ソート済みの2つの範囲における集合演算
    //std::ranges::includes
    //range2がrange1の部分集合であるかどうかを返す
    {
        vector<int> v1 = {1,2,3,4,5,6};
        vector<int> v2 = {1,6};
        cout << std::ranges::includes(v1, v2) << "\n";
    }

    //順列
    //.foundは順列が終端に達して最初の順列に戻るとfalseになる
    {
        vector<int> v = {1,2,3};
        do{
            for(const auto& n : v){
                cout << n << " ";
            }cout << "\n";
        }while(std::ranges::next_permutation(v).found);
    }

    
    

}
