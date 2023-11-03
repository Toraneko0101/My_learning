# AWKを使ったlastlogの改良
```
lastlog
    ・全てのユーザについての最後のログイン時刻をレポート
    ・システムにログインするために一度も使われたことないユーザアカウントを除外したり、rootについてを除外したり

・RS(record separator)についても学ぶ
```

# 13.1 AWKの範囲を使ってデータを除外する

## 13.1.1 lastlogコマンド
- UIDを制限
```
$ lastlog -u 1000-5000
```
## 13.1.2 AWKによる行のフィルタリング
```
$ LANG=C lastlog | awk '{
    if ($0 !~ /Never|User/){
        print $0
    }
}'
```
## 13.1.3 マッチした行のカウント
```
$ LANG=C lastlog | awk '{
    if ($0 !~ /Never|User/){
        cnt++
        print $0
    }
}
END{
    print "=========================="
    print "Total Number of Users processed: ", cnt
}'
```

## 13.2 フィールド数に基づく条件
```
・Userがserverの物理ホストに直接ログインしている場合、lastlogの出力結果にホストのフィールドは表示されない
・サーバコンソールに直接接続しているユーザはフィールドの数が異なっている。
・つまり、フィールドの数で(NFでわかる)表示フィールドを切り分けるわけか

$ LANG=C lastlog | awk '
BEGIN{
    printf "%8s %11s\n", "Username", "Login date"
    print "============================"
}
{
    if($0 !~ /Never|User/){
        cnt++
        if(NF == 8)
            printf "%8s %2s %3s %4s\n", $1, $5, $4, $8
        else
            printf "%8s %2s %3s %4s\n", $1, $6, $5, $9
    }
}
END{
    print "=========================="
    print "Total Number of Users processed: ", cnt
}'
```

# 13.3 AWKのRSを操作してXMLデータを処理する
```
複数行を1つとみなして操作したい
```
## 13.3.1 Apacheバーチャルホスト
```
該当ファイルは空行で区切っている。つまりRS変数は
RS="\n\n"
```
- コード
```awk
#  awk -f host.awk search=packt virtualhost.conf
# コマンドラインで変数を宣言可能
BEGIN{
    RS="\n\n"
}
{
    if ($0 ~ search){
        print $0
    }
}
```

## 13.3.2 XMLカタログ
```
gawkの場合、search変数に拡張正規表現の検索パターンが使える
```
```
区切り文字に以下を設定する
FS="[><]"
2文字以上の時は[]がいるのか?

CSVで書き直すため、OFSを調整する
拡張正規表現におけるOR条件はパイプ一つ(|)
```
- コード(> or <で区切る)
```awk
BEGIN{
    FS="[><]"
    RS="\n\n"
    OFS="/"
}
{
    if ($0 ~ search){
        print $4, ": ", $5, $8, ": ", $12 ": ", $13
    }
}
```

# 13.5 練習問題
- 13-1
```
$ LANG=C lastlog | awk '{
    if ($0 ~ /Never/){
        print $1
    }
}
END {
    print NR , "人"
}
'
```
- 13-2
```
$ LANG=C lastlog | awk '{
    if ($0 ~ /Never/){
        print $1
    }
}'

```