// g++ -std=c++20 sample.cpp sample_test.cpp -lgtest -lgtest_main -lpthread -o test 

/**
 * 初歩的なテストの記述方法
 * 1. test対象をincludeする
 * 2. 成功したtest -> OK
 *    失敗したtest -> FAILED
 *    通過したtest数 -> PASSEDに表示
 * 
 * 3.記述法
 * TEST(テストケース, テスト名){
 *      C++のコードを記述
 * }
 * ※テストケースとテスト名には_を記載できない
 * 
 * 4. Assert例
 * EXPECT_TRUE(condition);
 * EXPECT_FALSE(condition);
 * 
 * EXPECT_EQ(expected, actual)
 * _NE, _LT, _LE, _GT, _GE
 * 
 * 5. Expect or Assert
 * EXPECT => テストに失敗してもテスト関数を続行
 * ASSERT => テストに失敗すると中断してテスト関数を抜ける
 * ⇒すぐにrtnしてくるので、その後の後処理が実行されず、メモリリークにつながる可能性あり
 * つまり、ASSERTでもテスト関数が別なら次に行くだけなのか
 * 
 * 6. コマンドの引数の意味
 * -lgtest googletestライブラリであるlibgtest.aをリンクする。
 * testコード内でgtestの機能を使用するt前、これは不可欠。
 * -lgtest_main: 自分でmain関数を書かない場合必要
 * 通常のmain関数の代わりにgtestのメイン関数を使用することになる
 * -lpthread: マルチスレッドでの実行に対応するもの。
 * -o いつもの。testの実行結果が格納されるファイル名を記載
 * 
*/
#include <gtest/gtest.h>

#include "sample.hpp"

TEST(IsEvenTest, Negative){
    EXPECT_FALSE(isEven(-1));
    EXPECT_TRUE(isEven(-2));
}

TEST(IsEvenTest, Zero){
    EXPECT_TRUE(isEven(0));
}

TEST(IsEvenTest, Positive){
    EXPECT_FALSE(isEven(1));
    EXPECT_TRUE(isEven(2));
}
