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
*text   : これの場合、text[0]の場所が指し示される。これを%cとして使うので、当然先頭位置の文字が印字される
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
- %9sとしなかった場合
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