VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CSTM_Data"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Option Explicit

'==================================================================
' --------------------------     Events            ----------------
'==================================================================

Public Event ResolutionHasChanged(ByVal oldRes As Long, ByVal NewRes As Long)


'==================================================================
' ----------     Typen, Konstanten, Deklarationen      ------------
'==================================================================

Public Enum STMDataFileResult
    succeed = True
    failed = False
End Enum

Private Const copyright = "Schul-STM-Datenfile, (c) Arbeitsgruppe Prof. Fuchs, Universitaet Muenster"
'lokale Variable(n) zum Zuweisen der Eigenschaft(en)
Private Comment As String 'lokale Kopie
Private PPL As Long 'lokale Kopie
Private SS     As Long 'lokale Kopie
Private mvarData() As Single 'lokale Kopie
Private STMDataFileExt As String
Private varADInfo As CADInfo


'==================================================================
'-----------------   Konstruktor / Destruktor    ------------------
'==================================================================


Private Sub Class_Initialize()
    Set varADInfo = New CADInfo
    PPL = -1
    Comment = ""
    SS = -1
    STMDataFileExtension = ".STM"
End Sub

Private Sub Class_Terminate()
    Set varADInfo = Nothing
End Sub

'==================================================================
'-----------------          Methoden            ------------------
'==================================================================

Public Sub CopyInto(ByRef newData As CSTM_Data)
    Dim x As Long, y As Long
    If newData Is Nothing Then Set newData = New CSTM_Data
    
    newData.Resolution = Me.Resolution
    newData.SampleInfo = Me.SampleInfo
    newData.ScanSize = Me.ScanSize
    newData.STMDataFileExtension = Me.STMDataFileExtension
    
    For y = 1 To Me.Resolution
        For x = 1 To Me.Resolution
            newData.SetDataPoint x, y, Me.getDataPoint(x, y)
        Next x
        If (y Mod 20) = 0 Then DoEvents
    Next y
End Sub

Private Sub GotoEndOfFileHeader()
    Dim c As Byte
    Dim Last As Byte
    c = 0: Last = 0
    Do While Not EOF(1)
        Get #1, , c
        If Last = Asc(":") And ((c = 10) Or (c = 13)) Then Exit Do
        Last = c
    Loop
    Get #1, , c
End Sub

Private Function PutText(s As String)
    Dim i As Long
    For i = 1 To Len(s)
        Put #1, , CByte(Asc(Mid(s, i, 1)))
    Next i
    Put #1, , CByte(13)
    Put #1, , CByte(10)
End Function
Friend Function Save(ByVal path As String, Optional ByVal PathContainsFilename As Boolean = False) As STMDataFileResult
    If Not PathContainsFilename Then
        If Right(path, 1) <> "\" Then path = path + "\"
        path = path + "STM-Daten vom " & Format(Now(), "yyyy-mm-dd hh-nn-ss")
        If left(STMDataFileExt, 1) <> "." Then path = path & "."
        path = path & STMDataFileExt
    End If
    On Error GoTo SaveSTMData_Error
    
    
    Open path For Binary Access Write Lock Read Write As #1
        PutText copyright
        PutText "Resolution (in Punkten pro Zeile): " & CStr(PPL)
        PutText "ScanSize (in nm): " & CStr(SS)
        PutText "Kommentar: " & CStr(Comment)
        PutText "Maximal moegliche Eingangsspannung: " & Format(ADInfo.MaxInputVoltage, "0.0000")
        PutText "Minimal moegliche Eingangsspannung: " & Format(ADInfo.MinInputVoltage, "0.0000")
        PutText "aufgeteilt auf maximal nnn Skalenteile: " & CStr(ADInfo.MaxSkalenteile)
        PutText "Verstaerkung des OPVs:" & Format(ADInfo.OP_Gain, "0.0000")
        PutText "Jetzt folgt ein 4-Byte-Single(Float)-Array der Groesse Resolution x Resolution:"
        Put #1, , mvarData()
    Close #1

SaveSTMData_Error:
    Save = (Err.number = 0)
    On Error GoTo 0
End Function

Private Sub GetString(s As String)
    Dim b As Byte
    s = ""
    Do While Not EOF(1)
        Get #1, , b
        If b = 13 Then Exit Do
        s = s + Chr(b)
    Loop
    Get #1, , b
End Sub
Private Function ExtractInt(s As String) As Long
    s = Mid(s, InStr(1, s, ":") + 1)
    ExtractInt = CLng(s)
End Function
Private Function ExtractSng(s As String) As Single
    s = Mid(s, InStr(1, s, ":") + 1)
    s = Replace(s, ".", ",")
    ExtractSng = CSng(s)
End Function
Friend Function Load(ByVal Filename As String) As STMDataFileResult
    Dim s As String
    Dim vdata As Long
    Dim x As Long, y As Long, max As Double, min As Double
    
    On Error GoTo LoadSTMData_Error
    Open Filename For Binary Access Read Lock Read Write As #1
        GetString s
        If s <> copyright Then
            Beep
            MsgBox "Bei der Datei >>" & Filename & "<< handelt es sich um keinen korrekten Datenfile!", vbCritical + vbOKOnly
            Load = failed
            Close #1
            On Error GoTo 0
            Exit Function
        End If
        GetString s: Me.Resolution = ExtractInt(s)
        GetString s: Me.ScanSize = ExtractInt(s)
        GetString s: Me.SampleInfo = Mid(s, 12)
        GetString s: ADInfo.MaxInputVoltage = ExtractSng(s)
        GetString s: ADInfo.MinInputVoltage = ExtractSng(s)
        GetString s: ADInfo.MaxSkalenteile = ExtractInt(s)
        GetString s: ADInfo.OP_Gain = ExtractSng(s)
        GetString s:
        Get #1, , mvarData()
    Close #1

    max = -100000: min = 100000
    For y = 1 To PPL
        For x = 1 To PPL
            If max < mvarData(x, y) Then max = mvarData(x, y)
            If min > mvarData(x, y) Then min = mvarData(x, y)
    Next x, y
    max = CSng(CInt(max * (1 + Sgn(max) * 0.2) + 0.5))
    min = CSng(CInt(min * (1 - Sgn(min) * 0.2) - 0.5))
    ADInfo.MaxInputVoltage = max '* (1 + Sgn(max) * 0.2)
    ADInfo.MinInputVoltage = min '* (1 - Sgn(min) * 0.2)

LoadSTMData_Error:
    Load = (Err.number = 0)
    On Error GoTo 0
End Function


Friend Sub SetDataPoint(ByVal x As Long, ByVal y As Long, ByVal signal As Single)
    mvarData(x, y) = signal
End Sub
Friend Function getDataPoint(ByVal x As Long, ByVal y As Long) As Single
    getDataPoint = mvarData(x, y)
End Function

'==================================================================
' -------------------------   Properties   ------------------------
'==================================================================


Friend Property Let STMDataFileExtension(ByVal vdata As String)
    STMDataFileExt = vdata
End Property
Friend Property Get STMDataFileExtension() As String
    STMDataFileExtension = STMDataFileExt
End Property




Friend Property Let ScanSize(ByVal nm As Long)
    SS = nm
End Property
Friend Property Get ScanSize() As Long
    ScanSize = SS
End Property



Friend Property Let Resolution(ByVal PixelPerLine As Long)
    If PixelPerLine = PPL Then Exit Property
    RaiseEvent ResolutionHasChanged(PPL, PixelPerLine)
    PPL = PixelPerLine
    ReDim mvarData(1 To PixelPerLine, 1 To PixelPerLine)
End Property
Friend Property Get Resolution() As Long
    Resolution = PPL
End Property



Friend Property Let SampleInfo(ByVal vdata As String)
    Comment = vdata
End Property
Friend Property Get SampleInfo() As String
    SampleInfo = Comment
End Property




Friend Property Set ADInfo(new_ADInfo As CADInfo)
    Set ADInfo = new_ADInfo
End Property
Friend Property Get ADInfo() As CADInfo
    Set ADInfo = varADInfo
End Property

