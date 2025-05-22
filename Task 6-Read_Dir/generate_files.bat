@echo off
setlocal enabledelayedexpansion

:: Get the directory where the script is located
set "script_dir=%~dp0"
set "test_dir=%script_dir%Test_dir"

:: Create the Test_dir folder
mkdir "%test_dir%" 2>nul

:: Create files from 0 KB to 50 KB
for /L %%i in (0,1,50) do (
    set "filename=%test_dir%\file_%%iKB.txt"
    fsutil file createnew "!filename!" %%i000 >nul
)

echo Test files created successfully in: %test_dir%
endlocal
