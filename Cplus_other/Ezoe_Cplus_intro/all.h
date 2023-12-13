/*言語サポート系ライブラリ*/
#include <limits> //numeric_limitsなど
#include <new> //動的メモリ管理
#include <typeinfo> //型情報
#include <exception> //例外ハンドリング
#include <initializer_list> //初期化子リスト
#include <source_location> //ソースコード上の位置を表す
#include <version> //ライブラリ機能テストマクロを使用可能
#include <compare> //宇宙船演算子
//#include <coroutine> //コルーチン 使うには -fcoroutinesの指定が必要
#if __has_include(<stdfloat>)
    #include <stdfloat> //ex) float16_t 実装定義の拡張小数点型
#endif


/*コンセプトライブラリ*/
#include <concepts> //requiresやsame_as等の型比較に使える


/*汎用的なユーティリティライブラリ*/
#include <utility> //initializer_list & compareもinclude。pariやmoveも含まれる
#include <bitset> //bitの固定サイズ配列について計算する
#include <ratio> //コンパイル時に有理数を表現する
#include <tuple> //タプル
#include <optional> //無効値を入れられる
#include <variant> //候補の型を切り替えながら保持
#include <any> //あらゆる型の値を保持できる記憶域
#include <type_traits>
#include <functional>
#include <memory> //shared_ptrなど
#include <scoped_allocator>
#include <memory_resource>
#include <chrono>
#include <typeindex>
#include <execution>
#include <charconv>
#include <format> //Atcoderではまだ不採用
//C++23
#if __has_include(<expected>)
    #include <expected> //正常値かエラー値のどちらかを持てるobj
#endif
#if __has_include(<stacktrace>)
    #include <stacktrace>
#endif


/*文字列ライブラリ*/
#include <string> //文字関連
#include <string_view> //所有権を持たず文字列を参照する文字列クラス


/*ローカライズライブラリ*/
#include <locale>
//#include <text_encoding> //C++26


/*コンテナライブラリ*/
#include <array> //配列
#include <deque> //両端キュー
#include <forward_list> //単方向リスト
#include <list> //双方向リスト
#include <queue> //FIFO
#include <stack> //LIFO
#include <vector> //vector
#include <map> //連想配列
#include <set> //set
#include <unordered_map> //非順序連想配列
#include <unordered_set> //非順序集合
#include <span> //部分シーケンスの参照.配列のポインタがライブラリから渡された場合などに使用
#if __has_include(<mdspan>)
    #include <mdspan> //多次元配列ビュー
#endif
#if __has_include(<flat_map>)
    #include <flat_map> //ソート済みキーによる順序付き連想配列
#endif
#if __has_include(<flat_set>)
    #include <flat_set> //ソート済みキーによる順序付き集合
#endif


/*イテレータライブラリ*/
#include <iterator>


/*レンジライブラリ*/
#include <ranges> 
#if __has_include(<generator>)
    #include <generator> //コルーチンによるレンジ生成
#endif


/*アルゴリズムライブラリ*/
#include <algorithm>


/*数値ライブラリ*/
#include <complex> //複素数
#include <bit> //ビット操作
#include <random> //乱数生成
#include <valarray> //数値に特化した配列。sliceが使える
#include <numeric> //gcdなど。一般的な数値操作
#include <numbers> //数値 pieなど


/*入出力ライブラリ*/
#include <iostream> //ios, streambuf, isstream, ostreamをincludeする
#include <iomanip> //入出力に使用するフォーマットなど
#include <sstream> //文字列objを出力先、入力先とするstreamクラスを定義
#include <fstream> //ファイルを出力先、入力先とするstreamクラスを定義
#include <filesystem> //pathやファイル状態など。OSのファイルシステムを操作する
#include <syncstream> 
#if __has_include(<print>)
    #include <print> //書式指定による出力
#endif


/*正規表現ライブラリ*/
#include <regex> //正規表現


/*アトミック操作ライブラリ*/
#include <atomic> //アトミックアクセスのためのコンポーネント
#if __has_include(<stdatomic.h>)
    #include <stdatomic.h> //アトミック操作のC互換ライブラリ
#endif


/*スレッドサポートライブラリ*/
#include <stop_token>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <semaphore>
#include <latch>
#include <barrier>
#include <future>


/*C言語互換ライブラリ*/
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cuchar>
#include <cwchar>
#include <cwctype>


using namespace std::literals; //文字列リテラルを受け取り文字型のbasic_stringを構築する

