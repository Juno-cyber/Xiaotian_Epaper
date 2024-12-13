@echo off
setlocal enabledelayedexpansion
rem mode con: cols=80 lines=10
rem chcp 437
set VERSION=o26_download_script_v2.4beta
title %VERSION%
rem echo current path: %cd%
set PATH=%cd%/dll;%SystemRoot%\system32;%SystemRoot%;%SystemRoot%\System32\Wbem;%PATH%
tasklist|find /i "ICEman.exe" && taskkill /f /t /im ICEman.exe
:BEGIN
set work_path=bin
set index=1
set "filename=aa"
cd %work_path%
echo %VERSION%
echo List BIN files
echo -------------------------------------------------
for /R %%s in (*.bin) do ( 
echo !index! %%~ns%%~xs
set array_!index!=%%s
set /a index=index + 1
)
echo -------------------------------------------------
set /p sel=select BIN number then press ENTRY:

set index=0
for /R %%s in (*.bin) do ( 
set /a index=index + 1
set filename=%%~ns%%~xs
if /i !index!==!sel! goto 0
)
cd .. && cls && goto BEGIN
:0
rem echo show %array_1%
echo selected %filename%
cd ../ice
start "" /b "ICEman.exe" "-b 9900" "-t 9901" "-p 9902" "-A" "-N reset-hold-script.tpl"
cd ..
mv_download_o26_v1.2.exe --image bin/%filename% --addr 0x0 --verify --port 9900

echo Run reset and run script
cd dbg\bin\
nds32le-elf-gdb.exe -x dbg_reset_and_run.txt
rem Ping 127.0.0.1 –n 5 >nul
cd ..\..
tasklist|find /i "ICEman.exe" && taskkill /f /t /im ICEman.exe

echo DONE!
pause && cls && goto BEGIN
:END