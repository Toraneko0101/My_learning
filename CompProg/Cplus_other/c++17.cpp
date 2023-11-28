#include <bits/stdc++.h>
using namespace std;

struct Point{
    int x,y;
};

tuple<int, int, string> GetTuple(){
    return{20,40,"ABC"};
}

bool LessThan10(int n){
    return n < 10;
}

//戻り値の使い忘れを警告する
[[nodiscard]] int Increment(int n){
    return n+1;
}

int main(){
    /*c++17の追加処理等*/
    //1.値を範囲内に収める
    cout << clamp(20, 0, 100) << "\n"; //20
    cout << clamp(-20, 0, 100) << "\n"; //0
    cout << clamp(170, 0, 100) << "\n"; //100

    /**
     * random_device : class
     * random_device rd{};のようにしてobjを作って rd()で呼び出す。
     * random_device{}()なら直接呼び出せる
     * もしくは再利用しないなら名前を付けない
     * 
     * mt19937:obj
     * 
     * back_inserter: 末尾挿入のiterator
     * front_inserter: 先頭挿入のiterator
    */
    
    //2.要素の集合からランダムにN個を取り出す
    //sample(first, last, out(出力イテレータ), n(個), g(乱数ジェネレータ))
    string in = "ABCDEFG";
    int N = 4;
    string out;
    sample(in.begin(), in.end(), back_inserter(out), N, mt19937{random_device{}()});
    cout << out << "\n";

    //コピー & 挿入イテレータ
    vector<int> v = {1,2,3};
    vector<int> w = {4,5,6};
    copy(w.begin(), w.end(), back_inserter(v));
    /**
     * ostream_iterator: 要素をイテレートしながら第一引数に出力
    */
   copy(v.begin(), v.end(), ostream_iterator<int>(cout, ","));
   cout << endl;

   //3. 無効値を保持する(型が無効のもの)
   /**
    * optional<Type>
    * has_value() or ifで有効値をチェック可能
    * nulloptで無効値をチェック可能
    * 有効値を取り出すにはvalue()を使う
    * Type型のメンバにアクセスするにはoperator->
    * value_or(x)で有効値を保持している場合はその値を、保持していない場合はxを返す
   */
    //boolalpha: bool値を文字列として出力
    //noboolalpha: 戻す
    /**
     * optional
     * 任意の型Tの値を有効値としてあらゆる型に共通の無効値状態を表現できる型
     * objの初期化タイミングの遅延や、エラー報告用
    */
    cout << boolalpha;
    optional<int> oi; //defalutでは無効値
    if(oi) cout << oi.value() << "\n";
    cout << (oi == 200) << "\n"; //false
    oi = 200;
    if(oi) cout << oi.value() << "\n"; //200
    cout << (oi == 200) << "\n"; //true
    cout << oi.value_or(999) << "\n"; //200
    oi = nullopt; //無効値に
    cout << oi.value_or(999) << "\n"; //999

    optional<Point> op;
    if(op) cout << op->x << "," << op->y << "\n"; //未出力
    op = Point{11,22}; //有効値を入れる
    if(op) cout << op->x << "," << op->y << "\n"; //11,22
    op = nullopt;
    if(op) cout << op->x << "," << op->y << "\n"; //未出力

    //4. tupleと構造化束縛
    auto [a,b,c] = GetTuple();
    cout << a << "," << b << "," << c << "\n";

    //5 emplace_back(), emplace_front()が、追加された要素への参照を返す
    //push_back()は戻り値がない?
    vector<pair<int,int>> vec;
    //const auto p = v.emplace_back(11,33);
    const auto [first, second] = vec.emplace_back(11,33);
    cout << first << "\n";

    //6 insert_or_assign(map, unordered_map)
    //keyと同じキーを持つ要素が存在する場合は要素を代入
    //存在しない場合は要素を挿入。代入の場合はsecondにfalseの戻り値を返す
    unordered_map<string, int> m;
    cout << m.insert_or_assign("aaa", 5).second << "\n"; //true
    cout << m.insert_or_assign("aaa", 10).second << "\n"; //false
    cout << m["aaa"] << "\n";

    //7.非メンバ関数のdata(), size(), empty()
    //各種コンテナや配列で一貫して使える
    //data()はコンテナのポインタを取得する
    int ar[20];
    vector<int> vec1;
    cout << size(ar) << "\n";
    cout << size(vec1) << "\n";
    cout << empty(ar) << "\n";
    cout << empty(vec1) << "\n";
    vec1.emplace_back(2);
    int *vec2 = data(vec1);
    vec2[0] = 1;
    cout << vec1.at(0) << "\n";

    //8.gcdとlcm
    //戻り値の型はcommon_type_t<M,N>なので引数の型にとらわれない
    cout << gcd(554433221100LL, 12345) << "\n";
    cout << lcm(554433221100LL, 12345) << "\n";

    //9.not_fn:関数objの結果の否定を返す関数objを作る関数
    //bool型を返す関数objを受け取り、戻り値を論理反転する
    vector<int> vec3 = {3,5,7,9,11,13};
    //count_if: 条件を満たしている個数を返す
    cout << count_if(vec3.begin(), vec3.end(), LessThan10) <<"\n";
    cout << count_if(vec3.begin(), vec3.end(), not_fn(LessThan10)) << "\n";

    //10. 効率的な文字列検索アルゴリズムが利用可能に
    //ボイヤー・ムーア文字列検索アルゴリズム
    string in1 = "ATGGTTGGTTCGCTAAACTGCATCGTCGCTGTGTCCCAGAA";
    string pattern = "TGTGTCCCAG";
    boyer_moore_searcher searcher(pattern.begin(), pattern.end());

    auto it = search(in1.begin(), in1.end(), searcher);
    if(it != in1.end()) cout << distance(in1.begin(), it) << "\n"; //29
    else cout << "not_found\n";

    //11.3次元のhypot(x,y,z)
    //3次元のベクトルの長さを求める:2次元のもののoverload版
    cout << hypot(1.0, 1.0, 1.0) << "\n";

    //12.別の連想コンテナから要素を抜き出し・マージする
    unordered_set<int> s1 = {10,8,5,4};
    unordered_set<int> s2 = {10,6,4,2};
    s1.merge(s2); // s1 <- s2
    cout << "s1: ";
    for(const auto& e : s1) cout << e << " ";//6 2 4 5 8 10 
    cout << "\ns2: ";
    for(const auto& e: s2) cout << e << " "; //4 10

    unordered_map<string ,int> m1 = {
        {"one", 1},
        {"five", 5},
        {"ten", 10}
    };
    unordered_map<string ,int> m2 = {
        {"one", 1},
        {"two", 2},
        {"three", 3}
    };

    m1.merge(m2);
    cout << "\nm1: ";
    for(auto [key, val] : m1){
        cout << format("{}={} ",key, val);
    }
    cout << "\nm2: ";
    for(auto [key, val]:m2){
        cout << format("{}={} ", key, val);
    }
    cout << "\n";

    //13.if,switch等に初期化式を書けるように
    //変数のスコープを狭められる
    unordered_map<string, int> m3 = {
        {"one",1},
        {"two",2},
        {"three",3}
    };
    //戻り値はfindなのでiterator
    if(auto it = m3.find("three"); it != m3.end()){
        cout << it->second << "\n";
    }
    if(auto it = m3.find("two"); it != m3.end()){
        cout << it->second << "\n";
    }

    int x1 = 0;
    //戻り値を無視すると警告を出してくれる
    //Increment(x1);
    x1 = Increment(x1);
    cout << x1 << "\n";
}