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