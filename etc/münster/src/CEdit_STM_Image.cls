VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CEdit_STM_Image"
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

Public Event DataManipulationStarted(ByVal typ As DataManipulationMethods)
Public Event DataManipulationProgress(ByVal typ As DataManipulationMethods, ByVal Percent As Single)
Public Event DataManipulationFinished(ByVal typ As DataManipulationMethods)
Public Event ScaleHasChanged(ByVal AbsMin As Single, ByVal min As Single, ByVal max As Single, ByVal AbsMax As Single)

'==================================================================
' ----------     Typen, Konstanten, Deklarationen      ------------
'==================================================================


Public Enum DataManipulationMethods
    DMM_None = 0
    DMM_OptimizeScale = 1
    DMM_FlattenData = 2
    DMM_SmoothData = 3
    DMM_LnData = 4
    DMM_SubstLine = 5
End Enum




'lokale Variable(n) zum Zuweisen der Eigenschaft(en)
Private WithEvents STMData As CSTM_Data
Attribute STMData.VB_VarHelpID = -1
Private WithEvents STMImage As CSTM_Image
Attribute STMImage.VB_VarHelpID = -1
Private LineScan As CLineScan

Private mvarFilename As String 'lokale Kopie
Private STMFilesDir As String
Private Cdlg As CommonDialog


'==================================================================
'-----------------   Konstruktor / Destruktor    ------------------
'==================================================================


Private Sub Class_Initialize()
    Set STMImage = New CSTM_Image
    STMImage.AutoRedraw = True
    
    Set STMData = New CSTM_Data
    STMData.STMDataFileExtension = FileExt
    
    Set LineScan = New CLineScan
    Set Cdlg = Nothing
End Sub

Private Sub Class_Terminate()
    Set STMImage = Nothing
    Set STMData = Nothing
    Set LineScan = Nothing
    Set Cdlg = Nothing
End Sub


'==================================================================
' -------------------------   Properties   ------------------------
'==================================================================

Friend Property Get ADInfo() As CADInfo
    Set ADInfo = STMData.ADInfo
End Property


Friend Property Set CommonDialogControl(ByVal vdata As CommonDialog)
    Set Cdlg = vdata
End Property
Friend Property Get CommonDialogControl() As CommonDialog
    Set CommonDialogControl = Cdlg
End Property


Friend Property Let Resolution(ByVal PPL As Long)
    STMImage.Resolution = PPL
End Property
Friend Property Get Resolution() As Long
    Resolution = STMImage.Resolution
End Property


Friend Property Get MaxResolution() As Long
    MaxResolution = STMData.Resolution
End Property


Friend Property Let STMFilesDirectory(path As String)
    STMFilesDir = path
End Property
Friend Property Get STMFilesDirectory() As String
    STMFilesDirectory = STMFilesDir
End Property



Friend Property Get Visible() As Boolean
    Visible = STMImage.Visible
End Property


Friend Property Get SampleInfo() As String
    SampleInfo = STMImage.SampleInfo
End Property


Friend Property Let Filename(ByVal vdata As String)
    mvarFilename = vdata
End Property
Friend Property Get Filename() As String
    Filename = mvarFilename
End Property


Friend Property Set ImageScale(ByVal vdata As CScale)
    Set STMImage.ImageScale = vdata
End Property
Friend Property Get ImageScale() As CScale
    Set ImageScale = STMImage.ImageScale
End Property


'=========================================================================
'-------------------   Manipulations - METHODEN   ------------------------
'=========================================================================


Friend Sub ExecuteDataManipulation(typ As DataManipulationMethods, Optional ByVal PercentOfScale As Single = 100)
    Select Case typ
        Case DMM_None: Exit Sub
        Case DMM_OptimizeScale: OptimizeScale PercentOfScale
        Case DMM_FlattenData: FlattenData PercentOfScale
        Case DMM_SmoothData: SmoothData
        Case DMM_LnData: LnData PercentOfScale
        Case DMM_SubstLine: SubtractLine PercentOfScale
    End Select
End Sub

Friend Sub ResetScale()
    STMImage.ImageScale.ResetScale
End Sub

Friend Sub OptimizeScale(Optional ByVal PercentOfScale As Single = 100)
    Dim x As Long, y As Long
    Dim max As Single, min As Single
    Dim factor As Long, dscale As Single
    
    If PercentOfScale > 1 Then PercentOfScale = PercentOfScale / 100
    
    RaiseEvent DataManipulationStarted(DMM_OptimizeScale)
    DoEvents
    
    max = -100000#: min = 100000#
    factor = STMData.Resolution \ 5
    For y = 1 To STMData.Resolution
        For x = 1 To STMData.Resolution
            If max < STMData.getDataPoint(x, y) Then
                max = STMData.getDataPoint(x, y)
            ElseIf min > STMData.getDataPoint(x, y) Then
                min = STMData.getDataPoint(x, y)
            End If
        Next x
        If (y Mod factor) = 0 Then
            RaiseEvent DataManipulationProgress(DMM_OptimizeScale, y / STMData.Resolution)
            DoEvents
        End If
    Next y
        
    dscale = (max - min) * (0.5 - PercentOfScale / 2) ' = ( (1-PercentOfSCale)/2)*(Max-MIn)
    ImageScale.SetScaleValues (min - dscale), (max + dscale)
    RaiseEvent DataManipulationFinished(DMM_OptimizeScale)
    DoEvents
End Sub


Friend Sub SubtractLine(Optional ByVal PercentOfScale As Single = 100)
    Dim x As Long, y As Long
    Dim max As Single, min As Single
    Dim a As Single, b As Single
    Dim factor As Single, newvalue As Single
    Dim xarr() As Single, yarr() As Single
    Dim PPL As Long
    
    RaiseEvent DataManipulationStarted(DMM_SubstLine)
    DoEvents
    
    If PercentOfScale > 1 Then PercentOfScale = PercentOfScale / 100
    
    PPL = STMData.Resolution
    ReDim xarr(1 To PPL)
    ReDim yarr(1 To PPL)
    
    For x = 1 To PPL
        xarr(x) = x
    Next x
    
    factor = PPL \ 5
    max = -10000: min = 10000
    For y = 1 To PPL
        'copy array
        For x = 1 To PPL
            yarr(x) = STMData.getDataPoint(x, y)
        Next x
        'Lineare Regression a+x*b fuer zeile y
        Call MathModul.Fit(xarr(), yarr(), a, b)
        'Call MathModul.MedFit(xarr(), yarr(), a, b)
        'neuen Wert errechnen und setzen
        For x = 1 To PPL
            newvalue = yarr(x) - (a + x * b)
            STMData.SetDataPoint x, y, newvalue
            If max < newvalue Then max = newvalue
            If min > newvalue Then min = newvalue
        Next x
        If (y Mod factor) = 0 Then
            RaiseEvent DataManipulationProgress(DMM_SubstLine, y / PPL)
            DoEvents
        End If
    Next y
    
    factor = (max - min) * (0.5 - PercentOfScale / 2) ' = ( (1-PercentOfSCale)/2)*(Max-MIn)
    ImageScale.SetScaleValues (min - factor), (max + factor)
    RaiseEvent DataManipulationFinished(DMM_SubstLine)
    DoEvents
End Sub



Friend Sub FlattenData(Optional ByVal PercentOfScale As Single = 100)
    Dim x, y As Long
    Dim ay() As Single, by() As Single, ax As Single, bx As Single
    Dim xarr() As Single, yarr() As Single
    Dim max As Single, min As Single, newvalue As Single
    Dim factor As Single, PPL As Long
    
    RaiseEvent DataManipulationStarted(DMM_FlattenData)
    DoEvents
    
    PPL = STMData.Resolution
    If PercentOfScale > 1 Then PercentOfScale = PercentOfScale / 100
    ReDim xarr(1 To PPL), yarr(1 To PPL), ay(1 To PPL), by(1 To PPL)
    
    For x = 1 To PPL
        xarr(x) = x
    Next x
    factor = STMData.Resolution \ 5
    max = -10000: min = 10000
    
    For x = 1 To PPL
        For y = 1 To PPL
            yarr(y) = STMData.getDataPoint(x, y)
        Next y
        'Lineare Regression a+x*b fuer Spalte x
        Call MathModul.Fit(xarr(), yarr(), ay(x), by(x))
        If (x Mod factor) = 0 Then
            RaiseEvent DataManipulationProgress(DMM_FlattenData, x / PPL / 2)
            DoEvents
        End If
    Next x
    For y = 1 To PPL
        'copy array
        For x = 1 To PPL
            yarr(x) = STMData.getDataPoint(x, y)
        Next x
        'Lineare Regression a+x*b fuer zeile y
        Call MathModul.Fit(xarr(), yarr(), ax, bx)
        'neuen Wert errechnen und setzen
        For x = 1 To PPL
            newvalue = yarr(x) - (ax + x * bx) - (ay(y) + y * by(y))
            STMData.SetDataPoint x, y, newvalue
            If max < newvalue Then max = newvalue
            If min > newvalue Then min = newvalue
        Next x
        If (y Mod factor) = 0 Then
            RaiseEvent DataManipulationProgress(DMM_FlattenData, y / PPL / 2 + 0.5)
            DoEvents
        End If
    Next y
    
    factor = (max - min) * (0.5 - PercentOfScale / 2) ' = ( (1-PercentOfSCale)/2)*(Max-MIn)
    ImageScale.SetScaleValues (min - factor), (max + factor)
    RaiseEvent DataManipulationFinished(DMM_FlattenData)
    DoEvents
End Sub

Friend Sub SmoothData()
    Dim newData As CSTM_Data
    Dim x As Long, y As Long
    Dim factor As Single
    Dim signal As Double
    
    RaiseEvent DataManipulationStarted(DMM_SmoothData)
    DoEvents
    
    Set newData = New CSTM_Data
    STMData.CopyInto newData
    
    factor = STMData.Resolution \ 5
    For y = 2 To STMData.Resolution - 1
        For x = 2 To STMData.Resolution - 1
            signal = 12 * STMData.getDataPoint(x, y)
            signal = signal + 2 * (STMData.getDataPoint(x + 1, y) + STMData.getDataPoint(x - 1, y) + STMData.getDataPoint(x, y - 1) + STMData.getDataPoint(x, y + 1))
            signal = signal + 1 * (STMData.getDataPoint(x + 1, y + 1) + STMData.getDataPoint(x + 1, y - 1) + STMData.getDataPoint(x - 1, y - 1) + STMData.getDataPoint(x - 1, y + 1))
            newData.SetDataPoint x, y, CSng(signal / 24)
        Next x
        If (y Mod factor) = 0 Then
            RaiseEvent DataManipulationProgress(DMM_SmoothData, y / STMData.Resolution)
            DoEvents
        End If
    Next y
    
    newData.CopyInto STMData
    Set newData = Nothing
    
    RaiseEvent DataManipulationFinished(DMM_SmoothData)
    DoEvents
End Sub

Public Function LnData(Optional ByVal PercentOfScale As Single = 100)
    Dim x As Long, y As Long
    Dim factor As Single, fp As Single
    Dim max As Double, min As Double
    Dim d As Double
    
    RaiseEvent DataManipulationStarted(DMM_LnData)
    DoEvents
    
    If PercentOfScale > 1 Then PercentOfScale = PercentOfScale / 100
    
    factor = STMData.Resolution / 10
    max = -10000: min = 10000
    For y = 1 To STMData.Resolution
        For x = 1 To STMData.Resolution
            d = STMData.getDataPoint(x, y)
            If max < d Then max = d
            If min > d Then min = d
        Next x
        If (y Mod factor) = 0 Then
            RaiseEvent DataManipulationProgress(DMM_LnData, y / STMData.Resolution / 2)
            DoEvents
        End If
    Next y
    
    fp = (max - min) * (0.5 - PercentOfScale / 2) ' = ( (1-PercentOfSCale)/2)*(Max-MIn)
    min = min - fp: max = max + fp
    If min <= 0 Then d = min - 1 Else d = 0
    
    For y = 1 To STMData.Resolution
        For x = 1 To STMData.Resolution
            STMData.SetDataPoint x, y, Log(STMData.getDataPoint(x, y) - d)
        Next x
        If (y Mod factor) = 0 Then
            RaiseEvent DataManipulationProgress(DMM_LnData, 0.5 + y / STMData.Resolution / 2)
            DoEvents
        End If
    Next y

    ImageScale.SetAllScaleValues Log(min - d), Log(min - d), Log(max - d), Log(max - d)

    RaiseEvent DataManipulationFinished(DMM_LnData)
    DoEvents
End Function

' *************************************************************************
' *******************          METHODEN           *************************
' *************************************************************************


Friend Sub Hide()
    STMImage.Hide
End Sub

Friend Sub Show()
    Dim x As Long, y As Long
    Dim c As Long, d As Long
    Dim i As Integer
    
    c = STMImage.Resolution \ 10
    d = STMData.Resolution \ STMImage.Resolution
    
    STMImage.Show
    STMImage.RedrawScale
    
    For y = 1 To STMImage.Resolution
        For x = 1 To STMImage.Resolution
            STMImage.DrawPoint x, y, STMData.getDataPoint(x * d, y * d)
           ' For i = 1 To 1000
           ' Next i
        Next x
        If y Mod c Then DoEvents
    Next y
    
End Sub


Friend Sub ShowLineScanZeile(ByVal Line As Long)
    Dim x As Long
    Set LineScan.ADInfo = STMData.ADInfo
    Set LineScan.ImageScale = STMImage.ImageScale
    LineScan.Resolution = STMData.Resolution
    LineScan.ScanSize = STMData.ScanSize
    LineScan.Show
    For x = 1 To LineScan.Resolution
        LineScan.DrawPoint x, Line, STMData.getDataPoint(x, Line)
    Next x
End Sub
Friend Sub ShowLineScanSpalte(ByVal Line As Long)
    Dim y As Long
    Set LineScan.ADInfo = STMData.ADInfo
    Set LineScan.ImageScale = STMImage.ImageScale
    LineScan.Resolution = STMData.Resolution
    LineScan.ScanSize = STMData.ScanSize
    LineScan.Show
    For y = 1 To LineScan.Resolution
        LineScan.DrawPoint y, Line, STMData.getDataPoint(Line, y)
    Next y
End Sub

Friend Sub HideLineScan()
    LineScan.Hide
End Sub


'==================================================================
' --------------------------     File - Operationen
'==================================================================




Private Function AskForFilename(ByVal Extension As String, ByVal Filter As String) As String
    Cdlg.CancelError = True
    Cdlg.Flags = cdlOFNExplorer + cdlOFNCreatePrompt + cdlOFNHideReadOnly + cdlOFNLongNames
    Cdlg.DefaultExt = Extension
    Cdlg.Filter = Filter
    Cdlg.InitDir = STMFilesDir
    On Error Resume Next
    Cdlg.ShowSave
    If Err.number <> 0 Then Cdlg.Filename = ""
    AskForFilename = Cdlg.Filename
End Function

Friend Sub SaveBMPImage(Optional ByVal Fname As String = "")
    If Fname = "" Then Fname = AskForFilename(".BMP", "WindowsBitMap (*.BMP)|*.BMP")
    If Fname = "" Then Exit Sub

    SavePicture STMImage.Image, Fname
End Sub

Friend Sub SaveSTMData(Optional ByVal Fname As String = "")
    If Fname = "" Then Fname = AskForFilename(STMData.STMDataFileExtension, "STM-Datendatei (*" & STMData.STMDataFileExtension & ")|" & "*" & STMData.STMDataFileExtension)
    If Fname = "" Then Exit Sub
    
    If STMData.Save(Fname, True) = succeed Then
        Me.Filename = Fname
    End If
End Sub


Friend Sub LoadSTMData(Optional ByVal Fname As String = "")
    If Fname = "" Then Fname = Me.Filename
    If Fname = "" Then Exit Sub
    If STMData.Load(Fname) = succeed Then
        Me.Filename = Fname
        Set STMImage.ADInfo = STMData.ADInfo
        'STMImage.Resolution = STMData.Resolution
        STMImage.ScanSize = STMData.ScanSize
        STMImage.SampleInfo = STMData.SampleInfo
    End If
End Sub

Friend Sub ReloadData()
    If Me.Filename <> "" Then
        LoadSTMData Me.Filename
        STMImage.ImageScale.ResetScale
    End If
End Sub



' ***********************************************************************************
' ****************************     EVENT - HANDLING    ******************************
' ***********************************************************************************



Private Sub STMImage_ScaleHasChanged(ByVal AbsMin As Single, ByVal min As Single, ByVal max As Single, ByVal AbsMax As Single)
    If Me.Visible Then Me.Show
    RaiseEvent ScaleHasChanged(AbsMin, min, max, AbsMax)
End Sub
