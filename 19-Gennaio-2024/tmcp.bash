#!/bin/bash

if [[ "$1" != "-1" && "$1" != "-2" ]];
then
    dir1="$1"
    dir2="$2"
    mode="0"
else 
    dir1="$2"
    dir2="$3"
    mode="$1"
fi

echo "Mode: $mode"
echo "Dir1: $dir1"
echo "Dir2: $dir2"

files1=($(find $dir1 -printf '%P\n'))
files2=($(find $dir2 -printf '%P\n'))

echo "Files1: ${files1[@]}"
echo "Files2: ${files2[@]}"

echo "Result:"

if [[ "$mode" == "0" ]];
then
    for i in "${files1[@]}"
    do
        for j in "${files2[@]}"
        do
            if [[ "$i" == "$j" ]];
            then
                echo $i 
            fi
        done
    done
else
    declare -a files
    declare -a nfiles
    if [[ "$mode" == "-1" ]];
    then
        files=("${files1[@]}")
        nfiles=("${files2[@]}")
    elif [[ "$mode" == "-2" ]];
    then
        files=("${files2[@]}")
        nfiles=("${files1[@]}")
    fi
    declare -i bool
    for i in "${files[@]}"; do
        bool=0
        for j in "${nfiles[@]}"; do
            if [[ "$i" == "$j" ]]; then
                bool=1
            fi
        done
        if [[ $bool == 0 ]]; then
            echo $i
        fi
    done
fi

