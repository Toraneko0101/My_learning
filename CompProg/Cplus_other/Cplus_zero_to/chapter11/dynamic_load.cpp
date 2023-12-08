#include <iostream>
#include <dlfcn.h>
#include <functional>

using namespace std;

//Wrapperクラスで
//1. ライブラリのロード
//2. 関数の呼び出し
//3. アンロードを行う
class DynamicLibraryWrapper{
public:
    /**
     * 1. Constructorとして生成時に、以下の処理を行う
     * dlopen(ファイル名, hoge): 動的ライブラリを開く
     * ⇒正常終了の場合、handleが返されるのでこれでライブラリを操作する
     * 
     * dlerror(): 最後に使用された動的ロードのAPIでエラーがあった場合、その旨を返却
     * ※動的ライブラリの探し方は動的リングと一緒
     * ※今回はカレントに配置したので -L.でいいはず
     * 
     * 2. <返却されたhandle>
     * dlsym(handle, シンボル名):
     *  handleから関数や変数のポインタを取得する
     *  symbol名は、nmコマンドでobjectファイルや動的ライブラリを指定して確認する
     * 例) 
     * $ nm test.o
     * $ nm libhoge.o
     * ※名前マングリングを行う前の情報はc++filtで確認可能
     * nm test.o | c++filt
     * 
     * ⇒正常終了した場合、symbolのポインタが返される
     * ⇒シンボルが関数なら関数ポインタになる
     * ⇒errorの場合、NULLになるので!で条件判定
     * ⇒正常終了した結果がNULLになった場合を加味していないかも
     * ⇒dlsymが返すvoidポインタを関数ポインタ型に変換するためにreinterpret_castが用いられている
     * 
     * ⇒関数ポインタはmainの方でauto型として受け取る
    */
    DynamicLibraryWrapper(const char* libraryName):
        handle(dlopen(libraryName, RTLD_LAZY)){
            if(!handle){
                cerr << "Error loading library: " << dlerror() << "\n";
                throw std::runtime_error("Library loading error");
            }
        }

    template <typename FuncType>
    std::function<FuncType> getFunction(const char* functionName){
        void* symbol = dlsym(handle, functionName);
        if(!symbol){
            cerr << "Error loading library: " << dlerror() << "\n";
            throw std::runtime_error("Library loading error");
        }
        //void型のポインタをreinterpret_castで関数ポインタ型に変換して返す
        return reinterpret_cast<FuncType*>(symbol);
    }

    ~DynamicLibraryWrapper(){
        if(handle){
            //動的ライブラリを閉じる
            dlclose(handle);
        }
    }
private:
    void* handle;
};


int main(){
    try{
        //標準入力によって、ロードする形にする?


        //init library load
        DynamicLibraryWrapper lib1("./add_test.so");
        //関数取得(関数の型情報を記載)
        //extern "C"{}で、名前マングリングは無効化済み
        auto AddLibrary = lib1.getFunction<int(int, int)>("Add");

        //ライブラリの関数を実行
        cout << AddLibrary(5,4) << "\n";

        //新しいライブラリをロード
        DynamicLibraryWrapper lib2("./sub_test.so");
        auto SubLibrary = lib2.getFunction<int(int, int)>("Sub");
        
        //新しいライブラリの関数を実行
        cout << SubLibrary(5,4) << "\n";

    }catch(const std::exception& e){
        cerr << "Exception: " << e.what() << "\n";
        return 1; //異常終了
    }

    return 0;
}

//g++ -std=c++20 -shared -o add_test.so add_test.cpp
//g++ -std=c++20 -shared -o sub_test.so sub_test.cpp

//g++ -std=c++20 -c -o dynamic_load.o dynamic_load.cpp
//g++ -std=c++20 dynamic_load.o -ldl
// ./a.out