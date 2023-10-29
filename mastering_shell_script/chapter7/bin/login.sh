#!/bin/bash

show_system(){
    echo "The uptime is:"
    uptime
    echo
    echo "CPU Detail:"
    lscpu
    echo
    echo "User"
    whoami
}

show_system > login.txt