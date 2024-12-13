@echo off
set PATH=%cd%/dll;%SystemRoot%\system32;%SystemRoot%;%SystemRoot%\System32\Wbem;%PATH%
tasklist|find /i "ICEman.exe" && taskkill /f /t /im ICEman.exe
cd ice
start "" /b "ICEman.exe" "-b 9900" "-t 9901" "-p 9902" "-A" "-N reset-hold-script.tpl"
cd ..

echo Run reset and run script
cd dbg\bin\
nds32le-elf-gdb.exe -x dbg_reset_and_run.txt
rem Ping 127.0.0.1 –n 5 >nul
cd ..\..
tasklist|find /i "ICEman.exe" && taskkill /f /t /im ICEman.exe

echo DONE!
pause && cls && goto BEGIN
:END