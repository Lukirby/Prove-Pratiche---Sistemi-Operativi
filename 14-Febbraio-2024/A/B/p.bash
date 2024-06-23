#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <args>"
    exit 1
fi

for i in $@; do
    echo -n "$i "
done
