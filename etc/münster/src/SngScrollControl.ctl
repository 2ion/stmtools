VERSION 5.00
Begin VB.UserControl SngScrollControl 
   ClientHeight    =   270
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   3480
   ScaleHeight     =   270
   ScaleWidth      =   3480
   Begin VB.HScrollBar HS 
      Height          =   252
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   3492
   End
End
Attribute VB_Name = "SngScrollControl"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public Event Change()

Private Function Int2Sng(ByVal i As Integer) As Single
    Int2Sng = CSng(i / 1000)
End Function
Private Function Sng2Int(ByVal s As Single) As Integer
    If s < -30# Then s = -30#
    If s > 30# Then s = 30#
    Sng2Int = CInt(s * 1000)
End Function



'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=HS,HS,-1,CausesValidation
Public Property Get CausesValidation() As Boolean
    CausesValidation = HS.CausesValidation
End Property

Public Property Let CausesValidation(ByVal New_CausesValidation As Boolean)
    HS.CausesValidation() = New_CausesValidation
    PropertyChanged "CausesValidation"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=HS,HS,-1,Enabled
Public Property Get Enabled() As Boolean
    Enabled = HS.Enabled
End Property

Public Property Let Enabled(ByVal New_Enabled As Boolean)
    HS.Enabled() = New_Enabled
    PropertyChanged "Enabled"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=HS,HS,-1,LargeChange
Public Property Get LargeChange() As Single
    LargeChange = Int2Sng(HS.LargeChange)
End Property

Public Property Let LargeChange(ByVal New_LargeChange As Single)
    HS.LargeChange() = Sng2Int(New_LargeChange)
    PropertyChanged "LargeChange"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=HS,HS,-1,Max
Public Property Get max() As Long
    max = Int2Sng(HS.max)
End Property

Public Property Let max(ByVal New_Max As Long)
    Dim i As Integer
    i = Sng2Int(New_Max)
    If i < HS.min Then HS.min = i
    If i < HS.value Then HS.value = i
    HS.max() = i
    PropertyChanged "Max"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=HS,HS,-1,Min
Public Property Get min() As Long
    min = Int2Sng(HS.min)
End Property

Public Property Let min(ByVal New_Min As Long)
    Dim i As Integer
    i = Sng2Int(New_Min)
    If i > HS.max Then HS.max = i
    If i > HS.value Then HS.value = i
    HS.min() = i
    PropertyChanged "Min"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=HS,HS,-1,MouseIcon
Public Property Get MouseIcon() As Picture
    Set MouseIcon = HS.MouseIcon
End Property

Public Property Set MouseIcon(ByVal New_MouseIcon As Picture)
    Set HS.MouseIcon = New_MouseIcon
    PropertyChanged "MouseIcon"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=HS,HS,-1,MousePointer
Public Property Get MousePointer() As Integer
    MousePointer = HS.MousePointer
End Property

Public Property Let MousePointer(ByVal New_MousePointer As Integer)
    HS.MousePointer() = New_MousePointer
    PropertyChanged "MousePointer"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=HS,HS,-1,SmallChange
Public Property Get SmallChange() As Single
    SmallChange = Int2Sng(HS.SmallChange)
End Property

Public Property Let SmallChange(ByVal New_SmallChange As Single)
    HS.SmallChange() = Sng2Int(New_SmallChange)
    PropertyChanged "SmallChange"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=HS,HS,-1,Value
Public Property Get value() As Single
    value = Int2Sng(HS.value)
End Property

Public Property Let value(ByVal New_Value As Single)
    Dim i As Integer
    i = Sng2Int(New_Value)
    If i < HS.min Then HS.min = i
    If i > HS.max Then HS.max = i
    HS.value = i
    PropertyChanged "Value"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=HS,HS,-1,WhatsThisHelpID
Public Property Get WhatsThisHelpID() As Long
    WhatsThisHelpID = HS.WhatsThisHelpID
End Property

Public Property Let WhatsThisHelpID(ByVal New_WhatsThisHelpID As Long)
    HS.WhatsThisHelpID() = New_WhatsThisHelpID
    PropertyChanged "WhatsThisHelpID"
End Property

Private Sub HS_Change()
    RaiseEvent Change
End Sub

'Eigenschaftenwerte vom Speicher laden
Private Sub UserControl_ReadProperties(PropBag As PropertyBag)

    HS.CausesValidation = PropBag.ReadProperty("CausesValidation", True)
    HS.Enabled = PropBag.ReadProperty("Enabled", True)
    HS.LargeChange = PropBag.ReadProperty("LargeChange", 1)
    HS.max = PropBag.ReadProperty("Max", 30000)
    HS.min = PropBag.ReadProperty("Min", -30000)
    Set MouseIcon = PropBag.ReadProperty("MouseIcon", Nothing)
    HS.MousePointer = PropBag.ReadProperty("MousePointer", 0)
    HS.SmallChange = PropBag.ReadProperty("SmallChange", 1)
    HS.value = PropBag.ReadProperty("Value", 0)
    HS.WhatsThisHelpID = PropBag.ReadProperty("WhatsThisHelpID", 0)
End Sub


'Eigenschaftenwerte in den Speicher schreiben
Private Sub UserControl_WriteProperties(PropBag As PropertyBag)

    Call PropBag.WriteProperty("CausesValidation", HS.CausesValidation, True)
    Call PropBag.WriteProperty("Enabled", HS.Enabled, True)
    Call PropBag.WriteProperty("LargeChange", HS.LargeChange, 1)
    Call PropBag.WriteProperty("Max", HS.max, 30000)
    Call PropBag.WriteProperty("Min", HS.min, -30000)
    Call PropBag.WriteProperty("MouseIcon", MouseIcon, Nothing)
    Call PropBag.WriteProperty("MousePointer", HS.MousePointer, 0)
    Call PropBag.WriteProperty("SmallChange", HS.SmallChange, 1)
    Call PropBag.WriteProperty("Value", HS.value, 0)
    Call PropBag.WriteProperty("WhatsThisHelpID", HS.WhatsThisHelpID, 0)
End Sub


Private Sub UserControl_Resize()
    HS.top = 0
    HS.left = 0
    HS.width = UserControl.width
    HS.Height = UserControl.Height
End Sub


