Set objExcel = CreateObject("Excel.Application") 
Set objWorkBook = objExcel.Workbooks.Open("D:\temp\1.xlsx") 
objExcel.Cells(1, 1).Value = 7
objExcel.ActiveWorkbook.Save
objExcel.Quit 
Set oShell = WScript.CreateObject("WScript.Shell")
oShell.Run "cmd"
WScript.Sleep 1000
oShell.SendKeys "start excel.exe D:\temp\1.xlsx"  & vbCr