VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CStopUhr"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private Type SYSTEMTIME
        wYear As Integer
        wMonth As Integer
        wDayOfWeek As Integer
        wDay As Integer
        wHour As Integer
        wMinute As Integer
        wSecond As Integer
        wMilliseconds As Integer
End Type

Private startTime As SYSTEMTIME, stopTime As SYSTEMTIME


Private Declare Sub GetSystemTime Lib "kernel32" (lpSystemTime As SYSTEMTIME)




Friend Sub Start()
    GetSystemTime startTime
End Sub

Friend Sub Stopp()
    GetSystemTime stopTime
End Sub


Private Function SystemTime2Seconds(ST As SYSTEMTIME) As Double
    Dim sec As Double
    With ST
        sec = .wHour * 60
        sec = (sec + .wMinute) * 60
        sec = sec + .wSecond + .wMilliseconds / 1000
    End With
    SystemTime2Seconds = sec
End Function
Friend Property Get TimeElapsed() As Double
    Dim s1 As Double, s2 As Double
    s1 = SystemTime2Seconds(startTime)
    s2 = SystemTime2Seconds(stopTime)
    TimeElapsed = (s2 - s1)
End Property



