@echo off
if not exist bin\ (
    mkdir bin 
)
pushd ..
g++ -o test/bin/gem-test.exe test/main.cpp -Iinclude
popd

pause
pushd bin
gem-test.exe
popd