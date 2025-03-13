@echo off
setlocal enabledelayedexpansion

:: Get the current directory and create Test_dir inside it
set "test_dir=%CD%\Test_dir"
mkdir "%test_dir%" 2>nul

:: Create files from 0 KB to 50 KB
for /L %%i in (0,1,50) do (
    set "filename=%test_dir%\file_%%iKB.txt"
    fsutil file createnew "!filename!" %%i000 >nul
)

echo Test files created successfully in: %test_dir%
endlocal
