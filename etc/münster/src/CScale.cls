VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CScale"
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

Public Event ScaleHasChanged(ByVal AbsMin As Single, ByVal min As Single, ByVal max As Single, ByVal AbsMax As Single)
Public Event ColormapChanged()


'==================================================================
' ----------     Typen, Konstanten, Deklarationen      ------------
'==================================================================


'lokale Variable(n) zum Zuweisen der Eigenschaft(en)

Private AbsScaleMin As Single
Private AbsScaleMax As Single
Private ScaleMin As Single
Private ScaleMax As Single
Private mvarColormap(0 To 255) As Long 'lokale Kopie
Private ScaleFactor As Double
Private varADInfo As CADInfo

'==================================================================
'-----------------   Konstruktor / Destruktor    ------------------
'==================================================================


Private Sub Class_Initialize()
    Set ADInfo = New CADInfo
    
    AbsScaleMax = ADInfo.MaxInputVoltage
    AbsScaleMin = ADInfo.MinInputVoltage
    ScaleMin = AbsScaleMin
    ScaleMax = AbsScaleMax
    CalcScaleFactor
    
    SetDefaultColormap
End Sub

Private Sub Class_Terminate()
    Set ADInfo = Nothing
End Sub


Friend Sub ResetScale()
    ScaleMin = AbsScaleMin
    ScaleMax = AbsScaleMax
    CalcScaleFactor
    RaiseEvent ScaleHasChanged(AbsScaleMin, ScaleMin, ScaleMax, AbsScaleMax)
End Sub


Private Sub CalcScaleFactor()
    ScaleFactor = (ScaleMax - ScaleMin) / 255
End Sub


Friend Sub DrawScale(ByVal left As Long, ByVal top As Long, ByVal width As Long, ByVal window As Form)
Dim i As Long
    For i = 0 To 255
        window.Line (left, top + 255 - i)-(left + width, top + 255 - i), mvarColormap(i)
    Next i
End Sub


Friend Property Set ADInfo(ByVal new_ADInfo As CADInfo)
    Set varADInfo = new_ADInfo
    If Not (varADInfo Is Nothing) Then
        AbsScaleMax = varADInfo.MaxInputVoltage
        AbsScaleMin = varADInfo.MinInputVoltage
        ScaleMax = varADInfo.MaxInputVoltage
        ScaleMin = varADInfo.MinInputVoltage
    End If
End Property
Friend Property Get ADInfo() As CADInfo
    Set ADInfo = varADInfo
End Property





' ===============================================================
' --------------------  Absolute  Scale Values ------------------
' ===============================================================


Friend Property Let AbsoluteMaximumValue(ByVal vdata As Single)
    AbsScaleMax = vdata
End Property
Friend Property Get AbsoluteMaximumValue() As Single
    AbsoluteMaximumValue = AbsScaleMax
End Property


Friend Property Let AbsoluteMinimumValue(ByVal vdata As Single)
    AbsScaleMin = vdata
End Property
Friend Property Get AbsoluteMinimumValue() As Single
    AbsoluteMinimumValue = AbsScaleMin
End Property


Friend Sub SetAbsScaleValues(ByVal AbsMinValue As Single, ByVal AbsMaxValue As Single)
    If AbsMinValue > AbsMaxValue Then Exit Sub
    If AbsMinValue > ScaleMin Then ScaleMin = AbsMinValue
    If AbsScaleMax < ScaleMax Then ScaleMax = AbsMaxValue
    If (AbsMinValue = AbsScaleMin) And (AbsMaxValue = AbsScaleMax) Then Exit Sub
    AbsScaleMin = AbsMinValue
    AbsScaleMax = AbsMaxValue
    CalcScaleFactor
    RaiseEvent ScaleHasChanged(AbsScaleMin, ScaleMin, ScaleMax, AbsScaleMax)
End Sub

' ===============================================================
' --------------------    Scale Values      ---------------------
' ===============================================================

Friend Sub SetAllScaleValues(ByVal AbsMin As Single, ByVal min As Single, ByVal max As Single, ByVal AbsMax As Single)
    If ((AbsMin > min) Or (min > max) Or (max > AbsMax)) Then Exit Sub
    AbsScaleMin = AbsMin
    ScaleMin = min
    ScaleMax = max
    AbsScaleMax = AbsMax
    CalcScaleFactor
    RaiseEvent ScaleHasChanged(AbsScaleMin, ScaleMin, ScaleMax, AbsScaleMax)
End Sub



Friend Property Get ScaleMinLabel() As String
    ScaleMinLabel = Format(ScaleMin, "0.00 "" nA""")
End Property

Friend Property Let ScaleMinValue(ByVal vdata As Single)
    If vdata >= ScaleMax Then Exit Property
    If vdata = ScaleMin Then Exit Property
    ScaleMin = vdata
    CalcScaleFactor
    RaiseEvent ScaleHasChanged(AbsScaleMin, ScaleMin, ScaleMax, AbsScaleMax)
End Property

Friend Property Get ScaleMinValue() As Single
    ScaleMinValue = ScaleMin
End Property



Friend Property Get ScaleMaxLabel() As String
    ScaleMaxLabel = Format(ScaleMax, "0.00 "" nA""")
End Property

Friend Property Let ScaleMaxValue(ByVal vdata As Single)
    If vdata <= ScaleMin Then Exit Property
    If vdata = ScaleMax Then Exit Property
    ScaleMax = vdata
    CalcScaleFactor
    RaiseEvent ScaleHasChanged(AbsScaleMin, ScaleMin, ScaleMax, AbsScaleMax)
End Property
Friend Property Get ScaleMaxValue() As Single
    ScaleMaxValue = ScaleMax
End Property


Friend Sub SetScaleValues(ByVal MinValue As Single, ByVal MaxValue As Single)
    If MinValue > MaxValue Then Exit Sub
    If MinValue < AbsScaleMin Then AbsScaleMin = MinValue
    If MaxValue > AbsScaleMax Then AbsScaleMax = MaxValue
    If (MinValue = ScaleMin) And (MaxValue = ScaleMax) Then Exit Sub
    ScaleMin = MinValue
    ScaleMax = MaxValue
    CalcScaleFactor
    RaiseEvent ScaleHasChanged(AbsScaleMin, ScaleMin, ScaleMax, AbsScaleMax)
End Sub



' ======================================================
' -----------------------     ColorMap     -------------
' ======================================================

Friend Sub SetDefaultColormap()
    Dim i As Long, c As Long
    Dim r As Integer, g As Integer, b As Integer
    Dim LB As Long, UB As Long, DiffB As Long
    LB = LBound(mvarColormap)
    UB = UBound(mvarColormap)
    DiffB = UB - LB
    For i = LB To UB
        c = CInt((i - LB) / DiffB * 255)
        mvarColormap(i) = RGB(c, c, c)
        'r = CInt((c Mod 8) / 8 * 255)
        'g = CInt((c Mod 32) / 32 * 255)
        'b = CInt((c \ 64) * 64)
        'mvarColormap(i) = RGB(r, c, b)
    Next i
End Sub

Friend Function GetColor(ByVal vdata As Single) As Long
    Dim i As Integer
    i = CInt((vdata - ScaleMin) / ScaleFactor)
    If i < LBound(mvarColormap) Then i = LBound(mvarColormap)
    If i > UBound(mvarColormap) Then i = UBound(mvarColormap)
    GetColor = mvarColormap(i)
End Function

