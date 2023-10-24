#!/bin/bash

: << "COMMENT"

Author: @Toraneko0101
Web: https://github.com/Toraneko0101

指定したサーバにpingを送るスクリプト

Last Edited: 25/10/2015
COMMENT

read -p "Which server should be pinged " server_addr
ping -c3 $server_addr 2>&1 > /dev/null || echo "Server Dead"
