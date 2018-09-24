Set fso = CreateObject("Scripting.FileSystemObject")
Set WshShell = CreateObject ("WScript.Shell")
Set objEnv = WshShell.Environment("User")
objEnv("MyVar") = "xcopy ..\files\file1.txt ..\files\file3.txt"
WshShell.Run objEnv("MyVar")