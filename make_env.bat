@echo off

set qt_dir=C:\Qt\Qt5.7.1\5.7\msvc2013
set vc_dir=C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC

call "%qt_dir%\bin\qtenv2.bat"
call "%vc_dir%\vcvarsall.bat"