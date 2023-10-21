# 7章

- 条件分岐
```c
#include <stdio.h>

int main(void){
    int digit;
    scanf("%d", &digit);
    if(digit <= -1){
        printf("%dは負の整数です\n", digit);
    }
    if(digit % 3 == 0 && digit % 5==0){
        printf("%dは15の倍数\n", digit);
    }else if(digit % 3== 0){
        printf("%dは3の倍数\n", digit);
    }else if(digit % 5 == 0){
        printf("%dは5の倍数\n", digit);
    }else{
        printf("%dは3の倍数でも5の倍数でもない",digit);
    }

    return 0;
}
```
```c
// if val1 == val2 : ans = true
ans = val1 == val2

```

- scanfと&
```
&       : アドレス演算子。変数が指し示すメモリのアドレスを知りたいときに使う
scanf   : で値を格納するときはアドレスの場所さえ分かればいい
list    : text[10]ならtextがtext[0]の位置を指し示すので、&は不要
*       : 関節演算子。アドレスを指定して、その中身を変数として使う
*text   : これの場合、textのアドレスは、text[0]なのでその中身が指し示される。これを%cとして使うので、当然先頭位置の文字が印字される
```
- formatしておく
```c
#include <stdio.h>

int main(void){
    char text[128];
    printf("文字列を入力してください(9文字まで)\n");
    scanf("%9s", text);

    printf("入力された文字列の先頭文字は%cです", *text);
    return 0;
}
```
- %9sとしなかった場合(バッファオーバーフロー)
```
文字列を入力してください(9文字まで):
ppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp
ppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp
ppppppppppppppppppppppppppppppppppppppppppppppppp
*** stack smashing detected ***: terminated
Aborted
```

## 練習問題7

### 1-1
```
Q. 条件判断の時には0以外の数値のことをなんと呼ぶか。
A. 偽
```
### 1-2
```
1-2.
Q. 条件判断の時には0のことをなんと呼ぶか。
A. 真
```
### 1-3
```
1-3.
Q. {}で囲むことで、複数の文をまとめることをなんと呼ぶか。
A. ブロック文
```

### 2-1
```c
#include <stdio.h>

int main(void)
{
    int value, rest;

    scanf("%d", &value);

    rest = value % 2;

    if (rest == 0) printf("E");
    if (rest == 1) printf("O");

    printf("\n");

    return 0;
}
```
```
A. 入力された値が偶数ならE,奇数ならOと出力
```

### 3-1
```
Q. 西暦年を入力すると、その年にオリンピックが開かれるか、
表示するプログラムを作成せよ。
可能なら、夏季と冬季の区別も表示できればなお良い。
ヒント:シドニー五輪(夏)は2000年開催であった。

※条件がややこしくなるので、
以前夏季と冬季が同じ年だった時期のことは無視する。

```
```c
#include <stdio.h>

int main(void){

    int years;
    
    printf("西暦年を入力してください。ex) 2000 : ");
    scanf("%d", &years);

    if(years % 4 == 0){
        printf("%dは夏季オリンピックの年", years);
    }else if(years % 4 == 2){
        printf("%dは冬季オリンピックの年", years);
    }else{
        printf("%dはオリンピックがありません", years);
    }

    return 0;

}
```

### 4-1
```
Q. if (-1) printf("OK\n");

上記のプログラムを実行すると、OKが表示されるが、
それはなぜか簡潔に説明せよ。

A. 0以外はTrue扱いなので
```

# 8章
- switch & case
- cのcaseはor等が不可。弱い
```c
#include <stdio.h>

int main(void){

    int num;
    scanf("%d", &num);
    switch(num){
        case 1:
        case 10:
            printf("%d\n", 1);
            break;
        case 2:
            printf("%d\n", 2);
            break;
        default:
            printf("%d\n", -1);
            break;
    }

    return 0;
}
```

## 練習問題

### 1
```
A. else
A. else-if
A. switch-case
```

### 2
```
olympicの開催年1
```

### 3
```
caseとdefaultで書く。breakを忘れないように
```

### 4
```
共通した処理ならbreakは要らない。
switch文は対応する番号のcase文にJumpする機能しかもっていないので、
brakeをすることでcase文から抜ける
```

# 9章
- loop
```c
#include <stdio.h>

int main(void){

    for (int i=1; i<=10; i++){
        if(i==3){
            break;
        }
        if(i==2){
            continue;
        }
        printf("%d\n", i);
    }


    return 0;
}
```
## 練習問題

### 1
```
A. カウンタ変数
A. 無限ループ
```

### 2
```
1~9割引の値段表示
```

### 3
- 九九
```c
#include <stdio.h>

int main(void){

    for (int i=1; i<=10; i++){
        if(i==3){
            break;
        }
        if(i==2){
            continue;
        }
        printf("%d\n", i);
    }


    return 0;
}
```

## 4
```
カウンタ変数をstepに指定した分だけ変化させ、条件を外れた場合離脱する
```

# 10章
- ねずみ算(100万を超える月)
```c
#include <stdio.h>
#include <math.h>

int main(void){

    int judge = pow(10,6);
    int current_money = 1;
    int cnt = 1;
    while(1){
        current_money *= 2;
        cnt ++;
        if (current_money > judge){
            break;
        }
    }
    printf("%d\n", cnt);
}
```
- do-while
```c
#include <stdio.h>

int main(void){

    double r;
    double s;

    do{
        printf("半径?: ");
        scanf("%lf", &r);
    }while (r < 0);
        s = r * r * 3.14;
        printf("面積は %f です\n", s);

    return 0;
}
```

## 練習問題

### 1
```
A. 先判定
A. 後判定
```
### 2
```
年利1%で初期10000の時、何年で15000になるか
```

### 3
```
scanfとdo-while使う
```

###
```
後判定なので、1度は必ず入力処理を踏ませられるため
```

# 11章
- プロトタイプ宣言: 引数は変数を省略して、型だけ書いてもいい。コンパイラは変数の実装まで管理しない
- 仮引数：関数宣言に書かれた引数の型と名前。使用する変数を指定
- 実引数：関数を呼び出すときに渡す数値
```c
# include <stdio.h>
//printf等のプロトタイプ宣言はstdio.hファイル内に書かれている
int sum(int, int);

int main(void){
    int i,j;
    scanf("%d %d", &i, &j);
    int ans = sum(i,j);
    printf("%d\n", ans);
    return 0;
}

int sum(int min, int max){
    int ans = (min + max) * (max - min + 1) / 2;
    return ans;
}
```

## 練習問題
### 1
```
A. プロトタイプ宣言
A. 仮引数
A. 実引数
A. 戻り値
```
### 2
```
三角形の面積
```
### 3
```
略
```
### 4
```
処理を一つの部品としてまとめ、
再度同じ処理を行う時に、二度手間を防ぐため
```

# 12章
- スコープ
- グローバル変数：自動的に0に初期化
- スコープの内側の名前が優先される
- defaultでは1つのソースファイル内でglobal変数は共有される

- static:静的なローカル変数:関数を抜けても値が保持されるが、別箇所では使えない
- 関数の呼び出し回数のcntや、以前の位置の記憶などに使用可能
```c
#include <stdio.h>

void cnt();

int main(void){
    cnt();
    cnt();
    cnt();
    return 0;
}

void cnt(void){
    static int count;
    count++;
    printf("%d\n", count);
}
```
## 練習問題
### 1
```
A. ローカル変数
A. グローバル変数
A. static変数
```
### 2
```
local: count
global: var
static: arc
```

### 3
```
同名を使いたいことがあり、
その際の重複確認を容易にするため
```