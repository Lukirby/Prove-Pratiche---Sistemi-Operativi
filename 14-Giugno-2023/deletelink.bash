#!/bin/bash

if [[ -z $1 ]]; then
    echo "Uso: $0 <dir>"
    exit 1
fi

dir=$1

for file in $(find $dir -type l); do
    path=$(readlink $file)
    if [[ $path == /* ]]; then
        echo "Il link simbolico $file punta a un percorso assoluto."
        rm $file
    else
        echo "Il link simbolico $file punta a un percorso relativo."
    fi
done

find $dir -type l -exec readlink {} \;