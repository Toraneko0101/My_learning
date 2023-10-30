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