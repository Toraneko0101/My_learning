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
