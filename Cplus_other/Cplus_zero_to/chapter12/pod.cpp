/**
 * 非推奨
 * POD
 * plain old data
 * CとABI互換性が保証されるデータ構造
 * 
 * データ構造がPODであるか否かは
 * std::is_podで判定可能
 * コンパイル時に判断したいのでstatic_assertで判定しておく
 * 
 * C++11でPODはトリビアルとスタンダードレイアウトという
 * 2つの概念に分離された。
 * そして、実用上必要なものはトリビアルコピー可能型 or スタンダードレイアウト型と分かった
 * 
 * ⇒std::is_pod : deprecated
 * std::is_standard_layout: 型が標準的なメンバは位置を持っているか
 * std::is_trivially_copyable: 型がトリビアルにコピー可能か
 * std::is_trivial: 型がトリビアルなコピーコンストラクタやデストラクタを持つか
*/

#include <bits/stdc++.h>
using namespace std;

/**
 * Cには存在しないC++の機能
 * クラス:
 *  ・構造体にすればいい
 *  ・メンバ関数、継承、データメンバに対するアクセス修飾子はダメ
 *  ・Cの構造体はデータメンバを持つだけなので
 * 
 * Cの標準ヘッダファイルを使える
 *  
 * 
 * C++には存在しないCの機能
 *  ・複合リテラル
 *  
 * CとC++で異なるソースコードにする
 *  ・プリプロセッサ司令が使える
 * 
 * #ifdef __cplusplus
 * //C++だけで有効なコード
 * #else
 * //Cだけで有効なコード
 * #endif
 * ⇒これを用いて例えば、C++でだけメンバ関数を有効にできる
 * ⇒メンバ関数を追加するだけの派生クラスをC++で使用するとか
 * 　
*/


//cp pod.cpp pod.cとして実行したがうまくいった!
#ifdef __cplusplus

#include <bits/stdc++.h>
using namespace std;

int main(){
    int num = 10;
    cout << num << endl;
    return 0;
}

#else

#include <stdio.h>
int main(){
    int num = 10;
    printf("%d\n", num);
    return 0;
}
#endif