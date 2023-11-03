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