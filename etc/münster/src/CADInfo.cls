VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CADInfo"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Description = "Analog-Digital-Info"
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Option Explicit


Private varMaxSkalenteile As Long
Private varMaxInputVoltage As Single
Private varMinInputVoltage As Single
Private varOPGain As Single



Private Sub Class_Initialize()
    ' Spezifikationen fuer die ME300 von Meilhaus
    varMaxSkalenteile = &HFFF& '12Bit
    varMaxInputVoltage = 10# 'V
    varMinInputVoltage = -10# 'V
    varOPGain = 1# 'V/nA
End Sub



' ****************************************************************************************
' ***************************           PROPERTIES                 ***********************
' ****************************************************************************************


Friend Property Let MaxInputVoltage(ByVal voltage As Single)
    varMaxInputVoltage = voltage
End Property
Friend Property Get MaxInputVoltage() As Single
    MaxInputVoltage = varMaxInputVoltage
End Property


Friend Property Let MinInputVoltage(ByVal voltage As Single)
   varMinInputVoltage = voltage
End Property
Friend Property Get MinInputVoltage() As Single
    MinInputVoltage = varMinInputVoltage
End Property



Friend Property Let MaxSkalenteile(ByVal value As Long)
    varMaxSkalenteile = value
End Property
Friend Property Get MaxSkalenteile() As Long
    MaxSkalenteile = varMaxSkalenteile
End Property



Friend Property Let OP_Gain(ByVal V_pro_nA As Single)
    varOPGain = V_pro_nA
End Property
Friend Property Get OP_Gain() As Single
    OP_Gain = varOPGain
End Property




' ***************************************************************************************
' ***********************           METHODEN                *****************************
' ***************************************************************************************


Friend Sub GetInfoFromSTMTip(Optional ByVal STMTip As CSTM_Tip = Nothing)
    If STMTip Is Nothing Then Set STMTip = New CSTM_Tip
    
    Me.MaxInputVoltage = STMTip.MaxInputVoltage
    Me.MinInputVoltage = STMTip.MinInputVoltage
    Me.MaxSkalenteile = STMTip.MaxSkalenteile
    
    Set STMTip = Nothing
End Sub

Friend Sub SetInfo(ByVal MaxInputVolt As Single, ByVal MinInputVolt As Single, ByVal MaxSkalenteil As Long, ByVal OPV_Gain As Single)
    Me.MaxInputVoltage = MaxInputVolt
    Me.MinInputVoltage = MinInputVolt
    Me.MaxSkalenteile = MaxSkalenteil
    Me.OP_Gain = OPV_Gain
End Sub
Friend Function Skalenteile2NanoAmpere(ByVal ST As Long) As Single
    Dim v As Single
    v = (Me.MaxInputVoltage - Me.MinInputVoltage) / Me.MaxSkalenteile
    v = v * ST + MinInputVoltage
    Skalenteile2NanoAmpere = v * Me.OP_Gain
End Function

Friend Function Skalenteile2Label(ByVal ST As Long) As String
    Skalenteile2Label = Format(Skalenteile2NanoAmpere(ST), "0.00 "" nA""")
End Function
