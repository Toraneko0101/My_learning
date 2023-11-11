## level0
```
connect is bandit.labs.overthewire.org
on port 2220
The username is bandit0 
password is bandit0
```
- 回答
```
$ssh bandit0@bandit.labs.overthewire.org -p 2220
$cat readme
NH2SXQwcBdpmTEzi3bvBHMM9H66vVXjL
```

## level1
```
$ cat ./-
rRGizSaX8Mk1RTb1CNQoXTcYZWU6lgzi
```

## level2
```
$ cat "spaces in this filename"
aBZ0W5EmUfAf7kHTQeOwd8bauFJ2lAiG
```

## level3
```
$ cd inhere
$ ls -la
$ cat .hidden
2EW7BBsr6aMMoJ2HjW067dm8EgX26xNe
```

## level4
```
$ cd inhere
$ file ./-file*
$ cat ./-file07
lrIWWI6bB37kxfiCQZqUdOIYfr6eEeqR
```

## level5
```
- 注意点
    ・wc -cは各行の文字数をカウントするため、改行文字なども含める。よって実際のものよりバイト数が高くなる可能性あり
    ・find -size <num>c等の方がファイルのメタデータからとってくるので適切
    ・findはdirectoryの再帰的な検索を行う
    - $()で別のコマンドの引数として渡す
$ cd inhere
$ file *
$ find -type f
$ find -size 1033c ! -executable
$ file ./maybehere07/.file2
P4L4vucdmLnm8I7Vl7jG1ApGSfjYKqJU
```

## level6
```
$ man find
-user uname : ファイルの所有者がunameなら真
- group gname : ファイルの属するグループがgnameなら真
どこかに保存されるのでrouteから検索
エラーが多く出たので、エラーをブラックホールに捨てる
$ find -user bandit7 -group bandit6 -size 33c 2>/dev/null
$ cat ./var/lib/dpkg/info/bandit7.password
z7WtoNQU2XfjmMtWA8u5rN4vzqu4v99S
```

## level7
```
$ wc -c data.txt
$ cat data.txt | grep millionth
TESKZC0XvTetK0S9xNwm25STk5iWrBvP
```

## level8
```
$ sort data.txt | uniq -u
EN632PlfYiZbn3PhVK3XOGSlNInNE00t
```

## level9
```
$ file data.txt
data.txt data
$ grep -a -E "={2,}" data.txt
    -a, --text
    バイナリファイルをテキストファイルであるかのように処理
G7w8LIi6J3kTb8A7j9LgrywtEUlyyp6s
```

## level10
```
$ base64 -d data.txt
6zPeziLdR2RKNdNYFNb6nVCKzphlXHBM
```


## level11
```
rot13
※注意点
    文字コードとして扱いたいためさらに、single-quoteで囲む必要がある
    tr:文字の置換や切りつめ、削除を行う tr SET1 SET2 (SET1とSET2は1対1関係である必要がある)
    もしset1の方が短い場合、set2の終わりの方は無視される

※やめたやり方
str=$(cat data.txt)
for ((i=0; i<${#str}; i++)){
    printf "%d", "'${str:$i:1}'"
}

※採用案
$ cat data.txt | tr "A-Za-z" "N-ZA-Mn-za-m"
The password is JVNBBFSmZwKKOP0XbFXOoW8chDz5yVRv
```

## level12
```
繰り返しdump
    ・xxd -r  : 16進数 ->元のファイル
    ・圧縮されたファイルは  gzip  -d, gunzip,zcat を使うと元の形に復元することができる。(gzip -d *.gz)
    ・bzip2の場合は bzip -d *.bz
    ・tarの場合は -xvf (v:verbose)(x:アーカイブからファイルを抽出)(-f:アーカイブのファイル名を指定)
    ・-cだとアーカイブが作られる方
$ mkdir /tmp/hogehoge1
$ cp data.txt /tmp/hogehoge1/data.txt
$ mv /tmp/hogehoge1/data.txt /tmp/hogehoge1/data
$ cd /tmp/hogehoge1
$ xxd -r data >> data1
$ file data1
data1: gzip compressed data, was "data2.bin", last modified: Thu Oct  5 06:19:20 2023, max compression, from Unix, original size modulo 2^32 573 
$ mv data1 data1.gz
$ gzip -d data1.gz
$ file data1
data1: bzip2 compressed data, block size = 900k
$ mv data1 data1.bz2
$ bzip2 -d data1.bz2
$ file data1
data1: gzip compressed data, was "data4.bin", last modified: Thu Oct  5 06:19:20 2023, max compression, from Unix, original size modulo 2^32 20480
$ mv data1 data1.gz
$ gzip -d data1.gz
$ file data1
data1: POSIX tar archive (GNU)
$ mv data1 data1.tar
$ tar -xvf data1.tar 
$ mv data5.bin data5.tar
$ tar -xvf data5.tar
$ file data6.bin
$ data6.bin: bzip2 compressed data, block size = 900k
$ mv data6.bin data6.bz2
$ bzip2 -d data6.bz2
$ file data6
$ mv data6 data6.tar
$ tar -xvf data6.tar
$ file data8.bin
data8.bin: gzip compressed data, was "data9.bin", last modified: Thu Oct  5 06:19:20 2023, max compression, from Unix, original size modulo 2^32 49
$ mv data8.bin data8.gz
$ gzip -d data8.gz
$ file data8
data8: ASCII text
$ cat data8
The password is wbWdlBxEir4CaE8LaPhauuOo6pwRmrDw
```

## level13
```
※注意点
    ------BEGIN等の行も張り付けないと秘密鍵として認識されない
    chmod 700にしないとPermissionの関係でエラる
$ ls
sshkey.private
$ cat sshkey.private 
-----BEGIN RSA PRIVATE KEY-----
-----END RSA PRIVATE KEY-----

クライアント側でRSAキーを生成する
    $ cd ~/.ssh
    $ vim id_rsa
    $ <上記のRSAを張り付け>
    $ chmod 700 id_rsa

```

## level14
```
補足:
    nc
        cat "Exit" | nc localhost 30000なら、30000portにExitコマンドを送っていることになる
        Exitは標準入力として渡される
$ cat /etc/bandit_pass/bandit14 | nc localho
st 30000
Correct!
jN2kgmIXJ6fShzhT2avhotn4Zcka6tnt
```

## level15
```
openssl s_client [-connect host:port]
    遠隔ホストにSSL/TLSを使って接続するクライアント
-ign_eof
    入力まで処理したときに接続を阻害する
$ echo "jN2kgmIXJ6fShzhT2avhotn4Zcka6tnt" | openssl s_client -connect localhost:30001 -ign_eof

Correct!
JQttfApK4SeyHwDlI9SXGR50qclOAil1
```

## level16
```
$ nmap -p31000-32000 localhost
Starting Nmap 7.80 ( https://nmap.org ) at 2023-11-11 05:55 UTC
Nmap scan report for localhost (127.0.0.1)
Host is up (0.00043s latency).
Not shown: 995 closed ports
PORT      STATE SERVICE
31000/tcp open  unknown
31046/tcp open  unknown
31518/tcp open  unknown
31691/tcp open  unknown
31790/tcp open  unknown
31960/tcp open  unknown

SSL対応というのでopenssl s_clientで接続する
$ openssl s_client -connect localhost:31046
No client certificate CA names sent

$ echo "JQttfApK4SeyHwDlI9SXGR50qclOAil1" | openssl s_client -connect localhost:31790 -ign_eof
sshを得た

$ sudo vim ~/.ssh/bandit17_rsa

id_rsa以外の場合は、ssh接続時に-iオプションを使う
$ ssh bandit17@bandit.labs.overthewire.org -p 2220 ~/.ssh/bandit17_rsa
```

## level17
```
$ diff passwords.new passwords.old
42c42
< hga5tuuCLF6fFzUpnagiMN8ssu9LFrdg
---
> p6ggwdNHncnmCNxuAt0KtKVq185ZU7AW
```

## level18
```
sshでリモートマシンのコマンドを実行したい

ssh [-l user] [-p port] host [command]

$ ssh bandit18@bandit.labs.overthewire.org -p 2220 cat readme
awhqfNnAbc1naukrpqDYcF95h7HoMTrC
```

## level19
```
・setuidパーミッションが設定されたプログラムは、その所有者のユーザーIDで実行される
・実行するにはプログラムをコマンドラインで実行すればいい
・つまり、今回の場合、bandit20が所有者なのでbandit20として、以降のコマンドが実行される(ls -l)

$ ls -l /etc/bandit_pass/bandit20
-r-------- 1 bandit20 bandit20 33 Oct  5 06:19 /etc/bandit_pass/bandit20

$ ./bandit20-do
Run a command as another user.
  Example: ./bandit20-do id

$ strings bandit20-do
Run a command as another user.
  Example: %s id

$ ./bandit20-do cat /etc/bandit_pass/bandit20
VxCazJaVykI6W36BkBU0mJTCM8rR95XT

```
