Option Explicit
Dim FSO, Batch, path, WshShell
Set FSO = CreateObject("Scripting.FileSystemObject")
Set Batch = FSO.OpenTextFile("..\ex4.bat", 2, True)
Batch.Write "start excel.exe"
Batch.Close
Set WshShell = CreateObject("WScript.Shell")
WshShell.Run "..\ex4.bat", 1, True