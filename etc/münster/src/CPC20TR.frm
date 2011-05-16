VERSION 5.00
Object = "{E827D880-C8F2-11CF-BC1A-0080489D4CB5}#1.2#0"; "P1000.OCX"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form CPC20TR 
   Caption         =   "PC20TR - Klassenmodul"
   ClientHeight    =   870
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   1560
   LinkTopic       =   "Form1"
   ScaleHeight     =   870
   ScaleWidth      =   1560
   StartUpPosition =   3  'Windows-Standard
   Visible         =   0   'False
   Begin PC20Lib.PC20 PC20 
      Left            =   600
      Top             =   240
      _Version        =   65538
      _ExtentX        =   741
      _ExtentY        =   741
      _StockProps     =   0
   End
   Begin MSComctlLib.Toolbar Toolbar1 
      Align           =   1  'Oben ausrichten
      Height          =   630
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   1560
      _ExtentX        =   2752
      _ExtentY        =   1111
      Appearance      =   1
      _Version        =   393216
   End
End
Attribute VB_Name = "CPC20TR"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
#If PC20TR Then
' **********************************************************************************
' ****************      PUBLIC DEFINITIONS       ***********
' **********************************************************************************

Public Enum PC20TR_CardNumbers
    PC20TR_NoCard = -1
    PC20TR_Card1 = 1
    PC20TR_Card2 = 2
    PC20TR_Card3 = 3
    PC20TR_Card4 = 4
End Enum

Public Enum PC20TR_OutChannelNumbers
    PC20TR_NoOutChannel = -1
    PC20TR_OutChan1 = 1
    PC20TR_OutChan2 = 2
End Enum
Public Enum PC20TR_InChannelNumbers
    PC20TR_NoInChannel = -1
    PC20TR_InChan1 = 1
    PC20TR_InChan2 = 2
    PC20TR_InChan3 = 3
    PC20TR_InChan4 = 4
    PC20TR_InChan5 = 5
    PC20TR_InChan6 = 6
    PC20TR_InChan7 = 7
    PC20TR_InChan8 = 8
    PC20TR_InChan9 = 9
    PC20TR_InChan10 = 10
    PC20TR_InChan11 = 11
    PC20TR_InChan12 = 12
    PC20TR_InChan13 = 13
    PC20TR_InChan14 = 14
    PC20TR_InChan15 = 15
    PC20TR_InChan16 = 16
End Enum

Public Enum PC20TR_Class_Errors
    PC20TR_CardInitFailed = 2001
    PC20TR_SignalWrong = 2002
End Enum
    
Public Enum PC20TR_BitNumber
    PC20TR_Bit0 = 0
    PC20TR_Bit1 = 1
    PC20TR_Bit2 = 2
    PC20TR_Bit3 = 3
    PC20TR_Bit4 = 4
    PC20TR_Bit5 = 5
    PC20TR_Bit6 = 6
    PC20TR_Bit7 = 7
End Enum

Public Enum PC20TR_ByteNumber
    PC20TR_Bit00_08 = 0
    PC20TR_Bit09_16 = 1
    PC20TR_Bit17_24 = 2
    PC20TR_BIT25_32 = 3
End Enum

' **********************************************************************************
' ****************      LOCAL VARIABLES       ***********
' **********************************************************************************


Dim BoardNr As PC20TR_CardNumbers
Dim AORanges(0 To 3) As PC20TR_AnalogOutputRanges
Dim AIRanges(0 To 15) As PC20TR_AnalogInputRanges
Dim DigitalDirection(PC20TR_Bit00_08 To PC20TR_BIT25_32) As PC20TR_Directions


' **********************************************************************************
' **********************************************************************************
' **********************************************************************************
' ****************            PC20TR - DEFINITIONEN                      ***********
' **********************************************************************************
' **********************************************************************************
' **********************************************************************************



Public Enum PC20TR_Directions
    PC20TR_INPUT = 0
    PC20TR_OUTPUT = 1
End Enum

' Analog Input Ranges for PC20TR '
Public Enum PC20TR_AnalogInputRanges
     AI_NORange = -1
     AI_MINUS_10 = 0
     AI_MINUS_5 = 1
     AI_MINUS_2 = 2
     AI_MINUS_1 = 3
End Enum

'Analog Output Ranges '
Public Enum PC20TR_AnalogOutputRanges
    AO_NORange = -1
    AO_MINUS_5 = &H1
    AO_MINUS_10 = &H2
End Enum








' **********************************************************************************
' ****************       PUBLIC EVENTS        ***********
' **********************************************************************************

Public Event InitFailed()
Public Event AnalogInputRangeChanged(ByVal ChannelNr As PC20TR_InChannelNumbers, ByVal fromRange As PC20TR_AnalogInputRanges, ByVal toRange As PC20TR_AnalogInputRanges)
Public Event AnalogOutputRangeChanged(ByVal ChannelNr As PC20TR_OutChannelNumbers, ByVal fromRange As PC20TR_AnalogOutputRanges, ByVal toRange As PC20TR_AnalogOutputRanges)


' **********************************************************************************
' ****************      PROPERTIES         ****************
' **********************************************************************************


Public Property Let BoardNumber(ByVal nr As PC20TR_CardNumbers)
    BoardNr = nr
End Property
Public Property Get BoardNumber() As PC20TR_CardNumbers
    BoardNumber = BoardNr
End Property

Public Function MaxInputVoltage(ByVal ch As PC20TR_InChannelNumbers) As Single
    Select Case AIRanges(ch)
        Case AI_MINUS_10: MaxInputVoltage = 10
        Case AI_MINUS_5: MaxInputVoltage = 5
        Case AI_MINUS_2: MaxInputVoltage = 2
        Case AI_MINUS_1: MaxInputVoltage = 1
        'Case AI_PLUS_10: MaxInputVoltage = 10
        'Case AI_PLUS_5: MaxInputVoltage = 5
        'Case AI_PLUS_2: MaxInputVoltage = 2.5
        'Case AI_PLUS_1: MaxInputVoltage = 1.25
    End Select
End Function
Public Function MinInputVoltage(ByVal ch As PC20TR_InChannelNumbers) As Single
    Select Case AIRanges(ch)
        Case AI_MINUS_10: MinInputVoltage = -10
        Case AI_MINUS_5: MinInputVoltage = -5
        Case AI_MINUS_2: MinInputVoltage = -2
        Case AI_MINUS_1: MinInputVoltage = -1
        'Case AI_PLUS_10: MinInputVoltage = 0
        'Case AI_PLUS_5: MinInputVoltage = 0
        'Case AI_PLUS_2: MinInputVoltage = 0
        'Case AI_PLUS_1: MinInputVoltage = 0
    End Select
End Function

Public Function MaxOutputVoltage(ByVal ch As PC20TR_OutChannelNumbers) As Single
    Select Case AORanges(ch)
        Case AO_MINUS_10: MaxOutputVoltage = 10
        Case AO_MINUS_5: MaxOutputVoltage = 5
        'Case AO_MINUS_2: MaxOutputVoltage = 2.5
        'Case AO_MINUS_1: MaxOutputVoltage = 1.25
        'Case AO_PLUS_10: MaxOutputVoltage = 10
        'Case AO_PLUS_5: MaxOutputVoltage = 5
        'Case AO_PLUS_2: MaxOutputVoltage = 2.5
        'Case AO_PLUS_1: MaxOutputVoltage = 1.25
    End Select
End Function
Public Function MinOutputVoltage(ByVal ch As PC20TR_OutChannelNumbers) As Single
    Select Case AORanges(ch)
        Case AO_MINUS_10: MinOutputVoltage = -10
        Case AO_MINUS_5: MinOutputVoltage = -5
        'Case AO_MINUS_2: MinOutputVoltage = -2.5
        'Case AO_MINUS_1: MinOutputVoltage = -1.25
        'Case AO_PLUS_10: MinOutputVoltage = 0
        'Case AO_PLUS_5: MinOutputVoltage = 0
        'Case AO_PLUS_2: MinOutputVoltage = 0
        'Case AO_PLUS_1: MinOutputVoltage = 0
    End Select
End Function
Public Property Get MaxSkalenteile() As Long
    MaxSkalenteile = &HFFF&
End Property


' **********************************************************************************
' ****************      KLASSEN   -   PC20TR_THODEN     ****************
' **********************************************************************************

Private Sub Class_Initialize()
    Dim ch As Integer
    BoardNumber = PC20TR_NoCard
    
    For ch = 1 To 2
        AORanges(ch) = AO_MINUS_10
    Next ch
    For ch = 1 To 16
        AIRanges(ch) = AI_MINUS_10
    Next ch
End Sub

Private Sub Class_Terminate()
    InitCard
End Sub



' **********************************************************************************
' ****************      METHODEN         ****************
' **********************************************************************************

Public Sub InitCard(Optional ByVal nr As PC20TR_CardNumbers = PC20TR_NoCard)
    Dim version As Long
    
    
    If nr <> PC20TR_NoCard Then BoardNr = nr
    If BoardNr = PC20TR_NoCard Then
        RaiseEvent InitFailed
        Err.Raise vbObjectError + PC20TR_CardInitFailed
        Exit Sub
    End If
    
    'If BoardNr > PC20.InstalledCards Then
    '    RaiseEvent InitFailed
    '    Err.Raise vbObjectError + PC20TR_CardInitFailed
    '    Exit Sub
    'End If
    
    'PC20.CardId = BoardNr
    
    PC20.AnalogOut(1) = 0#
    PC20.AnalogOut(2) = 0#
End Sub

Public Sub SetInputChannelRange(ByVal ChannelNr As PC20TR_InChannelNumbers, ByVal range As PC20TR_AnalogInputRanges)
    Dim OldRange As PC20TR_AnalogInputRanges
    If AIRanges(ChannelNr) = range Then Exit Sub
    OldRange = AIRanges(ChannelNr)
    AIRanges(ChannelNr) = range
    RaiseEvent AnalogInputRangeChanged(ChannelNr, OldRange, range)
End Sub

Public Function GetInputChannelRange(ByVal ChannelNr As PC20TR_InChannelNumbers) As PC20TR_AnalogInputRanges
    GetInputChannelRange = AIRanges(ChannelNr)
End Function

Public Sub SetOutputChannelRange(ByVal ChannelNr As PC20TR_OutChannelNumbers, ByVal range As PC20TR_AnalogOutputRanges)
    Dim OldRange As PC20TR_AnalogOutputRanges
    If AORanges(ChannelNr) = range Then Exit Sub
    OldRange = AORanges(ChannelNr)
    AORanges(ChannelNr) = range
    RaiseEvent AnalogOutputRangeChanged(ChannelNr, OldRange, range)
End Sub
Public Function GetOutputChannelRange(ByVal ChannelNr As PC20TR_OutChannelNumbers) As PC20TR_AnalogOutputRanges
    GetOutputChannelRange = AORanges(ChannelNr)
End Function

' **********************************************************************************

Private Function ConvertOutSignal(ByVal signal As Long, ByVal OutRange As PC20TR_AnalogOutputRanges) As Single
    ConvertOutSignal = -1
    
    If ((signal >= 0) And (signal <= &HFFF)) Then
        Select Case OutRange
            Case AO_MINUS_5
                ConvertOutSignal = (CSng(signal) / &HFFF) * 10 - 5
            Case AO_MINUS_10
                ConvertOutSignal = (CSng(signal) / &HFFF) * 20 - 10
        End Select
    End If
End Function


Public Sub AnalogOutput(ByVal channel As PC20TR_OutChannelNumbers, ByVal value As Single, Optional ByVal OutputRange As PC20TR_AnalogOutputRanges = AO_NORange)
    If OutputRange = AO_NORange Then OutputRange = AORanges(channel)
    If ((value >= -10#) And (value <= 10#)) Then
        PC20.AnalogOut(channel) = value
    Else
        Err.Raise vbObjectError + PC20TR_SignalWrong
    End If
End Sub

Public Sub DirectAnalogOutput(ByVal channel As PC20TR_OutChannelNumbers, ByVal value As Long, Optional ByVal OutputRange As PC20TR_AnalogOutputRanges = AO_NORange)
    If OutputRange = AO_NORange Then OutputRange = AORanges(channel)
    
    If (value >= 0) And (value <= &HFFF) Then
        PC20.AnalogOut(channel) = ConvertOutSignal(value, OutputRange)
    Else
        Err.Raise vbObjectError + PC20TR_SignalWrong
    End If
End Sub


' **********************************************************************************

Public Function ConvertInSignal(ByVal value As Single, ByVal InputRange As PC20TR_AnalogInputRanges) As Integer
    Select Case InputRange
        Case AI_MINUS_10
            ConvertInSignal = ((value + 10) / 20) * &HFFF
        Case AI_MINUS_5
            ConvertInSignal = ((value + 5) / 10) * &HFFF
        Case AI_MINUS_2
            ConvertInSignal = ((value + 2) / 4) * &HFFF
        Case AI_MINUS_1
            ConvertInSignal = ((value + 1) / 2) * &HFFF
    End Select
End Function
Public Function AnalogInput(ByVal channel As PC20TR_InChannelNumbers, Optional ByVal InputRange As PC20TR_AnalogInputRanges = AI_NORange) As Single
    If InputRange = AI_NORange Then InputRange = AIRanges(channel)
    PC20.AnalogInRange = InputRange
    AnalogInput = PC20.AnalogIn(channel)
End Function
Public Function DirectAnalogInput(ByVal channel As PC20TR_InChannelNumbers, Optional ByVal InputRange As PC20TR_AnalogInputRanges = AI_NORange) As Integer
    Dim value As Single
    
    If InputRange = AI_NORange Then InputRange = AIRanges(channel)
    PC20.AnalogInRange = InputRange
    value = PC20.AnalogIn(channel)
    
    DirectAnalogInput = ConvertInSignal(value, InputRange)
End Function


' **********************************************************************************

Public Sub FillComboBox(cb As ComboBox, IODirection As PC20TR_Directions)
    cb.Clear
    If IODirection = PC20TR_INPUT Then
        cb.AddItem "±10 V", 0: cb.ItemData(0) = AI_MINUS_10
        cb.AddItem "± 5 V", 1: cb.ItemData(1) = AI_MINUS_5
        cb.AddItem "± 2 V", 2: cb.ItemData(2) = AI_MINUS_2
        cb.AddItem "± 1 V", 3: cb.ItemData(3) = AI_MINUS_1
    Else
        cb.AddItem "±10 V", 0: cb.ItemData(0) = AO_MINUS_10
        cb.AddItem "± 5 V", 1: cb.ItemData(1) = AO_MINUS_5
    End If
End Sub
Public Function Combo2RangeConst(cb As ComboBox, IODirection As PC20TR_Directions)
    If IODirection = PC20TR_INPUT Then
        Select Case cb.text
            Case "±10 V": Combo2RangeConst = AI_MINUS_10
            Case "± 5 V": Combo2RangeConst = AI_MINUS_5
            Case "± 2 V": Combo2RangeConst = AI_MINUS_2
            Case "± 1 V": Combo2RangeConst = AI_MINUS_1
        End Select
    Else
        Select Case cb.text
            Case "±10 V": Combo2RangeConst = AO_MINUS_10
            Case "± 5 V": Combo2RangeConst = AO_MINUS_5
        End Select
    End If
End Function

#End If 'if pc20tr
