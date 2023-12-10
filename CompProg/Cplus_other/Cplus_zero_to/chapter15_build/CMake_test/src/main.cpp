#include <iostream>
using namespace std;

int main(){
    int val{};
    val = 10;
    cout << val << endl;
    return 0;
}

/**
 * buildの手順
 * 1. cmakeがinstallされているか確かめる
 * 2. プロジェクトのディレクトリに移動
 * 3. ビルドディレクトリを作成
 * 4. ビルドディレクトリに移動
 * 5. cmakeでビルドfileを作成
 * cmake .. (親に対してってことか)
 * 6. Makeを使ってビルド
 * make
 * ⇒build内に生成されたことが確認された
 * ⇒CMakeLists.txtを変更することで、
 * 異なるプラットフォームやビルドツールによるビルドが可能になる
 * ⇒ついでに、.gitignoreにbuildを指定した
*/