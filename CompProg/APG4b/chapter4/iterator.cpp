#include <bits/stdc++.h>
using namespace std;
/**
 * c++におけるtemplateとclass,structの補足は後程
 * viewsについてももう少し知識がいる
 * 理解度についてまとめて書いておくファイルがいる
 * 初見✖, 解説あり△、解けるはず〇で。
*/

/**
 * distance(ite1, ite2); iterator間の距離
 * advance(ite, k); iteratorをk回進める、負の値で戻る
 * next(ite,k) //k個先のiteを得る : map,setでは使えない。返り値として得るので置き換わらない
 * prev(ite,k) //k個前のiteを得る: map,setでは使えない
 *  *iterator //iteの指す要素へアクセス。map/setは読み取り
 *  iterator->member :iteの指す要素のメンバへのアクセス
 *  container.erase(iterator) //iteratorの指す要素の削除
 * 
 * 各要素を指すものだと考えられる
*/

//例
int main(){
    vector<int> a = {3,1,4,5,7,8,9};
    //iteratorを変数に入れる場合はautoを使う
    //コンテナ毎に定義されていて大変なので
    auto itr1 = a.begin();
    itr1 = itr1 + 2; //2つ進める
    cout << *itr1 << endl; //4

    //forで配列の要素に順番にアクセス(範囲forでいい気もするが)
    //endは末尾の次なのでアクセスしないこと。beginも空の場合は末尾の次を指す
    //next(a.begin(),1) //1個目から返す
    for(auto it = next(a.begin(),1); it != a.end(); it++){
        cout << *it << endl;
    }

    // ->の例
    vector<pair<int,int>> b = {
        {1,4},
        {2,5},
        {3,6}
    };

    auto itr = b.begin() + 1;
    cout << (itr->first) << "," << (itr->second) << endl;

    //第二引数を省略すると、1になるっぽい:末尾が欲しい時の操作
    //空のコンテナに対して行わないこと
    auto i = prev(a.end(),1);
    cout << *i << endl;

    //要素を削除する場合、そのiteratorが無効化されるので注意。
    //eraseは削除後の次の要素のiteratorを返すので
    //it = a.erase(it);として再び代入する感じにする

    /**
     * 計算量
     * 配列のiteなら削除以外O(1),削除は,削除する要素以降が一個ずれるのでその分
     * map,setならbegin,endはO(1),それ以外は移動する回数
     * 要素の削除は償却計算量がO(1)。:N回行うと平均O(1)
    */

   /**
    * 無効
    * vector
    * 要素削除で、それ以降が無効化。eraseの戻り値を利用可能
    * push_backですべて無効化。
    * 
    * map,set
    * 削除でその要素に対するイテレータ無効化
    * 要素の変更は不可能。readonly
   */

    //幾つかの要素をsort
    vector<int> c = {2,4,7,6,1,2,4};
    sort(c.begin() + 1, c.end());
    cout << c.at(1) << endl;

    //find:指定した値に一致する最初の要素を探す
    //見つからなかった場合、第二引数のiteratorを返す
    //O(N)
    //map,setの場合はメンバ関数版の方が高速
    // map_obj.find(ite.begin(), ite.end(), "hoge");
    auto itr2 = find(c.begin(), c.end(), 7);
    if(itr2 == c.end()) cout << "not found" << "\n";
    else cout << distance(c.begin(), itr2) << "\n";//idx

    //find_if:条件を満たす最初の要素を返す:計算量は第1引数からの距離
    auto itr3 = find_if(c.begin(), c.end(),
    [](int x){ return x % 2 == 0; }
    );
    if(itr3 == a.end()) cout << "not found " << endl;
    else{
        int kyori = distance(c.begin(), itr3);
        cout << format("c[{}] = {} % 2 = 0\n", kyori, *itr3);
    }

    //lower_boundもiteratorを返すので、autoを用意し、*iterとアクセスしていたわけ
    //見つからなかった場合に範囲の最後を返すのは一緒
}