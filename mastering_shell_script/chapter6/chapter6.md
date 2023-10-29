# 6 ループを使った反復処理

# 6.1 forループ
```
$ type for
for is a shell keyword

・forはシェルキーワードであり、スクリプト内で使ったり、コマンドライン上で直接使うこともできる。
・シェルキーワードはスクリプトの構文と制御構造を操作するために使用される
```
- ユーザパスワード(コード)
```bash
sudo -i
for u in bob joe; do
    useradd $u
    echo "$u:Password1" | chpasswd
    passwd -e $u
done
```
- ユーザパスワード(説明)
```
useradd:
    ユーザの作成
chpasswd:
    ・複数のパスワードをバッチモードで更新
    ・root権限が必要。非対話的
    ・echo "username:password" | chpasswdのようにpassを変更できる
    ・ファイルに記載して、catしたデータを渡すこともできる。コマンド履歴に残らないのでそっちの方がいい
passwd -e username:
    指定したユーザアカウントのパスワードを期限切れにする。

```
- sudo -iとsudo su -の違いについて
```
sudo
    ・他のユーザの権限でプログラムを実行するコマンド
    ・sudo -i: ログインシェルとして指定されているシェルを実行

su
    他のユーザにスイッチする管理系のコマンド。

環境変数をクリアする意味合いだとsu -の方が強そう


```
- ディレクトリ内のファイル処理（コード）
```bash
#!/bin/bash
for f in *; do
    stat "$f"
done
```
- ディレクトリ内のファイル処理（説明）
```
stat:
    ファイルの属性や日付などを表示
```

- Ubuntuの日本語化
```
$ sudo apt install language-pack-ja
$ sudo dpkg-reconfigure locales
$ exit
```