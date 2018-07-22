@echo off
set local=%~dp0
call %local%\make_env.bat
cd /d %local%
qmake -tp vc
pause