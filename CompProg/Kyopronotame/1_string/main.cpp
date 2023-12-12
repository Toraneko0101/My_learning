#include <bits/stdc++.h>
using namespace std;

int main(){
    /**
     * c_str()
     * string -> char
     * 具体的には確保したメモリの先頭を指すポインタを返す
     * Cの関数で使えるようになるのが魅力
    */
    string s1("hello"); //string型に変換
    printf("%s\n", s1.c_str());

    /**
    * 文字列リテラルをstringで扱いたい場合
    * using namespace std::literals;を使う
    * s指定で、stringとして扱える
    */

    string s2(5, 'a');

    //1行単位の読み込み
    // string s3;
    // getline(cin, s3);
    // cout << s3 << "\n";

    //入力個数が与えられない場合の読み込み
    // vector<string> words;
    // string in;
    // while(cin >> in){
    //     words.emplace_back(in);
    // }
    // for(const auto &word: words) cout << word << "\n";

    //要素数
    cout << s2.size() << "\n";
    cout << size(s2) << "\n";
    if(empty(s2)) cout << "Yes" << "\n";
    //capasity
    cout << s2.capacity() << "\n";

    //先頭と後ろへアクセス
    cout << s1.front() << "\n";
    cout << s1.back() << "\n";

    //終端文字列にアクセス
    string s4;
    char ch = s4[0];
    if(ch == '\0') cout << "s[0] is NULL.\n";

    //viewの復習
    string s5("atcoder");
    for(const auto& ch: s5 
    | std::views::reverse
    | std::views::drop(2)
    | std::views::take(2)
    ){
        cout << ch << "\n";
    }

    //view -> string
    string s6 = "abcdefg";
    auto view = (s6 | views::take(3));
    string s7(view.begin(), view.end());
    cout << s7 << endl;
    //C++23からはranges::to<std::string>()で変換可能

    /**
     * 末尾追加はO(1) -> 償却計算量
     * 先頭追加はO(N)
    */
    string s8("neko");
    s8.insert(s8.begin(), 'i');
    cout << s8 << endl;
    s8.erase(s8.begin());

    /**
     * 文字列消去
     * 通例の場合、配列の先頭をNULL終端文字にしている
     * そのため。clear()をしても確保した配列領域は変わらない
     * そのため、shrink_to_fit()を用いて現在の要素数に合わせて占有している無駄メモリを減らす
    */
    string s9(100, 'a');
    s9.clear();
    s9.shrink_to_fit();
    cout << s9.capacity() << "\n";

    //交換するときはswwap
    //ranges::swapでも可能

    //部分文字列
    string s10 = "atcoder";
    cout << s10.substr(1,4) << "\n"; //末尾を省略したら終わりまで
    cout << string(s10.begin(), s10.begin() + 2) << "\n";

    //string_viewで既存の部分文字列を指すものをコピーなしで作成
    cout << string_view{s10.begin(), s10.begin() + 2} << "\n";

    //メンバ関数
    cout << s10.starts_with("at") << "\n";
    cout << s10.ends_with("der") << "\n";
    // cout << s10.contains(ch) << "\n"; //C++23~
    cout << s10.find("der") << "\n"; //最初に現れる位置
    cout << s10.rfind("der") << "\n"; //末尾から検索
    //⇒見つからない場合、string::nposが返る(C++23からはcontainsで場合分け可能)
    //これはstd::size_tの最大値となる
    cout << s10.find("fdjsapdfk") << "\n";
    cout << string::npos << "\n";

    /**
     * 各種イテレータ
     * .begin(), .end()
     * .rbegin() .rend(): 逆イテレータ
    */

    
}