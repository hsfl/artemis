#!/bin/bash


# Check if the script is already running
if pidof -o %PPID -x "run.sh">/dev/null; then
    echo "Process already running"
    exit
fi


python ~/python/main.py


