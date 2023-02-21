@echo off
if not exist bin\ (
    mkdir bin 
)
pushd ..
clang++ -std=c++20 -o test/bin/gem-test.exe test/main.cpp -Iinclude
popd