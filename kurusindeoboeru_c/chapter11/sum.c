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