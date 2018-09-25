@echo off
title Checker

g++ data.cpp -std=c++17 -O2 -o data.exe
g++ std.cpp -std=c++17 -O2 -o std.exe
g++ chk.cpp -std=c++17 -O2 -o chk.exe

set /a caseNum=1

:loop
data.exe > input.txt
std.exe < input.txt > output_std.txt
chk.exe < input.txt > output_chk.txt

fc output_std.txt output_chk.txt

if %errorlevel% == 0 (
    echo #%caseNum%: Accepted
    set /a caseNum=%caseNum%+1
    goto loop
) else (
    echo #%caseNum%: Wrong Answer
    pause
)