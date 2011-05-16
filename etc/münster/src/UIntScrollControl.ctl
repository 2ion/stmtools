VERSION 5.00
Begin VB.UserControl UIntScrollControl 
   ClientHeight    =   270
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4080
   ScaleHeight     =   270
   ScaleWidth      =   4080
   Begin VB.HScrollBar HS 
      Height          =   255
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   4095
   End
End
Attribute VB_Name = "UIntScrollControl"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public Event Change()

Private Function int2uint(i As Integer) As Long
    int2uint = CLng(i + 32768)
End Function
Private Function uint2int(ui As Long) As Integer
    If ui < 0 Then ui = 0
    If ui > &HFFFF& Then ui = &HFFFF&
    uint2int = CInt(ui - 32768)
End Function



'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=HS,HS,-1,CausesValidation
Public Property Get CausesValidation() As Boolean
Attribute CausesValidation.VB_Description = "Gibt zurück oder legt fest, ob für ein Steuerelement, das den Fokus verloren hat, eine Überprüfung stattfindet."
    CausesValidation = HS.CausesValidation
End Property

Public Property Let CausesValidation(ByVal New_CausesValidation As Boolean)
    HS.CausesValidation() = New_CausesValidation
    PropertyChanged "CausesValidation"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=HS,HS,-1,Enabled
Public Property Get Enabled() As Boolean
Attribute Enabled.VB_Description = "Gibt einen Wert zurück, der bestimmt, ob ein Objekt auf vom Benutzer erzeugte Ereignisse reagieren kann, oder legt diesen fest."
    Enabled = HS.Enabled
End Property

Public Property Let Enabled(ByVal New_Enabled As Boolean)
    HS.Enabled() = New_Enabled
    PropertyChanged "Enabled"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=HS,HS,-1,LargeChange
Public Property Get LargeChange() As Long
Attribute LargeChange.VB_Description = "Gibt den Umfang der Änderung an der Value-Eigenschaft in einer Bildlaufleiste zurück, wenn der Benutzer auf den Bereich der Bildlaufleiste klickt, oder legt diesen fest."
    LargeChange = int2uint(HS.LargeChange)
End Property

Public Property Let LargeChange(ByVal New_LargeChange As Long)
    HS.LargeChange() = uint2int(New_LargeChange)
    PropertyChanged "LargeChange"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=HS,HS,-1,Max
Public Property Get Max() As Long
Attribute Max.VB_Description = "Gibt die maximale Einstellung für die Value-Eigenschaft der Position einer Bildlaufleiste zurück oder legt diese fest."
    Max = int2uint(HS.Max)
End Property

Public Property Let Max(ByVal New_Max As Long)
    HS.Max() = uint2int(New_Max)
    PropertyChanged "Max"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=HS,HS,-1,Min
Public Property Get Min() As Long
Attribute Min.VB_Description = "Gibt die maximale Einstellung für die Value-Eigenschaft der Position einer Bildlaufleiste zurück oder legt diese fest."
    Min = int2uint(HS.Min)
End Property

Public Property Let Min(ByVal New_Min As Long)
    HS.Min() = uint2int(New_Min)
    PropertyChanged "Min"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=HS,HS,-1,MouseIcon
Public Property Get MouseIcon() As Picture
Attribute MouseIcon.VB_Description = "Legt ein benutzerdefiniertes Maussymbol fest."
    Set MouseIcon = HS.MouseIcon
End Property

Public Property Set MouseIcon(ByVal New_MouseIcon As Picture)
    Set HS.MouseIcon = New_MouseIcon
    PropertyChanged "MouseIcon"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=HS,HS,-1,MousePointer
Public Property Get MousePointer() As Integer
Attribute MousePointer.VB_Description = "Gibt den Typ des Mauszeigers zurück, der angezeigt wird, wenn dieser sich über einem Teil eines Objekts befindet, oder legt diesen fest."
    MousePointer = HS.MousePointer
End Property

Public Property Let MousePointer(ByVal New_MousePointer As Integer)
    HS.MousePointer() = New_MousePointer
    PropertyChanged "MousePointer"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=HS,HS,-1,SmallChange
Public Property Get SmallChange() As Long
Attribute SmallChange.VB_Description = "Gibt den Umfang der Änderungen der Value-Eigenschaft einer Bildlaufleiste zurück, wenn der Benutzer auf einen Bildlaufpfeil klickt, oder legt diesen fest."
    SmallChange = int2uint(HS.SmallChange)
End Property

Public Property Let SmallChange(ByVal New_SmallChange As Long)
    HS.SmallChange() = uint2int(New_SmallChange)
    PropertyChanged "SmallChange"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=HS,HS,-1,Value
Public Property Get value() As Long
Attribute value.VB_Description = "Gibt den Wert eines Objekts zurück oder legt diesen fest."
    value = int2uint(HS.value)
End Property

Public Property Let value(ByVal New_Value As Long)
    HS.value() = uint2int(New_Value)
    PropertyChanged "Value"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=HS,HS,-1,WhatsThisHelpID
Public Property Get WhatsThisHelpID() As Long
Attribute WhatsThisHelpID.VB_Description = "Gibt eine zugeordnete Kontextnummer für ein Objekt zurück oder legt diese fest."
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
    HS.Max = PropBag.ReadProperty("Max", 32767)
    HS.Min = PropBag.ReadProperty("Min", 0)
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
    Call PropBag.WriteProperty("Max", HS.Max, 32767)
    Call PropBag.WriteProperty("Min", HS.Min, 0)
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

