Set WshShell = CreateObject ("WScript.Shell")
Set objEnv = WshShell.Environment("User")
objEnv("MyVar") = "notepad.exe ..\files\file2"
WshShell.Run objEnv("MyVar")