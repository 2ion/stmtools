VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CSTM_Tip"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Option Explicit



Public Enum CSTFBR
    top = 1
    Bottom = 2
End Enum



Public Event FrameBorderReached(position As CSTFBR)
Public Event TipPropertiesChanged()


'lokale Variable(n) zum Zuweisen der Eigenschaft(en)
Private mvarX As Long 'lokale Kopie
Private mvarY As Long 'lokale Kopie
Private PPL As Long 'lokale Kopie
Private Angle As Single
Private LineInc As Long
Private vFirstLineInFrame As Boolean 'lokale Kopie
Private SS As Long
Private dX As Long
Private dY As Long
Private LogSignal As Boolean
Private mvarMinInputVoltage As Double


#If ME300 Then
    '----------------------- fuer ME300 - AD/DA-Karte von Meilhaus
    Private WithEvents IOCard As CME300
Attribute IOCard.VB_VarHelpID = -1
    'Private WithEvents IOCard As CRandom
    Const INChannel = ME300InChan1
#End If
#If PC20TR Then
    ' ----------------------- fuer PC20TR - AD/DA-Karte von BMC
    Private WithEvents IOCard As CPC20TR
Attribute IOCard.VB_VarHelpID = -1
    Const INChannel = PC20TR_InChan1
#End If




Private Function Ln(ByVal signal As Double) As Double
    If mvarMinInputVoltage > signal Then signal = mvarMinInputVoltage
    Ln = Log(signal - mvarMinInputVoltage + 1)
End Function


' ******************************************************************************
' ****************************    PROPETIES        *****************************
' ******************************************************************************

Friend Property Let ScanAngle(ByVal degree As Single)
    Angle = degree / 180 * 3.14159265
End Property
Friend Property Get ScanAngle() As Single
    ScanAngle = Angle * 180 / 3.14159265
End Property



Friend Property Let Logarithm(ByVal vdata As Boolean)
    If LogSignal = vdata Then Exit Property
    LogSignal = vdata
    RaiseEvent TipPropertiesChanged
End Property
Friend Property Get Logarithm() As Boolean
    Logarithm = LogSignal
End Property



Friend Sub SetInputVoltageRange(ByVal v As Single)
#If ME300 Then
    v = Abs(v)
    If v <= 1.25 Then
        IOKarte.SetInputChannelRange INChannel, AI_MINUS_1
    ElseIf (v <= 2.5) Then
        IOKarte.SetInputChannelRange INChannel, AI_MINUS_2
    ElseIf (v <= 5) Then
        IOKarte.SetInputChannelRange INChannel, AI_MINUS_5
    Else
        IOKarte.SetInputChannelRange INChannel, AI_MINUS_10
    End If
#End If
#If PC20TR Then
    v = Abs(v)
    If v <= 1 Then
        IOKarte.SetInputChannelRange INChannel, AI_MINUS_1
    ElseIf (v <= 2) Then
        IOKarte.SetInputChannelRange INChannel, AI_MINUS_2
    ElseIf (v <= 5) Then
        IOKarte.SetInputChannelRange INChannel, AI_MINUS_5
    Else
        IOKarte.SetInputChannelRange INChannel, AI_MINUS_10
    End If
#End If
End Sub

Friend Property Get MaxInputVoltage() As Single
    If LogSignal Then
        MaxInputVoltage = Ln(IOCard.MaxInputVoltage(INChannel))
    Else
        MaxInputVoltage = IOCard.MaxInputVoltage(INChannel)
    End If
End Property
Friend Property Get MinInputVoltage() As Single
    mvarMinInputVoltage = IOCard.MinInputVoltage(INChannel)
    If LogSignal Then
        MinInputVoltage = Ln(mvarMinInputVoltage)
    Else
        MinInputVoltage = mvarMinInputVoltage
    End If
End Property
Friend Property Get MinOutputVoltage() As Single
    #If ME300 Then
        MinOutputVoltage = IOCard.MinOutputVoltage(ME300OutChan1)
    #End If
    #If PC20TR Then
        MinOutputVoltage = IOCard.MinOutputVoltage(PC20TR_OutChan1)
    #End If
End Property
Friend Property Get MaxOutputVoltage() As Single
    #If ME300 Then
        MaxOutputVoltage = IOCard.MaxOutputVoltage(ME300OutChan1)
    #End If
    #If PC20TR Then
        MaxOutputVoltage = IOCard.MaxOutputVoltage(PC20TR_OutChan1)
    #End If
End Property
Friend Property Get MaxSkalenteile() As Long
    MaxSkalenteile = IOCard.MaxSkalenteile
End Property



Friend Property Let XOffset(ByVal nm As Long)
    dX = nm
End Property
Friend Property Get XOffset() As Long
    XOffset = dX
End Property


Friend Property Let YOffset(ByVal nm As Long)
    dY = nm
End Property
Friend Property Get YOffset() As Long
    YOffset = dY
End Property


Friend Property Let ScanSize(ByVal nm As Long)
    SS = nm
End Property
Friend Property Get ScanSize() As Long
    ScanSize = SS
End Property


Friend Property Let Resolution(ByVal PixelPerLine As Long)
    PPL = PixelPerLine
End Property
Friend Property Get Resolution() As Long
    Resolution = PPL
End Property



Friend Property Let y(ByVal PixelInLine As Long)
    If PixelInLine < 1 Then PixelInLine = 1
    If PixelInLine > PPL Then PixelInLine = PPL
    mvarY = PixelInLine
    SetTip
End Property
Friend Property Get y() As Long
    y = mvarY
End Property



Friend Property Let x(ByVal PixelInLine As Long)
    If PixelInLine < 1 Then PixelInLine = 1
    If PixelInLine > PPL Then PixelInLine = PPL
    mvarX = PixelInLine
    SetTip
End Property
Friend Property Get x() As Long
    x = mvarX
End Property



Friend Property Get wasFirstLineInFrame() As Boolean
    wasFirstLineInFrame = vFirstLineInFrame
End Property



' ******************************************************************************
' ****************************    KONSTRUKTOR       *****************************
' ******************************************************************************


Private Sub Class_Initialize()
    
    LogSignal = False
    
#If ME300 Then
    '----------------------- fuer ME300 - AD/DA-Karte
    Set IOCard = New CME300
    IOCard.InitCard ME300Card1
    IOCard.SetOutputChannelRange ME300OutChan1, AO_MINUS_10
    IOCard.SetOutputChannelRange ME300OutChan2, AO_MINUS_10
    IOCard.SetInputChannelRange INChannel, AI_MINUS_10
#End If
#If PC20TR Then
    '----------------------- fuer ME300 - AD/DA-Karte
    Set IOCard = New CPC20TR
    IOCard.InitCard PC20TR_Card1
    IOCard.SetOutputChannelRange PC20TR_OutChan1, AO_MINUS_10
    IOCard.SetOutputChannelRange PC20TR_OutChan2, AO_MINUS_10
    IOCard.SetInputChannelRange INChannel, AI_MINUS_10
#End If

    mvarX = 1
    mvarY = 1
    XOffset = 0
    YOffset = 0
    PPL = 128
    LineInc = 1
    vFirstLineInFrame = False


End Sub

Private Sub Class_Terminate()
    Set IOCard = Nothing
End Sub


' ******************************************************************************
' ****************************    METHODEN         *****************************
' ******************************************************************************

#If ME300 Then
    Friend Property Get IOKarte() As CME300
       Set IOKarte = IOCard
    End Property
#End If
#If PC20TR Then
    Friend Property Get IOKarte() As CPC20TR
       Set IOKarte = IOCard
    End Property
#End If

Friend Sub SetXYOffset(ByVal deltaX As Long, ByVal deltaY As Long)
    XOffset = deltaX 'nm
    YOffset = deltaY 'nm
End Sub

Friend Sub setXY(ByVal Xvalue As Long, ByVal Yvalue As Long)
    Me.x = Xvalue
    Me.y = Yvalue
End Sub



Friend Sub NextLine()
    If (LineInc = 1) And (mvarY = Resolution) Then
        RaiseEvent FrameBorderReached(Bottom)
        vFirstLineInFrame = True
        LineInc = -1
        Exit Sub
    End If
    If (LineInc = -1) And (mvarY = 1) Then
        RaiseEvent FrameBorderReached(top)
        vFirstLineInFrame = True
        LineInc = 1
        Exit Sub
    End If
    vFirstLineInFrame = False
    Me.y = Me.y + LineInc
End Sub

Friend Sub MoveHome()
    setXY 1, 1
End Sub


Friend Sub MoveToFirstCol()
    Do Until Me.x = 1
        Me.x = Me.x - 1
    Loop
End Sub


Friend Sub MoveToLastCol()
    Do Until Me.x = Me.Resolution
        Me.x = Me.x + 1
    Loop
End Sub


Friend Function getSignal() As Single
    If LogSignal Then
        getSignal = Ln(getI())
    Else
        getSignal = getI()
    End If
End Function




' -----------------------------------------------------------------------------------
' ---------------------------    INTERFACE   DATA   AQUISITION    -------------------
' -----------------------------------------------------------------------------------


Private Sub SetTip()
On Error Resume Next

    Dim PPL_2 As Single
    Dim xc As Single, yc As Single
    Dim xr As Single, yr As Single
    Dim sa As Single, ca As Single
    
    PPL_2 = PPL / 2
    sa = Sin(Angle): ca = Cos(Angle) ' calculate Sin and Cos
    xc = x - PPL_2: yc = y - PPL_2 ' translate Coord from Left/Top to FrameCenter
    xr = xc * ca - yc * sa: yr = xc * sa + yc * ca ' Rotate
    xr = xr + PPL_2: yr = yr + PPL_2 ' translate Coord from FrameCenter to Left/Top
    
    xr = (xr - 1) / (PPL - 1) * ScanSize: yr = (yr - 1) / (PPL - 1) * ScanSize ' Convert from pixel to nm
    xr = xr + XOffset: yr = yr + YOffset ' Move to Offset.
     
    xr = xr / MaxScanSize * (MaxOutputVoltage - MinOutputVoltage) + MinOutputVoltage ' Convert from nm 2 Voltage
    yr = yr / MaxScanSize * (MaxOutputVoltage - MinOutputVoltage) + MinOutputVoltage
    

    
#If ME300 Then
    '----------------------- fuer ME300 - AD/DA-Karte
    If xr > IOCard.MaxOutputVoltage(ME300OutChan1) Then xr = IOCard.MaxOutputVoltage(ME300OutChan1)
    If yr > IOCard.MaxOutputVoltage(ME300OutChan2) Then yr = IOCard.MaxOutputVoltage(ME300OutChan2)
    If xr < IOCard.MinOutputVoltage(ME300OutChan1) Then xr = IOCard.MinOutputVoltage(ME300OutChan1)
    If yr < IOCard.MinOutputVoltage(ME300OutChan2) Then yr = IOCard.MinOutputVoltage(ME300OutChan2)
    
    IOCard.AnalogOutput ME300OutChan1, xr
    IOCard.AnalogOutput ME300OutChan2, yr
#End If
#If PC20TR Then
    '----------------------- fuer PC20TR - AD/DA-Karte
    If xr > IOCard.MaxOutputVoltage(PC20TR_OutChan1) Then xr = IOCard.MaxOutputVoltage(PC20TR_OutChan1)
    If yr > IOCard.MaxOutputVoltage(PC20TR_OutChan2) Then yr = IOCard.MaxOutputVoltage(PC20TR_OutChan2)
    If xr < IOCard.MinOutputVoltage(PC20TR_OutChan1) Then xr = IOCard.MinOutputVoltage(PC20TR_OutChan1)
    If yr < IOCard.MinOutputVoltage(PC20TR_OutChan2) Then yr = IOCard.MinOutputVoltage(PC20TR_OutChan2)
    
    IOCard.AnalogOutput PC20TR_OutChan1, xr
    IOCard.AnalogOutput PC20TR_OutChan2, yr
#End If
    
On Error GoTo 0
End Sub


Private Function getI() As Single
    getI = IOCard.AnalogInput(INChannel)
End Function





' ************************************************************
' ******************    EVENTS HANDLING         **************
' ************************************************************

#If ME300 Then
    Private Sub IOCard_AnalogInputRangeChanged(ByVal ChannelNr As ME300InChannelNumbers, ByVal fromRange As ME300AnalogInputRanges, ByVal toRange As ME300AnalogInputRanges)
        mvarMinInputVoltage = IOCard.MinInputVoltage(INChannel)
        RaiseEvent TipPropertiesChanged
    End Sub
#End If
#If PC20TR Then
    Private Sub IOCard_AnalogInputRangeChanged(ByVal ChannelNr As PC20TR_InChannelNumbers, ByVal fromRange As PC20TR_AnalogInputRanges, ByVal toRange As PC20TR_AnalogInputRanges)
        mvarMinInputVoltage = IOCard.MinInputVoltage(INChannel)
        RaiseEvent TipPropertiesChanged
    End Sub
#End If
