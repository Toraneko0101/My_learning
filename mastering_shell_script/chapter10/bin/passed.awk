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