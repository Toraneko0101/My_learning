# AWKを使ったログの集約
```
・ログファイルからデータをフィルタリングして表示する
・AWKは比較的効率的に数十万行のデータを処理できる。
```

# 12.1 HTTPログファイルのフォーマット
```
ファイルを扱う際に、最初にすること
    0. ファイルの構造を理解する
    1. フィールドの区切り文字を見る
    2. それぞれのフィールドの意味を見る

```
- Apache HTTP Webサーバのアクセスログファイル
```
/var/log/apache2/access.log
    デフォルトの格納位置(Debian系)
```

- access.logについて
```
今回は、自分のログが20行しかなかったので
curl -O https://raw.githubusercontent.com/oreilly-japan/mastering-linux-shell-scripting-2e-ja/main/ch12/access.log
で、github上からダウンロードした

curl -O URL
    ダウンロードしたファイルを元のファイル名で保存
wget URL
    curl -O URLと同様
```
- 初見の感想
```
favicon.icoへのアクセスが404で失敗している。
/wp/?p=1951へのアクセスは200で通っている
```

- フィールドの意味
```
70.168.57.66
    クライアントのIPアドレス
-
    RFC1413およびidentdクライアントによって定義される識別子
    IdentityCheckが有効だとハイフン以外になる
-
    ユーザ認証が有効な場合はユーザID。無効ならハイフン
[11/Sep/2014:23:59:16 +0100]
    リクエストの日付と時刻。最後はオフセット
 "GET /wp/wp-content/uploads/2014/05/cropped-wp3.png HTTP/1.1"
    実際のリクエストとメソッド
200
    HTTPステータスコード
65326
    バイト数でのファイルサイズ
"http://theurbanpenguin.com/wp/?p=1951"
    アクセス元のURL
"Mozilla/5.0 (Windows NT 6.1; WOW64; rv:32.0) Gecko/20100101 Firefox/32.0"
    どのOSでどのブラウザからアクセスしてきたか

```
- 注意点
```
$ tail -3 access.log | awk '{print $4 $5}'
ダブルクォートの中のスペースにも反応してフィールドを分割しているため、予想と異なる挙動をする
```

- printf補足
```
$ tail -10 access.log | awk '{printf "%30.30s %5d\n", $7, $9}'
※上のコードは30文字を超えると省略される。超えない場合は空白スペースを入れる
```

# 12.2 Webログからのデータの表示

## 12.2.1 日付によるエントリの選択
```
・正規表現で2014年9月10日23時のエントリのみを表示する
・行数を表示するときはwc -lを使ってもいいが、incrementするのが一般的
・変数はおそらく0に初期化される
$ awk '{
    if ( $4 ~ /10\/Sep\/2014:23/){
        print $4
        COUNT++
    }
}
END{
    print COUNT
}
' access.log
```

## 12.2.2 404エラーの集約
```
・リクエストの種類で脅威を識別することもできる
$ awk '{
    if ( $9 ~ /404/){
        print $9, $7
    }
}' access.log | sort -u

sort -u
    ・sort | uniq
    ・ソートを行ったうえで同じ内容の行を1行に集約して出力する
```

## 12.2.3 HTTPアクセスコードの集約
```awk
{ record[$9]++ }
END {
    for (r in record){
        print r, "has occurred ", record[r], "times."
    }
}
```
- 説明
```
{ record[$9]++ }
    配列に保存する。statusが200ならrecord[200]が++される
    これはおそらく連想配列であり、$9の値をキーとする
    Pythonでいうdefaultdictのような動きをするので初期化が不要。配列のキーに対応する値が存在しない場合、AWKはそれを0とみなす。

for ( r in record)
    おそらく範囲forのようなもの。未定義の数字は飛ばされる
```
- 404コードだけ処理させる
```awk
{
    if( $9 == "404"){
        record[$9,$7]++
    }
}

END{
    for (r in record){
        print r, "has occurred ", record[r], " times."
    }
}
```
- 404コードだけ処理させる（解説）
```
record[$9,$7]++
    ・セパレータを挟み、添え字は文字列に変換される
    ・疑似的な二次元配列も可能(\034で連結しているのでゼロパディングする必要はない)
    ・実際は添え字をSUBSEP("\034")で処理しているので1次元
```

## 12.2.4 リソースのヒット数
- 特定のページやリソースが何回リクエストされたかをチェック
```

$ awk '{
    print $7
}' access.log | sort | uniq -c | sort -rn
```
- リクエストされたファイルについて限定する
```
awk '{
    if($7 ~ /php/){
        print $7
    }
}' access.log | sort | uniq -c | sort -nr
```
- 解説
```
sort
    printされた行に対して、sort
uniq -c
    重複する行をカウント
sort -nr
    -n 数値の大小で並び替え
    -r 降順で並び替え
```

## 12.2.5 画像のホットリンクの識別
```
画像の直リンク
    ・誰かがほかのサーバから画像にリンクを張ると、こっちの通信速度が低下する
```
- awkを使って画像のホットリンクを防止する
```
$ awk '
BEGIN{
    FS = "\""
}
{
    if ($2 ~ /\.(png|jpg|gif)/){
        print $4
    }
}' access.log | sort | uniq -c | sort -rn

※apacheを使っている場合は、小さな.htaccesファイルを用いて、
参照元が自分のドメインでないかどうかをチェック可能
https://httpd.apache.org/docs/current/mod/mod_rewrite.html
```

# 12.3 もっともランキングの高いIPアドレスの表示
```awk

# 最もランキングの高いIPアドレス -> サイトにアクセスするために最も多く使われたアドレスを表示する
# $1はIPなので、その回数を数える
{ ip[$1]++ }
END{
    for (i in ip){
        if (max < ip[i]){
            max = ip[i]
            maxnumber = i
        }
    }
        print maxnumber, "has accessed ", max, " times."
}
```

# 12.4 ブラウザーデータの表示
```awk
# アクセスするために使われたブラウザ情報
{ browser[$12]++ }
END {
    for (b in browser){
        print b, " has accessed ", browser[b], " times."
    }
}
```

# 12.5 Eメールログの処理
```
このファイルは$7がfrom or toらしい
受信ならtoで始まり、送信ならfromで始まる
```
- コード
```awk
# 受信メッセージ
$ awk '{
    if ($7 ~ /^to/){
        print $0
    }
}' mail.log
```

# 12.7 練習問題
- 12-1
```
$1
```
- 12-2
```
NR
```
- 12-3
```
sort | uniq
```
- 12 -4
```awk
$ awk '{
    if ($7 ~ /\.php/){
        php[$7]++
    }
}
END {
    max=""
    max_count=0
    for (p in php){
        if (php[p] > max_count){
            max = p
            max_count = php[p]
        }
    }
    print max , ":", max_count
}
' access.log
```