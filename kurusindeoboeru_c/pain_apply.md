# 応用編

## 汎用計算

```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//angle to radian
#define RAD(ARC) ((ARC) * 3.14159 / 180)

int main(void){
    printf("%d\n", abs(-10));
    printf("%f\n", pow(8,3));
    printf("%f\n", sqrt(16));
    printf("%f\n", sin(RAD(30)));
    double syahenn = 5 / cos(RAD(40));
    double taihenn = syahenn * sin(RAD(40));
    printf("対辺:%f\n", taihenn);
    printf("高さ:%f\n", taihenn + 1.6);
}
```

## 疑似乱数
${X_{n+1} = (A \times X_n + B) \mod M}$
なお、A,B,Mは定数で、M>A, M>B, A>0, B>=0
```
問題点
    32bitならせいぜい数十億程度の周期しかないので
    多次元にするとランダム性が失われる

例
    A = 3, B = 5, M = 13, X_0 = 8
    X_1 = (3 * 8 + 5) % 13 = 3
    X_2 = (3 * 3 + 5) % 13 = 1
    X_3 = (3 * 1 + 5) % 13 = 8
    分かる通り、周期は最大でMになる
    以下を満たすとき、周期はM
    1. BとMが互いに素
    2. A-1がMのもつ全ての素因数で割り切れる
    3. Mが4の倍数の時は、A-1も4の倍数

メリット
    定数による加減算で実装可能
    状態記憶以外にほとんどメモリを使わないので軽い
    -> 回路として組むなら線形帰還シフトレジスタの方がいいとのことだったが

```
- 例
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int get_random(int min, int max);

int main(void){
    //乱数の最大値はRAND_MAX
    //rand() / RAND_MAXで 0 ~ 1
    //max - minで幅
    int min = 5;
    int max = 10;
    int num;
    //疑似乱数の種を現在時刻で初期化。シードは正の値に
    srand((unsigned int)time(NULL));

    for (int i=0; i<10; i++){
        //rand() 0 ~ RAND_MAX
        // 5 + rand()* 6 / (1.0 + RANS_MAX)
        // min-pattern
        // 5 + 0 = 5
        // max-pattern
        // 5 + (int)(6x  / 1 + x) = 5 + (int)5.9999 = 10
        printf("%d\n", get_random(1,6));
    }
}

int get_random(int min, int max){
    int num = min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
    return num;
}
```