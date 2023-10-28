#!/bin/bash

shopt -s nocasematch

read -p "Type color or mono for script output:"
if [[ $REPLY =~ colou?r ]]; then
    source $HOME/program_file/my_learning/mastering_shell_script/snippets/color
fi

# paramが設定されていない場合は、モノクロ表示
echo -e "${RED}This is $0 $RESET"
shopt -u nocasematch
exit 0