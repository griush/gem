@echo off
call Build.bat
pause
pushd bin
gem-test.exe
popd