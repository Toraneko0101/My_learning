#include <bits/stdc++.h>
using namespace std;

int main(){
    /*初期化*/
    //1 普通に
    string str = "Hello";
    //2 vecのような初期化:こっちの方が効率的
    string str1(10, 'a');
    string str1_5(3, 42); //ascii
    string str2("Neko");
    //3. pointerを利用した初期化
    //文字列リテラルからchar*型の変換は非推奨なので,constをつけないとエラーが出る
    const char *data = "nekodayo";
    string str3(data);
    //4. [char* first, char* end)
    // std::end 範囲から最後尾の次を指すiteratorを取得する
    char org_str[] = {'N', 'E', 'K', 'O'};
    string str4(org_str, std::end(org_str));
    //5. charの一部から生成
    const char *org_str1 = "abc123xyz";
    string str5(org_str1 + 3, org_str1 + 6); //123
    //6 copy_constructor
    string org("123");
    string org_new(org); //123
    //7 他のstrから切り出す
    string base_str("foo bar");
    string str6(base_str, 4, 3); //bar
    string str7(base_str.begin(), base_str.begin() + 3); //foo
    //8 第一引数から切り出す
    string str8("ABCDEFG", 3); //3文字切り出し(ABC)

    //連結 +
    string str9("12");
    string str10("xyz");
    str9 += str10;

    //追加
    str9.push_back('A'); //文字型:1文字なら最適
    str9.append("back", 1); //2文字挿入
    str9.append("back", 1, 3); //1文字目以降の位置から3文字挿入
    //挿入
    str9.insert(str9.begin() + 2, {'a', 'b'}); //O(N)
    str9.insert(2, "ABC"); //2文字目から挿入
    cout << str9 << "\n";

    /**
     * push_backとinsertでいいように思えるが、
     * stringに文字列を追加するとバッファの再確保が発生する可能性あり
     * 事前にバッファの容量を指定しておくのもよし
     * 再確保時には余裕をもってメモリが消費されるので、予め設定しておくと無駄がなし
    */
    string str11 = "1234567890123456";
    //str11.capacity(); //現在のキャパシティ
    str11.reserve(64); //キャパシティを事前に増やす
    str11 += str11;
    str11 += str11; 
    cout << str11.capacity() << "\n"; //キャパシティは増大しない

    //削除
    string str12("Help me");
    if(size(str12) != 0) str12.pop_back(); //末尾削除-空に対して行ってはいけない(size()でifしておけばいいか)
    //erase:移動するので削除以降の文字がNとしてO(N)
    str12.erase(str12.begin() + 4); //Helpm
    //eraseの範囲で一度に削除
    str12.erase(str12.begin() + 2, str12.begin() + 4); //Hem

    //その他
    //サイズを取る
    // str.size() == str.length() == std::size(str);

    //文字列の一部を取得
    string str13("hogedayo");
    //先頭と最後尾
    cout << str13.front() << " " << str13.back() << "\n";
    cout << str13[0] << " " << str13[size(str13) - 1] << "\n";
    //切り出す[2, 2+4)
    cout << str13.substr(2,4) << "\n";

    //文字列データ先頭アドレスを返す
    cout << str13.c_str() << "\n";
    cout << str13.data() << "\n";

    //状態変更
    /**
     * clear():文字列空⇒メモリは解放されない
     * resize(size, moji):文字列を指定サイズに設定
     * str.swap(another_str): 別のobjと内容入れ替え
     * shrink_to_fit: sizeまでcapacityを縮小する
    */
    string str14("inudayo");
    string str15("nekodayo");
    str14.resize(4);
    cout << str14 << "\n";
    str14.swap(str15);
    cout << str14 << "\n";

    //文字列検索、置換
    string str16("abcabc");
    cout << str16.find("b", 3) << "\n"; //3文字目から検索
    cout << str16.rfind("b", 3) << "\n"; //3文字目から前方に向かって検索
    str16.replace(1,2,"xyz"); //1文字目から2文字をxyzに置換
    cout << str16 << "\n"; 

    //数値、文字相互変換
    int a_int = 12;
    string str17 = to_string(a_int);
    int b_int = stoi(str17);

    //文字列分割
    string str18("C,C++,Java,Python");
    vector<string> tokens;
    string token;
    stringstream ss(str18); //入出力可能なsstreamに変換
    /**
     * getline(cin, 入力文字列格納, 分割文字列)
     * eofや文字列の終端でfalseを返す
    */
    while(getline(ss, token, ',')){
        tokens.push_back(token);
    }
    for(auto &s: tokens){
        cout << s << " ";
    }cout << "\n";

    /**
     * stringstream
     * 文字列の分解と組み立てが可能、#include <sstream>
     * 
     * istringstream //分解
     * ostringstrema //組み立て
     * stringstreamは多重継承しているのでperformanceを追い求めたい場合は、使うといいかも
    */
    stringstream str19 {"50 + 12"};
    int val1, val2;
    string op;
    str19 >> val1 >> op >> val2;
    cout << val1 << op << val2 << "\n";
    str19.clear(); //streamのエラー状態をリセット。ファイルに終わりにeofbitが経っている場合、goodbitに戻す
    str19.str(""); //空文字をstreamのコンテンツとして設定し、以前のコンテンツをすべて破棄
    str19 << 5 << " * " << 2;
    cout << str19.str() << "\n";

    //入力文字を特定区切りで分割する(末尾,なら飛び越える)
    vector<string> vec10;
    string str20, line;
    getline(cin, str20);
    stringstream ss1(str20);
    //1行文の文字列を分割
    while(getline(ss1, line, ',')){
        vec10.push_back(line);
    }

    for(const string &s: vec10){
        cout << s << endl;
    }




}