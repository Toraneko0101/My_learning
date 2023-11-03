
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