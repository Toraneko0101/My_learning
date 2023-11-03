#  awk -f host.awk search=packt virtualhost.conf
#  awk -f host.awk search=www\..+\.com virtualhost.conf 
# コマンドラインで変数を宣言可能
BEGIN{
    RS="\n\n"
}
{
    if ($0 ~ search){
        print $0
    }
}