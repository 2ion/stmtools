VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CRandom"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
#If ME300 Then

Private miv As Single
Private x As Single
' **********************************************************************************
' ****************      PUBLIC DEFINITIONS       ***********
' **********************************************************************************


' **********************************************************************************
' ****************       PUBLIC EVENTS        ***********
' **********************************************************************************

Public Event AnalogInputRangeChanged(ByVal ChannelNr As ME300InChannelNumbers, ByVal fromRange As ME300AnalogInputRanges, ByVal toRange As ME300AnalogInputRanges)
Public Event AnalogOutputRangeChanged(ByVal ChannelNr As ME300OutChannelNumbers, ByVal fromRange As ME300AnalogOutputRanges, ByVal toRange As ME300AnalogOutputRanges)


' **********************************************************************************
' ****************      PROPERTIES         ****************
' **********************************************************************************

Public Function MaxInputVoltage(ByVal ch As Long) As Single
    MaxInputVoltage = miv
End Function
Public Function MinInputVoltage(ByVal ch As Long) As Single
    MinInputVoltage = -miv
End Function

Public Function MaxOutputVoltage() As Single
    MaxOutputVoltage = miv
End Function
Public Function MinOutputVoltage() As Single
    MinOutputVoltage = -miv
End Function
Public Property Get MaxSkalenteile() As Long
    MaxSkalenteile = 2 ^ 12 - 1
End Property


' **********************************************************************************
' ****************      KLASSEN   -   ME300THODEN     ****************
' **********************************************************************************

Private Sub Class_Initialize()
    Randomize
    miv = 10#
End Sub

' **********************************************************************************
' ****************      METHODEN         ****************
' **********************************************************************************

Public Sub AnalogOutput(ByVal ch As Long, ByVal signal As Single)
    x = signal
End Sub
Public Sub DirectAnalogOutput(ByVal ch As Long, ByVal value As Long)
End Sub

Public Sub InitCard(ByVal c As Long)

End Sub
Public Sub SetOutputChannelRange(ByVal c As Long, ByVal r As Long)

End Sub
' **********************************************************************************

Public Sub SetInputChannelRange(ByVal ch As Long, ByVal range As Long)
    Select Case range
        Case 0: miv = 10#
        Case &H10: miv = 5#
        Case &H20: miv = 2.5
        Case &H30: miv = 1.25
    End Select
    RaiseEvent AnalogInputRangeChanged(ch, AI_MINUS_1, AI_MINUS_1)
End Sub

Public Function ConvertInSignal(ByVal value As Long) As Single
    ConvertInSignal = CSng(value) / MaxSkalenteile * (Me.MaxOutputVoltage - Me.MinOutputVoltage) + Me.MinOutputVoltage
End Function
Public Function AnalogInput(ByVal channel As ME300InChannelNumbers, Optional ByVal InputRange As ME300AnalogInputRanges = AI_NORange) As Single
    AnalogInput = ConvertInSignal(DirectAnalogInput(channel, InputRange))
End Function
Public Function DirectAnalogInput(ByVal channel As ME300InChannelNumbers, Optional ByVal InputRange As ME300AnalogInputRanges = AI_NORange) As Long
    Dim s As Single
    '---------- Noise
    's = Rnd()
    
    '--------- Sine
    's = Sin(2 * 3.141592 * x / 0.1)
    's = 0.75 * s * 0.5
    's = (s + 0.5)
    
    '--------- Sine+ramp
    s = Sin(2 * 3.141592 * x / 0.1) + x / 5
    s = 0.5 * s * 0.5
    s = (s + 0.5)
    
    '--------- ramp
    's =  x / 10 * 0.75 * 0.5
    's = (s + 0.5)

    DirectAnalogInput = CLng(s * MaxSkalenteile)
End Function


' **********************************************************************************

#End If '#if me300
