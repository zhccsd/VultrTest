@echo off
set local=%~dp0
call %local%\make_env.bat
cd /d %local%
qmake
nmake clean
nmake debug
windeployqt %local%\bin\debug
pause