@echo off
setlocal enabledelayedexpansion

:: Define the directory to store test files
set "test_dir=C:\Users\salla\OneDrive\Desktop\Operating-Systems\Task 6\Test_dir"
mkdir "%test_dir%" 2>nul

:: Create files from 0 KB to 50 KB
for /L %%i in (0,1,50) do (
    set "filename=%test_dir%\file_%%iKB.txt"
    fsutil file createnew "!filename!" %%i000 >nul
)

echo Test files created successfully!
endlocal
