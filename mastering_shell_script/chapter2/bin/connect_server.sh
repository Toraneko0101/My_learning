#!/bin/bash

# Author: @Toraneko0101
# ssh接続のための情報を入力する
# Last Edited: 25/10/2023

read -p "Which server do you want to connect to: " server_name
read -p "Which username do you want to use: " user_name
ssh ${user_name}@server_name