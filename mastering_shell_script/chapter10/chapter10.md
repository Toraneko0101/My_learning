# AWKの基礎
```
sedでは文字列操作について学べた。
```

# 10.1 AWKの背後にある歴史
```
・AWKは70年代に生まれた
・gawk
    GNU AWK。だいたいこれ
tawk
    Solaris,DOS,Windowsで動作する
mawk
    実行速度の向上が目的
BWK awk
    macOSなど

・gawkにはawkという名前のシンボリックリンクが存在しているので、awkとgawkは同じコマンドになる
・Ubuntuの場合はデフォルトのリンク先がmawkになっているので、gawkをinstallする

・/usr/bin/awk -> /etc/alternatives/awk

```
- awkによるHello World
```
$ awk 'BEGIN { print "Hello World!" }'

BEGINブロック
    ヘッダ情報の作成
ENDブロック
    サマリー情報を作成
・メインのブロックとは別に作成可能
```

# 10.2 ファイルの内容の表示とフィルタリング
- ファイル全体を表示
```
$ awk '{ print }' /etc/passwd
$ awk '{ print $0 }' /etc/passwd

$0
    行全体を表す
$1
    1番目のフィールドを表す neko,inu,nezumiならneko
```
- フィールドの区切り文字を指定する
```
$ awk -F":" '{ print $1 }' /etc/passwd

-F
    フィールドセパレータを指定
```
- BEGINブロックの中で行う
```
$ awk 'BEGIN { FS=":" } { print $1 }' /etc/passwd
```
- ENDブロックの使い方
```
※sammaryデータを表示したいときに使う
NR
    現在までに処理した行の数

$ awk 'BEGIN {FS=":"} {print $1 } END { print NR }' /etc/passwd
```

- 単一引用符を使うと、複数行にわたってコードを書ける
```
$ awk '
BEGIN { FS=":" }
{ print $1 }
END { print "Total:", NR }' /etc/passwd
```

- 処理中の各行に行番後を表示```
```
※,なら要素を並べて表示
$ awk '
BEGIN { FS=":" }
{ print NR,$1 }
END { print "Total:", NR }' /etc/passwd
```
- 各ブロックは省略できる
```
wc -lコマンドのようなもの
$ awk '
END { print "Total_row: ",NR }' /etc/passwd
```

- 選択した行だけを処理
```
- ~5行
$ awk 'NR<6' /etc/passwd

- 8~12行目
$ awk 'NR==8,NR==12' /etc/passwd

- 正規表現を適応(2つのスラッシュの間に書く)
$ awk '/bash$/' /etc/passwd
```

# 10.3 AWKの変数
```
FIELDWIDTHS
    フィールドの長さを指定
RS
    レコードセパレータを指定
FS
    フィールドセパレータを指定(default space)
OFS
    出力フィールドセパレータを指定(default space)
ORS
    出力レコードセパレータ
FILENAEE
    処理されるファイル名
NF
    現在のレコードのフィールド数

FNR
    現在のファイルにおいて処理したレコードの数
    (NRは通し番号で、FNRはファイル毎に振られる番号)

IGNORECASE
    大文字と小文字を区別しない
```
- 日本語化後に英語のマニュアルを見る方法
```
LANG=C man gawk
※gawkの日本語版マニュアルは糞古いので英語版を見ること
```

- 変数を用いて中身を切り出す
```
/*ファイル*/
John Doe
15 back street
(123) 455-3584

Mokhtar Ebrahim
10 Museum street
(456) 352-3541

/*コード*/
# FS="\n"で、改行がセパレータの区切り目となった
# RS=""で、空行がレコードの区切り目となった
# OFS=" "で、出力セパレータが半角スペースとなった
$ awk '
BEGIN{FS="\n"; RS=""; OFS=" "} 
{print $1,$3}' test.txt
```
- NRとFNR
```
awk 'BEGIN{FS="\n"}
{print $1,"FNR="FNR}' test2.txt test2.txt

Welcome to AWK programming FNR=1
This is a test line FNR=2
And this is one more FNR=3
Welcome to AWK programming FNR=1
This is a test line FNR=2
And this is one more FNR=3

※RSのデフォルトは\n

$ awk '
BEGIN {FS="\n"}
{print $1, "FNR:"FNR, "NR:"NR}
END{print "Total lines: ", NR}' test2.txt test2.txt

Welcome to AWK programming FNR:1 NR:1
This is a test line FNR:2 NR:2
And this is one more FNR:3 NR:3
Welcome to AWK programming FNR:1 NR:4
This is a test line FNR:2 NR:5
And this is one more FNR:3 NR:6
Total lines:  6
```

## 10.3.1 ユーザ定義変数
```
変数は文字で始まっていればいい
$ awk '
BEGIN{
    var="Welcome to the Under Ground"
    print var
}'
- 文字列連結はスペースで
$ awk '
BEGIN{
    str1="Neko"
    str2="I like "
    str3=str2 str1 "."
    print str3
}'
```

# 10.4 条件文

## 10.4.1 if文
```
$ awk '
{if ($1 > 50)
    print $1
}' test3.txt

- else文
$ awk '
{
    if($1 > 50){
        x = $1 * 2
        print x
    }else{
        x = $1 * 3
        print x
    }
}' test3.txt

※波括弧を使わない場合は、;で同一行に記載可能
※コードをファイルに保存し、-fでawkコマンドに割り当て可能
```

## 10.4.2 whileループ
```
・i++が使える。
・RS区切りで処理する
・$iはセパレータから反映するためのもの
$ awk '{
    total = 0
    i = 1
    while(i < 4){
        total += $i
        i++
    }
    mean = total / 3
    print "Mean value:", mean
}' test4.txt
```

## 10.4.3 forループ
```
$ awk '{
    total = 0
    for (var = 1; var < 4; var++){
        total += $var

    }
    mean = total / 3
    print "Mean value:", mean
}' test4.txt
```

# 10.5 出力結果の書式設定
- 工夫無し
```
$ awk '
BEGIN {FS=":"}
{print $1,$3,$7}
' /etc/passwd

※列の幅が均等ではなくなる
```
- printfでフォーマット指定
```
$ awk '
BEGIN {FS=":"}
{ printf "%10s %4d %20s\n", $1, $3, $7}
' /etc/passwd

%10
    10文字の幅
```
- Headerを指定
```
$ awk '
BEGIN {
    FS=":";
    printf "%10s %4s %20s\n", "Name", "UID", "Shell"
}
{
    printf "%10s %4d %20s\n", $1, $3, $7
}' /etc/passwd

      Name  UID                Shell
      root    0            /bin/bash
      ...   ...                  ...
```
- 色を付ける(関数の作成)
```
※仮引数に$は必要ない。関数内でそれを使うと、呼び出しの際に与えられた実引数を参照できなくなるため。適当な名前でももちろんいい。
$ awk '
function green(a,b,c){
    printf "\033[32m %10s %4s %20s \033[0m\n", a,b,c
}
BEGIN{
    FS=":";
    green("Name:", "UID:", "Shell:")
}
{
    printf "%10s %4d %20s\n",$1,$3,$7
}' /etc/passwd
```
# 10.6 UIDを使ってユーザ表示をさらにフィルタリングする

- UIDが1000以上のユーザ(一般ユーザ)を表示する
```
$ awk '{
    FS=":";
    if($3 > 999){
        printf "%10s %4d %20s\n", $1, $3, $7
    }
}' /etc/passwd

※nobodyユーザ
    UID:65534
    ・NFS(network file system)を使用してファイル共有する際、
    サーバ側のファイルをクライアントに提供する際のセキュリティ問題を解決するために使用することがある。
    ・つまり、通常ユーザからのアクセスを制限するために用いられる

    ※フィールドについては$でアクセス。変数に関しては$は要らない

```

# 10.7 AWKの制御ファイル
- passed.awk
```awk
function green(a,b,c){
    printf "\033[32m %10s %4s %20s \033[0m\n", a,b,c
}
BEGIN{
    FS=":";
    green("Name:", "UID:", "Shell:")
}

{
    printf "%10s %4d %20s\n",$1,$3,$7
}
```
```
以下で実行
    $ awk -f passed.awk /etc/passwd
```

## 10.7.1 組み込み関数
```
awkに用意されている関数に関して

文末のセミコロンが要らないのはスクリプト言語だからだと思う。
コンパイラ型の言語は、プログラム全体がコンパイルされるので、文の終了を明示する必要があるが、1行ずつ解釈する場合は構わない。
本当に1行ずつ解釈されているかは別として
```
- standard.awk
```awk
# awk内でデータを生成して、ファイルから読み込まないので以下のようにした
{
    x=sqrt(5)
    y=rand()
    printf "%f %f", x, y
    print
    exit 0
}
```

# 10.8 まとめ
```
・慣れるまでは、ワンライナーより見やすく書く
・正直shellの文法より他のプログラム言語に近くて好きだ
・スクリプト言語なので;が要らないのもいい
```

# 10.9 練習問題
- 10-1
```
変数のくせしてドル記号がついているので表示されない
```
- 10-2
```
$2の値がないので、出力されない。
```

- 10-3
```
while (i < 4)にしないと、$1 $2までしかtotalに加算されない
```

- 10-4
```
rootのみなので1行
```