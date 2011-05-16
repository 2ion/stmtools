VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CME300"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
#If ME300 Then
' **********************************************************************************
' ****************      PUBLIC DEFINITIONS       ***********
' **********************************************************************************

Public Enum ME300CardNumbers
    ME300NoCard = -1
    ME300Card1 = 0
    ME300Card2 = 1
    ME300Card3 = 2
    ME300Card4 = 3
End Enum
Public Enum ME300OutChannelNumbers
    ME300NoOutChannel = -1
    ME300OutChan1 = 0
    ME300OutChan2 = 1
    ME300OutChan3 = 2
    ME300OutChan4 = 3
End Enum
Public Enum ME300InChannelNumbers
    ME300NoInChannel = -1
    ME300InChan1 = 0
    ME300InChan2 = 1
    ME300InChan3 = 2
    ME300InChan4 = 3
    ME300InChan5 = 4
    ME300InChan6 = 5
    ME300InChan7 = 6
    ME300InChan8 = 7
    ME300InChan9 = 8
    ME300InChan10 = 9
    ME300InChan11 = 10
    ME300InChan12 = 11
    ME300InChan13 = 12
    ME300InChan14 = 13
    ME300InChan15 = 14
    ME300InChan16 = 15
End Enum

Public Enum ME300Class_Errors
    ME300CardInitFailed = 2001
    ME300SignalWrong = 2002
End Enum
    
Public Enum ME300BitNumber
    ME300Bit0 = 0
    ME300Bit1 = 1
    ME300Bit2 = 2
    ME300Bit3 = 3
    ME300Bit4 = 4
    ME300Bit5 = 5
    ME300Bit6 = 6
    ME300Bit7 = 7
End Enum

' **********************************************************************************
' ****************      LOCAL VARIABLES       ***********
' **********************************************************************************


Dim BoardNr As ME300CardNumbers
Dim AORanges(0 To 3) As ME300AnalogOutputRanges
Dim AIRanges(0 To 15) As ME300AnalogInputRanges



' **********************************************************************************
' **********************************************************************************
' **********************************************************************************
' ****************      ME300ILHAUS - DEFINITIONEN       ***********
' **********************************************************************************
' **********************************************************************************
' **********************************************************************************



Public Enum ME300PortConstants
    PORTA = 0
    PORTB = 1
    PORTC = 2
    PORTCL = 3
    PORTCH = 4
    PORTD = 8
    PORTE = 9
    PORTF = 10
    PORTFL = 11
    PORTFH = 12
End Enum
Public Enum ME300Directions
    ME300input = 0
    ME300OUTPUT = 1
End Enum
Public Enum ME300GeneralConstants
    IN32 = 0
    OUT32 = 1
    IN16 = 2
    OUT16 = 3
    INOUT16 = 4
End Enum
' ME300-260/260D/300 Register Set '
        '8-Bit Register'
Public Enum ME3008BitRegisterConstants
     ME300_FID = &H0    'R'
     ME300_ADSTART = &H0        'W'
     ME300_STATUS = &H1 'R'
     ME300_CONTROL1 = &H1       'W'
     ME300_RESETINT = &H2       'R'
     ME300_CONTROL2 = &H2       'W'
     ME300_KANALLISTE = &H3
     ME300_TIME300R0DATA = &H4
     ME300_TIME300R1DATA = &H5
     ME300_TIME300R2DATA = &H6
     ME300_TIME300RCONTROL = &H7
     ME300_DIGITAL_A = &H8
     ME300_DIGITAL_B = &H9
     ME300_DIGITAL_C = &HA
End Enum
        '16-Bit register'
Public Enum ME30016BitRegisterConstants
     ME300_FIFO = &H10
     ME300_DA_CONTROL = &H14
     ME300_DA_DATA_A = &H18
     ME300_DA_DATA_B = &H1A
     ME300_DA_DATA_C = &H1C
     ME300_DA_DATA_D = &H1E
End Enum

' Analog Input Ranges for ME300-300 '
Public Enum ME300AnalogInputRanges
     AI_NORange = -1
     AI_DYNAMIC = -2
     AI_MINUS_10 = &H0
     AI_MINUS_5 = &H10
     AI_MINUS_2 = &H20
     AI_MINUS_1 = &H30
     AI_PLUS_10 = &H40
     AI_PLUS_5 = &H50
     AI_PLUS_2 = &H60
     AI_PLUS_1 = &H70
End Enum
' Trigger Modes for ME300-300 '
Public Enum ME300AnalogInputTriggerModes
    AI300_TRIGGER_TIME300R = &H2
    AI300_TRIGGER_EXT_LOW = &H3
    AI300_TRIGGER_EXT_HIGH = &H13
End Enum

' Scan Modes '
Public Enum ME300ScanModes
    SCAN_SINGLE = &H1
    SCAN_INFINITE = &H2
    SCAN_STREAME300R = &H10
End Enum

' Data Buffer Access '
Public Enum ME300DataBufferAccess
    FILE_BEGIN = &H0
    FILE_CURRENT = &H1
    FILE_END = &H2
End Enum

'Analog Output Ranges '
Public Enum ME300AnalogOutputRanges
    AO_NORange = -1
    AO_DYNAMIC = -2
    AO_PLUS_10 = &H0
    AO_MINUS_5 = &H1
    'AO_PLUS_5 = &H2
    AO_MINUS_10 = &H3
End Enum


'File ME300.bas'
'Include File for 32-bit Driver DLL ME300_32.dll'

Rem Das Modul "ME300.bas" ermöglicht Ihnen, die DLL "ME300_32.dll" zu benutzen.

Private Declare Function ME300GetDLLVersion Lib "ME300_32.dll" Alias "_VBme300GetDLLVersion@0" () As Long
Private Declare Function ME300GetDrvErrMess Lib "ME300_32.dll" Alias "_VBme300GetDrvErrMess@4" (ByVal cErrorlist As String) As Long
Private Declare Function ME300PROMVersion Lib "ME300_32.dll" Alias "_VBme300PROMVersion@8" (ByVal iBoardNumber As Long, ByRef iVersion As Long) As Long
Private Declare Function ME300MakeChannelList Lib "ME300_32.dll" Alias "_VBme300MakeChannelList@4" (iChannelList As Long) As Long

Private Declare Function ME300DIOSetPortDirection Lib "ME300_32.dll" Alias "_VBme300DIOSetPortDirection@12" (ByVal iBoardNumber As Long, ByVal iPortNo As Long, ByVal iDir As Long) As Long

Private Declare Function ME300DIGetBit Lib "ME300_32.dll" Alias "_VBme300DIGetBit@16" (ByVal iBoardNumber As Long, ByVal iPortNo As Long, ByVal iBitNo As Long, ByRef iBitValue As Long) As Long
Private Declare Function ME300DIGetByte Lib "ME300_32.dll" Alias "_VBme300DIGetByte@12" (ByVal iBoardNumber As Long, ByVal iPortNo As Long, ByRef iValue As Long) As Long

Private Declare Function ME300DOSetBit Lib "ME300_32.dll" Alias "_VBme300DOSetBit@16" (ByVal BoardNumber As Long, ByVal iPortNo As Long, ByVal iBitNo As Long, ByVal BitValue As Long) As Long
Private Declare Function ME300DOSetByte Lib "ME300_32.dll" Alias "_VBme300DOSetByte@12" (ByVal BoardNumber As Long, ByVal iPortNo As Long, ByVal iValue As Long) As Long

Private Declare Function ME300AISetTrigger Lib "ME300_32.dll" Alias "_VBme300AISetTrigger@8" (ByVal iBoardNumber As Long, ByVal iModePolarity As Long) As Long
Private Declare Function ME300AISetTimer Lib "ME300_32.dll" Alias "_VBme300AISetTimer@16" (ByVal iBoardNumber As Long, ByVal iScan0 As Long, ByVal iScan1 As Long, ByVal iChan As Long) As Long
Private Declare Function ME300AISetChannelList Lib "ME300_32.dll" Alias "_VBme300AISetChannelList@8" (ByVal iBoardNumber As Long, iChannelList As Long) As Long
Private Declare Function ME300AISingle Lib "ME300_32.dll" Alias "_VBme300AISingle@16" (ByVal iBoardNumber As Long, ByVal iChannelNo As Long, ByVal iRange As Long, sValue As Integer) As Long
Private Declare Function ME300AIScan Lib "ME300_32.dll" Alias "_VBme300AIScan@12" (ByVal iBoardNumber As Long, ByRef iNumberOfSamples As Long, sArray As Integer) As Long

Private Declare Function ME300AIScanStartEx Lib "ME300_32.dll" Alias "_VBme300AIScanStartEx@12" (ByVal iBoardNumber As Long, ByVal iMode As Long, ByVal iNumberOfScans As Long) As Long
Private Declare Function ME300AIScanStop Lib "ME300_32.dll" Alias "_VBme300AIScanStop@4" (ByVal iBoardNumber As Long) As Long
Private Declare Function ME300AIReadBuffer Lib "ME300_32.dll" Alias "_VBme300AIReadBuffer@12" (ByVal iBoardNumber As Long, ByRef piNumberOfScans As Long, psArray As Integer) As Long
Private Declare Function ME300SetThreadPriority Lib "ME300_32.dll" Alias "_VBme300SetThreadPriority@6" (ByVal iBoardNumber As Long, ByVal sPriority As Integer) As Long

Private Declare Function ME300AOSingle Lib "ME300_32.dll" Alias "_VBme300AOSingle@16" (ByVal iBoardNumber As Long, ByVal iChannelNo As Long, ByVal iRange As Long, ByVal sValue As Integer) As Long
Private Declare Function ME300AOResetAll Lib "ME300_32.dll" Alias "_VBme300AOResetAll@4" (ByVal iBoardNumber As Long) As Long



' **********************************************************************************
' **********************************************************************************
' **********************************************************************************
' ****************      MEILHAUS - DEFINITIONEN     ENDE  **************************
' **********************************************************************************
' **********************************************************************************
' **********************************************************************************









' **********************************************************************************
' ****************       PUBLIC EVENTS        ***********
' **********************************************************************************

Public Event InitFailed()
Public Event AnalogInputRangeChanged(ByVal ChannelNr As ME300InChannelNumbers, ByVal fromRange As ME300AnalogInputRanges, ByVal toRange As ME300AnalogInputRanges)
Public Event AnalogOutputRangeChanged(ByVal ChannelNr As ME300OutChannelNumbers, ByVal fromRange As ME300AnalogOutputRanges, ByVal toRange As ME300AnalogOutputRanges)


' **********************************************************************************
' ****************      PROPERTIES         ****************
' **********************************************************************************


Public Property Let BoardNumber(ByVal nr As ME300CardNumbers)
    BoardNr = nr
End Property
Public Property Get BoardNumber() As ME300CardNumbers
    BoardNumber = BoardNr
End Property

Public Function MaxInputVoltage(ByVal ch As ME300InChannelNumbers) As Single
    Select Case AIRanges(ch)
        Case AI_MINUS_10: MaxInputVoltage = 10
        Case AI_MINUS_5: MaxInputVoltage = 5
        Case AI_MINUS_2: MaxInputVoltage = 2.5
        Case AI_MINUS_1: MaxInputVoltage = 1.25
        Case AI_PLUS_10: MaxInputVoltage = 10
        Case AI_PLUS_5: MaxInputVoltage = 5
        Case AI_PLUS_2: MaxInputVoltage = 2.5
        Case AI_PLUS_1: MaxInputVoltage = 1.25
    End Select
End Function
Public Function MinInputVoltage(ByVal ch As ME300InChannelNumbers) As Single
    Select Case AIRanges(ch)
        Case AI_MINUS_10: MinInputVoltage = -10
        Case AI_MINUS_5: MinInputVoltage = -5
        Case AI_MINUS_2: MinInputVoltage = -2.5
        Case AI_MINUS_1: MinInputVoltage = -1.25
        Case AI_PLUS_10: MinInputVoltage = 0
        Case AI_PLUS_5: MinInputVoltage = 0
        Case AI_PLUS_2: MinInputVoltage = 0
        Case AI_PLUS_1: MinInputVoltage = 0
    End Select
End Function

Public Function MaxOutputVoltage(ByVal ch As ME300OutChannelNumbers) As Single
    Select Case AORanges(ch)
        Case AO_MINUS_10: MaxOutputVoltage = 10
        Case AO_MINUS_5: MaxOutputVoltage = 5
        'Case AO_MINUS_2: MaxOutputVoltage = 2.5
        'Case AO_MINUS_1: MaxOutputVoltage = 1.25
        Case AO_PLUS_10: MaxOutputVoltage = 10
        'Case AO_PLUS_5: MaxOutputVoltage = 5
        'Case AO_PLUS_2: MaxOutputVoltage = 2.5
        'Case AO_PLUS_1: MaxOutputVoltage = 1.25
    End Select
End Function
Public Function MinOutputVoltage(ByVal ch As ME300OutChannelNumbers) As Single
    Select Case AORanges(ch)
        Case AO_MINUS_10: MinOutputVoltage = -10
        Case AO_MINUS_5: MinOutputVoltage = -5
        'Case AO_MINUS_2: MinOutputVoltage = -2.5
        'Case AO_MINUS_1: MinOutputVoltage = -1.25
        Case AO_PLUS_10: MinOutputVoltage = 0
        'Case AO_PLUS_5: MinOutputVoltage = 0
        'Case AO_PLUS_2: MinOutputVoltage = 0
        'Case AO_PLUS_1: MinOutputVoltage = 0
    End Select
End Function
Public Property Get MaxSkalenteile() As Long
    MaxSkalenteile = &HFFF&
End Property


' **********************************************************************************
' ****************      KLASSEN   -   ME300THODEN     ****************
' **********************************************************************************

Private Sub Class_Initialize()
    Dim ch As Integer
    BoardNumber = ME300NoCard
    
    For ch = 0 To 3
        AORanges(ch) = AO_MINUS_10
    Next ch
    For ch = 0 To 15
        AIRanges(ch) = AI_MINUS_10
    Next ch
End Sub

Private Sub Class_Terminate()
    InitCard
End Sub



' **********************************************************************************
' ****************      METHODEN         ****************
' **********************************************************************************

Public Sub InitCard(Optional ByVal nr As ME300CardNumbers = ME300NoCard)
    Dim version As Long
    
    If nr <> ME300NoCard Then BoardNr = nr
    If BoardNr = ME300NoCard Then
        RaiseEvent InitFailed
        Err.Raise vbObjectError + ME300CardInitFailed
        Exit Sub
    End If
    
    If ME300PROMVersion(BoardNr, version) = 0 Then
        Err.Raise vbObjectError + ME300CardInitFailed
        Exit Sub
    End If
    If version <> &H39 Then
        Err.Raise vbObjectError + ME300CardInitFailed, ""
        Exit Sub
    End If
    If ME300AOResetAll(BoardNr) = 0 Then
        Err.Raise vbObjectError + ME300CardInitFailed
        Exit Sub
    End If
End Sub

Public Sub SetInputChannelRange(ByVal ChannelNr As ME300InChannelNumbers, ByVal range As ME300AnalogInputRanges)
    Dim OldRange As ME300AnalogInputRanges
    If AIRanges(ChannelNr) = range Then Exit Sub
    OldRange = AIRanges(ChannelNr)
    AIRanges(ChannelNr) = range
    RaiseEvent AnalogInputRangeChanged(ChannelNr, OldRange, range)
End Sub
Public Function GetInputChannelRange(ByVal ChannelNr As ME300InChannelNumbers) As ME300AnalogInputRanges
    GetInputChannelRange = AIRanges(ChannelNr)
End Function

Public Sub SetOutputChannelRange(ByVal ChannelNr As ME300OutChannelNumbers, ByVal range As ME300AnalogOutputRanges)
    Dim OldRange As ME300AnalogOutputRanges
    If AORanges(ChannelNr) = range Then Exit Sub
    OldRange = AORanges(ChannelNr)
    AORanges(ChannelNr) = range
    RaiseEvent AnalogOutputRangeChanged(ChannelNr, OldRange, range)
End Sub
Public Function GetOutputChannelRange(ByVal ChannelNr As ME300OutChannelNumbers) As ME300AnalogOutputRanges
    GetOutputChannelRange = AORanges(ChannelNr)
End Function

' **********************************************************************************

Private Function ConvertOutSignal(ByVal signal As Single, ByVal OutRange As ME300AnalogOutputRanges) As Integer
    ConvertOutSignal = -1
    
    Select Case OutRange
        Case AO_PLUS_10
            If (signal >= 0) Or (signal <= 10) Then
                ConvertOutSignal = CInt(signal / 10 * &HFFF)
            End If
        Case AO_MINUS_5
            If (signal >= -5) Or (signal <= 5) Then
                ConvertOutSignal = CInt((signal + 5) / 10 * &HFFF)
            End If
        Case AO_MINUS_10
            If (signal >= -10) Or (signal <= 10) Then
                ConvertOutSignal = CInt((signal + 10) / 20 * &HFFF)
            End If
    End Select
End Function

Public Sub AnalogOutput(ByVal channel As ME300OutChannelNumbers, ByVal signal As Single, Optional ByVal OutputRange As ME300AnalogOutputRanges = AO_NORange)
    Dim value As Integer
    
    If OutputRange = AO_NORange Then OutputRange = AORanges(channel)
    If OutputRange = AO_DYNAMIC Then
        If signal > 0 Then OutputRange = AO_PLUS_10
        If signal <= 0 Then OutputRange = AO_MINUS_5
        If signal < -5 Then OutputRange = AO_MINUS_10
    End If
    
    value = ConvertOutSignal(signal, OutputRange)
    If value < 0 Then value = 0
    If value >= 0 Then
        ME300AOSingle BoardNr, channel, OutputRange, value
    Else
        Err.Raise vbObjectError + ME300SignalWrong
    End If
End Sub
Public Sub DirectAnalogOutput(ByVal channel As ME300OutChannelNumbers, ByVal value As Long, Optional ByVal OutputRange As ME300AnalogOutputRanges = AO_NORange)
    If OutputRange = AO_NORange Then OutputRange = AORanges(channel)
    
    'If value < 0 Then value = 0
    'If value > &HFFF Then value = &HFFF
    If (value >= 0) And (value <= &HFFF) Then
        ME300AOSingle BoardNr, channel, OutputRange, value
    Else
        Err.Raise vbObjectError + ME300SignalWrong
    End If
End Sub


' **********************************************************************************

Public Function ConvertInSignal(ByVal value As Integer, ByVal InputRange As ME300AnalogInputRanges) As Single
    Select Case InputRange
        Case AI_MINUS_10
            ConvertInSignal = ((value / &HFFF * 20) - 10)
        Case AI_MINUS_5
            ConvertInSignal = ((value / &HFFF * 10) - 5)
        Case AI_MINUS_2
            ConvertInSignal = ((value / &HFFF * 5) - 2.5)
        Case AI_MINUS_1
            ConvertInSignal = ((value / &HFFF * 2.5) - 1.25)
        Case AI_PLUS_10
            ConvertInSignal = ((value / &HFFF * 10))
        Case AI_PLUS_5
            ConvertInSignal = ((value / &HFFF * 5))
        Case AI_PLUS_2
            ConvertInSignal = ((value / &HFFF * 2.5))
        Case AI_PLUS_1
            ConvertInSignal = ((value / &HFFF * 1.25))
    End Select
End Function
Public Function AnalogInput(ByVal channel As ME300InChannelNumbers, Optional ByVal InputRange As ME300AnalogInputRanges = AI_NORange) As Single
    Dim value As Integer
    
    If InputRange = AI_NORange Then InputRange = AIRanges(channel)
    If InputRange = AI_DYNAMIC Then
        ME300AISingle BoardNr, channel, AI_MINUS_10, value
        Select Case ConvertInSignal(value, AI_MINUS_10)
            Case Is < -5: InputRange = AI_MINUS_10
            Case Is < -2.5: InputRange = AI_MINUS_5
            Case Is < -1.2: InputRange = AI_MINUS_2
            Case Is <= 0: InputRange = AI_MINUS_1
            Case Is > 0: InputRange = AI_PLUS_1
            Case Is > 1.2: InputRange = AI_PLUS_2
            Case Is > 2.5: InputRange = AI_PLUS_5
            Case Is > 5: InputRange = AI_PLUS_10
        End Select
    End If
    ME300AISingle BoardNr, channel, InputRange, value
    AnalogInput = ConvertInSignal(value, InputRange)
End Function
Public Function DirectAnalogInput(ByVal channel As ME300InChannelNumbers, Optional ByVal InputRange As ME300AnalogInputRanges = AI_NORange) As Integer
    Dim value As Integer
    
    If InputRange = AI_NORange Then InputRange = AIRanges(channel)
    
    ME300AISingle BoardNr, channel, InputRange, value
    DirectAnalogInput = value
End Function


' **********************************************************************************

Public Sub FillComboBox(cb As ComboBox, IODirection As ME300Directions, Optional ByVal DynamicAllowed As Boolean = False)
    cb.Clear
    If IODirection = ME300input Then
        cb.AddItem "+10 V", 0: cb.ItemData(0) = AI_PLUS_10
        cb.AddItem "+ 5 V", 1: cb.ItemData(1) = AI_PLUS_5
        cb.AddItem "+ 2.5 V", 2: cb.ItemData(2) = AI_PLUS_2
        cb.AddItem "+ 1.25 V", 3: cb.ItemData(3) = AI_PLUS_1
        cb.AddItem "±10 V", 4: cb.ItemData(4) = AI_MINUS_10
        cb.AddItem "± 5 V", 5: cb.ItemData(5) = AI_MINUS_5
        cb.AddItem "± 2.5 V", 6: cb.ItemData(6) = AI_MINUS_2
        cb.AddItem "± 1.25 V", 7: cb.ItemData(7) = AI_MINUS_1
        If DynamicAllowed Then cb.AddItem "dynamic", 8: cb.ItemData(8) = AI_DYNAMIC
    Else
        cb.AddItem "+10 V", 0: cb.ItemData(0) = AO_PLUS_10
        cb.AddItem "±10 V", 1: cb.ItemData(1) = AO_MINUS_10
        cb.AddItem " ±5 V", 2: cb.ItemData(2) = AO_MINUS_5
        If DynamicAllowed Then cb.AddItem "dynamic", 3: cb.ItemData(3) = AO_DYNAMIC
    End If
End Sub
Public Function Combo2RangeConst(cb As ComboBox, IODirection As ME300Directions)
    If IODirection = ME300input Then
        Select Case cb.Text
            Case "+10 V": Combo2RangeConst = AI_PLUS_10
            Case "+ 5 V": Combo2RangeConst = AI_PLUS_5
            Case "+ 2.5 V": Combo2RangeConst = AI_PLUS_2
            Case "+ 1.25 V": Combo2RangeConst = AI_PLUS_1
            Case "±10 V": Combo2RangeConst = AI_MINUS_10
            Case "± 5 V": Combo2RangeConst = AI_MINUS_5
            Case "± 2.5 V": Combo2RangeConst = AI_MINUS_2
            Case "± 1.25 V": Combo2RangeConst = AI_MINUS_1
            Case "dynamic": Combo2RangeConst = AI_DYNAMIC
        End Select
    Else
        Select Case cb.Text
            Case "+10 V": Combo2RangeConst = AO_PLUS_10
            Case "±10 V": Combo2RangeConst = AO_MINUS_10
            Case " ±5 V": Combo2RangeConst = AO_MINUS_5
            Case "dynamic": Combo2RangeConst = AO_DYNAMIC
        End Select
    End If
End Function

#End If '#If ME300 Then
