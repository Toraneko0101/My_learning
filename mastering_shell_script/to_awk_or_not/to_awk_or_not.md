# 1. Simple examples

- coins.txt
```
gold     1    1986  USA                 American Eagle
gold     1    1908  Austria-Hungary     Franz Josef 100 Korona
silver  10    1981  USA                 ingot
gold     1    1984  Switzerland         ingot
gold     1    1979  RSA                 Krugerrand
gold     0.5  1981  RSA                 Krugerrand
gold     0.1  1986  PRC                 Panda - silver lined
silver   1    1986  USA                 Liberty dollar
gold     0.25 1986  USA                 Liberty 5-dollar piece
silver   0.5  1986  USA                 Liberty 50-cent piece
silver   1    1987  USA                 Constitution dollar
gold     0.25 1987  USA                 Constitution 5-dollar piece
gold     1    1988  Canada              Maple Leaf
```

- silverを先頭に含む行の検索
```
$ awk '/^silver/' coins.txt

コマンドが指定されていないと、デフォルトでは一致した行を出力する。
```

- 1980年より前に鋳造された全てのコインのリスト
```
$ awk ' $3 < 1980 {print $3, "  ", $5, $6, $7, $8}' coins.txt
```

- 1986年より古い銀コインを探す
```
$ awk '{
    if ($3 < 1986 && $1 ~ /^silver/){
        print $0
    }
}' coins.txt
```

- 数字の分析(一列目が4より大きい場合のみ)
```
$ awk ' $1 > 4{
    print $1 + $2 * $3
}' 123.txt
```
- 2番目の列の値が1番目の列より小さい場合各行の3番目を出力
```
$ awk '
$2 < $1{
    print $1,$2,$3,$1+$2*$3
}' 123.txt
```

## AWKコマンドライン構文
```
NF: フィールド
$NF: フィールド数の値を表示
$NF-2:フィールド数の値-2
$(NF-2):最後から3番目のフィールド

123.txtを2回指定すると、FNRがファイルの行数を意味していることが分かる
```

- printfとprint
```
printは改行が行われる。
セパレータはデフォルトで改行とtab,spaceに作用する
```

- practice
```
$ awk '{
    printf "%8s %8s %8s\n", $1, $2, $3
}' pay.txt
```

# 2. Teasing with grep