@echo off
@rem Batch file for Andes Technology Product to launch ICEman
Set HOME=%~dp0
For %%A in ("%HOME:~0,-1%") do (
    Set CYGPATH=%%~dpA
)
set PATH=%CYGPATH%cygwin\bin;%HOME%;%PATH%
IF EXIST "%CYGPATH%cygwin\bin\bash.exe" set SHELL=/bin/bash
set CYGPATH=cygpath
"..\cygwin\bin\bash.exe" --login -i

:END