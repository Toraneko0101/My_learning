/**
 * 実行時にサイズが確定するようなものについてはヒープを使用する
 * new, deleteは使用しない
 * vectorはheap
 * ローカル変数などはstack
 * stackはLIFOなので、x,yの順で宣言したらy,xの順で取り出される
*/

//new,delete
/**
 * 昔はこうやってヒープにメモリを動的に確保していた
 * int* p1 = new int(100);
 * int* p2 = new int[5];
 * delete p1;
 * delete[] p2;
 * 
 * しかしこれだと、deleteし忘れでメモリリークが起こったりする
 * ちなみに、malloc/freeでも確保解放は可能だが推奨されていない
 * メモリリーク：プログラムが終了してもメモリが解放されないこと
 * 
 * 加えて、newしていないポインタや既に解放したメモリに対するdeleteは未定義動作を引き起こす
 * そのため、条件分岐をしたり
 * nullptrを行って、明示的に初期化を行い...などの面倒な問題が出てくる
 * 構造が複雑化するほど、メモリの動的確保を管理するのは困難になり
 * 実行中にプログラムが落ちたりという動作を引き起こすことにつながる
*/

/**
 * スマートポインタ
 * そこで登場したのがこれ。
 * 動的メモリを確保する責任者を作ってやる
 * Rustみたいにメモリの所有権という概念で管理を行う
 * 
 * 所有権を持つ
 * 　メモリにアクセスする権利と解放する義務を持つ
 * 　所有権は共有したりもできるが、所有権が消えることはない
 * 　★そして、自身が破棄されるとき、自分が保有するメモリの唯一の所有者ならメモリを解放する
 * 　スコープを抜けて破棄されたタイミングで、メモリも解放される寸法ってことか
 * 　またこれは、勝手にメモリが解放されることも防いでくれる
 * 　スマートポインタにメモリ管理をゆだね、動的メモリ管理から解放されよう
*/

/**
 * unique_ptr
 *  所有権はただ1つのインスタンスが管理する
 *  生ポインタと比べてオーバーヘッドがない
 *  所有権が常に単一なのでコピー不可
 *  ムーブ：所有権の移動は可能
 * 
 * shared_ptr
 *  所有権を複数のインスタンスで共有
 *  コピーすると、所有権は複数インスタンスで共有
 *  メモリの開放は最後に所有権を持つインスタンスが行う
 *  ★コピーしなくてもperformance面でオーバーヘッドあり
 * 
 * weak_ptr
 *  自身ではメモリへの所有権は持たない
 *  shared_ptrの持つメモリへの参照を保持する
 *  知らない間に参照先のメモリが解放されることもある
 *  ★参照先のメモリが解放されているかいないかは確かめ可能
 *  shared_ptrへの昇格することもできる
*/
#include <bits/stdc++.h>
using namespace std;
//本来は #include <memory>


void unique_func(int len){
    //ポインタの初期化 今までのポインタでいうint* ptr = nullptr
    unique_ptr<int[]> ptr;

    //len > 0ならその長さのメモリを確保
    if(len > 0){
        //メモリの確保はmake_unique関数が内部で担当
        ptr = make_unique<int[]>(len);
    }

    for(int i=0; i<len; ++i){
        ptr[i] = i*i;
    }
}
//ここでptrのディストラクタが呼ばれる
//ptrがメモリを保持していれば,自動的にdeleteで解放される


//戻り値として使用
unique_ptr<string> hello(int num){
    string str;
    for(int i=0; i<num; i++) str += "hello!";
    return make_unique<string>(str);
}

int main(){
    unique_func(10);

    //メモリの管理
    /**
     * 非推奨
     * //動的確保したメモリのアドレスを指定
     * unique_ptr<int> uptr1(new int(10));
     * 
     * //reset関数を使って後から代入
     * unique_ptr<int> uptr2;
     * uptr2.reset(new int(10));
     * 
     * newを呼ばないこと
    */

    //推奨
    /**
     * shared_ptrの場合、自身の参照カウンタも同的に
     * メモリを書く方する必要があるので
     * make_shared(T)の方が処理速度上もメリットがあるらしい
    */
    auto uptr1 = make_unique<int>(10);
    auto sptr1 = make_shared<int>(10);
    //後から代入する場合も同様
    unique_ptr<int> uptr2;
    shared_ptr<int> sptr2;
    uptr2 = make_unique<int>(20);
    sptr2 = make_shared<int>(20);

    //複数の引数を持つコンストラクタを呼び出す場合
    auto uptr3 = make_unique<pair<int, string>>(10,"test");

    /**
     * 明示的初期化を防ぐ
     * make_unique, make_sharedは引数無しで呼び出してもT()による
     * 明示的初期化が行われる
     * intの場合は0, stringの場合は""
     * 絶対に値を代入する場合、これはコストとなる
     * そのため
     * 
     * make_unique_for_overwrite<T>
     * make_shared_for_overwrite<T>
     * が用意された。不定の値が入る。使用前に上書きする事
     * 不定の中身を評価する動作は未定義
    */
    auto sptr3 = make_shared_for_overwrite<int>();
    *sptr3 = 10;
    int i = *sptr3;

    //メモリにアクセスする
    
    //所有権を持つかどうか確認
    auto uptr4 = make_unique<int>(20);
    auto sptr4 = make_shared<int>(30);

    //true or false
    auto canAccessU = static_cast<bool>(uptr4);

    //直接放り込むことも可能
    if(uptr4) cout << "uptr4 have ownership\n";

    for(int i=0; i<10 && sptr4; i++){
        cout << i << " ";
    }cout << "\n";

    //ポインタの保持するメモリにアクセス
    auto uptr5 = make_unique<string>("unique");
    cout << *uptr5 << endl;
    cout << uptr5->size() << endl;
    //アドレス取得(所有権はスマートポインタが保持したまま)
    //勝手にdeleteしてはいけない
    string* rawuptr = uptr5.get();

    //所有権の移動
    //sharedの場合でもmoveを使うと空になる
    //移動先が既に別のメモリを確保していた場合、古いメモリは自動的に解放される
    auto uptr6 = make_unique<int>(40);
    //ムーブコンストラクタ。所有権はuptr7に移動。uptr6は空
    auto uptr7 = std::move(uptr6); 
    unique_ptr<int> uptr8;
    uptr8 = std::move(uptr7);
    auto uptr9 = make_unique<int>(50);
    uptr9 = std::move(uptr8);
    cout << *uptr9 << "\n"; //40

    //swap
    auto uptr10 = make_unique<int>(30);
    auto uptr11 = make_unique<int>(33);
    std::swap(uptr10, uptr11);

    //関数の戻り値
    auto response = hello(4);
    cout << *response << "\n";

    //派生クラスのスマートポインタを基底に変換は可能
    //unique -> sharedへの所有権移動も可能

    //template型の推論補助:template引数(<int>など)を省略
    auto uptr12 = std::make_unique<int>(10);
    std::shared_ptr sptr12 = std::move(uptr12);

    /**
     * メモリの開放
     * 明示的に開放したい場合は
     * uptr.reset();という風に引数無しで呼ぶ
    */

    /**
    * 配列型を扱う
    * unique_ptr<T[]>
    * shared_ptr<T[]> (C++17 ~ )
    * 引数は確保する配列長
    */
    auto smartArrayU = make_unique<int[]>(10);
    auto smartArrayS = make_shared<int[]>(10); //(C++20~)
    for(int i=0; i<10; i++){
        smartArrayU[i] = i;
        smartArrayS[i] = -i;
    }

    /**
     * unique_ptr vs shared_ptr
     * copy :
     *  unique_ptr ✖
     *  shared_ptr 〇
     * 
     * shared_ptr
     *  メモリに所有権を持つインスタンスの数を記録する共有の参照カウンタを持っている
     *  shared_ptrのcopyで参照カウンタ++
     *  ディストラクタや解放で、参照カウンタ--
     *  参照カウンタ=0なら、メモリ解放
     *  この++,--分のオーバーヘッドがあるので処理速度がunique_ptrに劣る
     *  参照カウンタの値を知る、use_count()を並列処理で使用すると信頼性が低い
     * 
    */
    auto sptr13 = make_shared<int>(10);
    shared_ptr<int> sptr14(sptr13);
    {
        shared_ptr<int> sptr15;
        sptr15 = sptr14; //所有権は13,14,15
    } //所有権は13,14

    sptr13.reset(); //明示的な解放。
    //所有権は14
    //mainを抜ける際に、14のディストラクタが呼ばれ、メモリは解放される

    /**
     * release
     * スマートポインタが管理しているメモリの所有権を放棄
     * メモリの生のポインタを返す
     * メモリはスマートポインタの管理下でなくなる
     * そのため手動でメモリを解放しなくてはならない
     * また、unique_ptrでしか使えない
     * 
     * auto ptr = make_unique<int>(19);
     * int *pint = ptr.release();
     * delete pint;
    */

    /**
     * weak_ptr
     * shared_ptrとともに使う。補助的役割
     * shared_ptrの循環参照を避けられる
    */

    /**
     * 循環参照
     * クラスを学んでから
    */
}
