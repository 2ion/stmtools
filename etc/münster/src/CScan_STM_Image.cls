VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CScan_STM_Image"
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

Public Event ScanSizeHasChanged()
Public Event ResolutionHasChanged(ByVal oldRes As Long, ByVal NewRes As Long)
Public Event DataSaved()
Public Event NewScanVelocity(ByVal t As Double)

'==================================================================
' ----------     Typen, Konstanten, Deklarationen      ------------
'==================================================================

Private bildnr As Integer

Public Enum ScanDirectionConstants
    None = 0
    LeftToRight = 1
    RightToLeft = 2
    BothDirections = 3
End Enum

Public Enum SaveDataConstants
    SaveNone = 0
    SaveNext = 1
    SaveThis = 2
End Enum


'lokale Variable(n) zum Zuweisen der Eigenschaft(en)
Private mvarScanDirection As ScanDirectionConstants 'lokale Kopie
Private mvarFitScaleToFirstLine As Boolean 'lokale Kopie
Private mvarDatafilePath As String 'lokale Kopie
Private mvarsavedata As SaveDataConstants 'lokale Kopie
Private ScanInProgress As Boolean
Private AbortScan As Boolean
Private mvarSecondsPerLine As Double
Private mvarDelayAfterPixel As Long ' in millisekunden

Private WithEvents STMTip As CSTM_Tip
Attribute STMTip.VB_VarHelpID = -1
Private WithEvents STMData As CSTM_Data
Attribute STMData.VB_VarHelpID = -1
Private WithEvents STMImage As CSTM_Image
Attribute STMImage.VB_VarHelpID = -1
Private LineScan As CLineScan
Attribute LineScan.VB_VarHelpID = -1
Private StopUhr As CStopUhr


'==================================================================
'-----------------   Konstruktor / Destruktor    ------------------
'==================================================================

Private Sub Class_Initialize()
    Set STMData = New CSTM_Data
    Set STMImage = New CSTM_Image
    Set LineScan = New CLineScan
    Set STMTip = New CSTM_Tip
    Set StopUhr = New CStopUhr
    
    ScanInProgress = False
    bildnr = 0
    refresh_ADInfo
    
    Set LineScan.ImageScale = STMImage.ImageScale
    STMImage.UserCanUnload = False
    ScanDirection = LeftToRight
    FitScaleToFirstLine = False
    DatafilePath = "c:\"
    
    Resolution = 128
    ScanSize = 400
    XOffset = 0
    YOffset = 0
    mvarDelayAfterPixel = -32000
    mvarSecondsPerLine = 1
End Sub

Private Sub Class_Terminate()
    StopScan
    Set STMData = Nothing
    Set STMImage = Nothing
    Set LineScan = Nothing
    Set STMTip = Nothing
End Sub



'==================================================================
' -------------------------   Properties   ------------------------
'==================================================================

Friend Property Let ScanAngle(ByVal degree As Single)
    STMTip.ScanAngle = degree
End Property
Friend Property Get ScanAngle() As Single
    ScanAngle = STMTip.ScanAngle
End Property


Friend Property Let LogarithmSignal(ByVal vdata As Boolean)
    STMTip.Logarithm = vdata
End Property



Friend Property Get LinesPerSecond() As Double
    LinesPerSecond = 1 / mvarSecondsPerLine
End Property


Friend Property Let DelayAfterPixel(ByVal milliseconds As Long)
    mvarDelayAfterPixel = milliseconds
End Property
Friend Property Get DelayAfterPixel() As Long
    DelayAfterPixel = mvarDelayAfterPixel
End Property



Friend Property Get Tip() As CSTM_Tip
    Set Tip = STMTip
End Property

Friend Property Let DatafilePath(ByVal path As String)
    mvarDatafilePath = path
End Property
Friend Property Get DatafilePath() As String
    DatafilePath = mvarDatafilePath
End Property




Friend Property Let FitScaleToFirstLine(ByVal vdata As Boolean)
    mvarFitScaleToFirstLine = vdata
End Property
Friend Property Get FitScaleToFirstLine() As Boolean
    FitScaleToFirstLine = mvarFitScaleToFirstLine
End Property



Friend Property Let ScanDirection(ByVal vdata As ScanDirectionConstants)
    mvarScanDirection = vdata
End Property
Friend Property Get ScanDirection() As ScanDirectionConstants
    ScanDirection = mvarScanDirection
End Property



Friend Property Let Resolution(ByVal PixelPerLine As Long)
    STMData.Resolution = 512 'PixelPerLine
    STMImage.Resolution = PixelPerLine
    LineScan.Resolution = PixelPerLine
    STMTip.Resolution = 512 'PixelPerLine
    If STMImage.Visible Then
        STMImage.Show
        STMImage.RedrawScale
    End If
    If LineScan.Visible Then
        LineScan.Hide
        LineScan.Show
    End If
End Property
Friend Property Get Resolution() As Long
    Resolution = STMData.Resolution
End Property



Friend Property Let SampleInfo(ByVal text As String)
    STMData.SampleInfo = text
    STMImage.SampleInfo = text
End Property
Friend Property Get SampleInfo() As String
    SampleInfo = STMData.SampleInfo
End Property


Friend Property Let XOffset(ByVal nm As Long)
    STMTip.XOffset = nm
End Property
Friend Property Get XOffset() As Long
    XOffset = STMTip.XOffset
End Property



Friend Property Let YOffset(ByVal nm As Long)
    STMTip.YOffset = nm
End Property
Friend Property Get YOffset() As Long
    YOffset = STMTip.YOffset
End Property



Friend Property Let ScanSize(ByVal nm As Long)
    STMData.ScanSize = nm
    STMImage.ScanSize = nm
    LineScan.ScanSize = nm
    STMTip.ScanSize = nm
End Property
Friend Property Get ScanSize() As Long
    ScanSize = STMData.ScanSize
End Property



Friend Property Let ImageVisible(ByVal vdata As Boolean)
    STMImage.Visible = vdata
End Property
Friend Property Get ImageVisible() As Boolean
    ImageVisible = STMImage.Visible
End Property



Friend Property Let LineScanVisible(ByVal vdata As Boolean)
    LineScan.Visible = vdata
End Property
Friend Property Get LineScanVisible() As Boolean
    LineScanVisible = LineScan.Visible
End Property



Friend Property Let SaveData(ByVal vdata As SaveDataConstants)
    mvarsavedata = vdata
End Property
Friend Property Get SaveData() As SaveDataConstants
    SaveData = mvarsavedata
End Property





' ==========================================================
' -----------------    METHODEN    -----------------------
' ==========================================================


Private Sub refresh_ADInfo()
    STMData.ADInfo.GetInfoFromSTMTip STMTip
    STMData.ADInfo.OP_Gain = CSng(Main.OPV_Gain)
    Set STMImage.ADInfo = STMData.ADInfo
    Set LineScan.ADInfo = STMData.ADInfo
    STMImage.ImageScale.ResetScale
End Sub


Friend Sub ShowImage()
    STMImage.Show
End Sub

Friend Sub HideImage()
    StopScan
    STMImage.Hide
End Sub

Friend Sub ShowLineScan()
    LineScan.Show
End Sub

Friend Sub HideLineScan()
    LineScan.Hide
End Sub


Friend Sub HideAll()
    LineScan.Hide
    STMImage.Hide
End Sub

Friend Sub SaveSTMData()
    STMData.Save mvarDatafilePath
    RaiseEvent DataSaved
End Sub

Friend Sub StopScan()
    AbortScan = True
End Sub


Friend Sub StartScan(Optional ByVal Direction As ScanDirectionConstants = None)
    If ScanInProgress Then Exit Sub
    
    If Direction = None Then Direction = Me.ScanDirection
    AbortScan = False
    ScanInProgress = True
    
    STMTip.MoveHome
    While Not AbortScan
        StopUhr.Start
        If (mvarScanDirection And 1) <> 0 Then
            Scan_LR
            STMTip.NextLine
        Else
            STMTip.MoveToLastCol
        End If
        If (mvarScanDirection And 2) <> 0 Then
            Scan_RL
            STMTip.NextLine
        Else
            STMTip.MoveToFirstCol
        End If
        StopUhr.Stopp
        mvarSecondsPerLine = StopUhr.TimeElapsed / 2
        RaiseEvent NewScanVelocity(mvarSecondsPerLine)
        DoEvents
    Wend
    DoEvents
    STMTip.MoveHome
    ScanInProgress = False
End Sub



Private Sub FitScaleToLine(ByVal y As Long, Optional ByVal PercentOfScale As Single = 100)
    Dim x As Long
    Dim max As Single, min As Single
    Dim delta As Single
    
    If PercentOfScale > 1 Then PercentOfScale = PercentOfScale / 100
    max = -100000#: min = 200000#
    For x = 1 To STMData.Resolution
        If max < STMData.getDataPoint(x, y) Then
            max = STMData.getDataPoint(x, y)
        ElseIf min > STMData.getDataPoint(x, y) Then
            min = STMData.getDataPoint(x, y)
        End If
    Next x

    delta = (max - min) * (0.5 - PercentOfScale / 2) ' = ( (1-PercentOfSCale)/2)*(Max-MIn)
    STMImage.ImageScale.SetScaleValues (min - delta), (max + delta)
End Sub




Private Sub ProcessCurrentSignal(Optional signal As Single = -234)
Dim i As Single, d As Integer
    d = STMData.Resolution \ STMImage.Resolution
    If signal = -234 Then
        i = STMTip.getSignal
    Else
        i = signal
    End If
    STMData.SetDataPoint STMTip.x, STMTip.y, i
    If ((STMTip.x Mod d) = 0) And ((STMTip.y Mod d) = 0) Then
        STMImage.DrawPoint STMTip.x \ d, STMTip.y \ d, i
        If LineScan.Visible Then LineScan.DrawPoint STMTip.x \ d, STMTip.y \ d, i
    End If
End Sub


Private Sub Scan_LR()
On Error Resume Next
    Dim x As Long
    Dim delay As Long
    For x = 1 To STMData.Resolution
        For delay = -32000 To mvarDelayAfterPixel: Next delay
        STMTip.x = x
        If Err.number = 0 Then
            ProcessCurrentSignal
        Else
            ProcessCurrentSignal 0
        End If
    Next
On Error GoTo 0
End Sub
Private Sub Scan_RL()
On Error Resume Next
    Dim x As Long
    Dim delay As Long
    For x = STMData.Resolution To 1 Step -1
        For delay = -32000 To mvarDelayAfterPixel: Next delay
        STMTip.x = x
        If Err.number = 0 Then
            ProcessCurrentSignal
        Else
            ProcessCurrentSignal 0
        End If
    Next
On Error GoTo 0
End Sub



' ==========================================================
' -----------------    EVENT Handling   -----------------------
' ==========================================================




Private Sub STMData_ResolutionHasChanged(ByVal oldRes As Long, ByVal NewRes As Long)
    RaiseEvent ResolutionHasChanged(oldRes, NewRes)
'    STMImage.Resolution = NewRes
'    LineScan.Resolution = NewRes
'    STMTip.Resolution = NewRes
End Sub


Private Sub STMTip_FrameBorderReached(position As CSTFBR)
    If mvarsavedata = SaveThis Then
        bildnr = bildnr + 1
        'If bildnr = 20 Then
            SaveSTMData
            bildnr = 0
        'End If
    End If
    If mvarsavedata = SaveNext Then SaveData = SaveThis
    If mvarFitScaleToFirstLine Then
        FitScaleToLine STMTip.y, 0.85
    Else
        STMImage.ImageScale.ResetScale
    End If
End Sub

Private Sub STMTip_TipPropertiesChanged()
    refresh_ADInfo
End Sub
