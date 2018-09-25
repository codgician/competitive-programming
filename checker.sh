#!/bin/bash

g++ data.cpp -std=c++17 -O2 -o data
g++ std.cpp -std=c++17 -O2 -o std
g++ chk.cpp -std=c++17 -O2 -o chk

caseNum=1

while true; do
    ./data > input.txt
    ./std < input.txt > output_std.txt
    ./chk < input.txt > output_chk.txt
    if diff output_std.txt output_chk.txt; then
        printf "Case #%s: Accepted\n" $caseNum
        caseNum=$((caseNum+1))
    else
        printf "Case #%s: Wrong Answer\n" $caseNum
        exit 0
    fi
done