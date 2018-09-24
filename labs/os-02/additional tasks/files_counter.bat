@echo off
set /a txt_count = 0
set /a bat_count = 0
set /a doc_count = 0
for %%i in (*.*) do  (
if "%%~xi"==".txt" set /a txt_count += 1
if "%%~xi"==".bat" set /a bat_count += 1
if "%%~xi"==".doc" set /a doc_count += 1
)
echo .txt files: %txt_count%
echo .bat files: %bat_count%
echo .doc files: %doc_count%
pause