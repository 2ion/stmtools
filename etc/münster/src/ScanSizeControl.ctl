VERSION 5.00
Begin VB.UserControl ScanSizeControl 
   ClientHeight    =   1380
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   3285
   ScaleHeight     =   1380
   ScaleWidth      =   3285
   ToolboxBitmap   =   "ScanSizeControl.ctx":0000
   Begin VB.Frame ScanSize_Frame 
      Caption         =   "Größe der Rasterbereichs"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1335
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   3255
      Begin VB.TextBox ScanSize 
         Alignment       =   1  'Rechts
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   405
         Left            =   510
         TabIndex        =   2
         Text            =   "400"
         Top             =   360
         Width           =   735
      End
      Begin VB.HScrollBar ScanSizeScroll 
         Height          =   255
         LargeChange     =   50
         Left            =   240
         Max             =   400
         Min             =   10
         SmallChange     =   10
         TabIndex        =   1
         Top             =   885
         Value           =   10
         Width           =   2865
      End
      Begin VB.Label ScanSize2 
         Caption         =   "nm × 400 nm"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   1290
         TabIndex        =   3
         Top             =   405
         Width           =   1695
      End
   End
End
Attribute VB_Name = "ScanSizeControl"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit


Public Event Change()



' *******************************************************************************
' *****************     USERCONTROL  --  METHODEN        ************************
' *******************************************************************************



Private Sub UserControl_InitProperties()
    Max = 32767
    Min = -32768
    value = 0
    Set UserControl.Font = Ambient.Font
End Sub

Private Sub UserControl_Resize()
    UserControl.width = 3285
    UserControl.Height = 1380
    
End Sub


' *******************************************************************************
' *****************              METHODEN                ************************
' *******************************************************************************


Private Sub ScanSize_KeyPress(KeyAscii As Integer)
Dim dummy As Boolean
    Select Case KeyAscii
        Case Asc("0") To Asc("9")
            If Len(ScanSize) >= 4 Then KeyAscii = 0
        Case vbKeyBack
            Exit Sub
        Case vbKeyReturn
            ScanSize_Validate dummy
            ScanSizeScroll.SetFocus
        Case Else
            KeyAscii = 0
    End Select
End Sub

Private Sub ScanSize_Validate(Cancel As Boolean)
    Dim SS As Long
    
    SS = CLng(ScanSize / ScanSizeScroll.SmallChange) * ScanSizeScroll.SmallChange
    If SS < Min Then
        MsgBox "Der minimale Scanbereich beträgt " & Min & " nm!", vbCritical + vbOKOnly
        SS = Min
    ElseIf SS > Max Then
        MsgBox "Der maximale Scanbereich beträgt " & Max & " nm!", vbCritical + vbOKOnly
        SS = Max
    End If
    
    ScanSizeScroll.value = SS
    ScanSizeScroll_Change
    Cancel = False
End Sub

Private Sub ScanSizeScroll_Change()
    ScanSizeScroll = (ScanSizeScroll \ ScanSizeScroll.SmallChange) * ScanSizeScroll.SmallChange
    ScanSize.text = CStr(ScanSizeScroll)
    ScanSize2 = "nm × " & ScanSize & " nm"
    RaiseEvent Change
End Sub



' *******************************************************************************
' *****************             PROPERTIES               ************************
' *******************************************************************************



'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=UserControl,UserControl,-1,BackColor
Public Property Get BackColor() As OLE_COLOR
Attribute BackColor.VB_Description = "Gibt die Hintergrundfarbe zurück, die verwendet wird, um Text und Grafik in einem Objekt anzuzeigen, oder legt diese fest."
    BackColor = UserControl.BackColor
End Property

Public Property Let BackColor(ByVal New_BackColor As OLE_COLOR)
    UserControl.BackColor() = New_BackColor
    ScanSize_Frame.BackColor = New_BackColor
    ScanSize2.BackColor = New_BackColor
    PropertyChanged "BackColor"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=UserControl,UserControl,-1,BackStyle
Public Property Get BackStyle() As Integer
Attribute BackStyle.VB_Description = "Zeigt an, ob ein Bezeichnungsfeld oder der Hintergrund eines Figur-Steuerelements transparent oder undurchsichtig ist."
    BackStyle = UserControl.BackStyle
End Property

Public Property Let BackStyle(ByVal New_BackStyle As Integer)
    UserControl.BackStyle() = New_BackStyle
    ScanSize2.BackStyle = New_BackStyle
    PropertyChanged "BackStyle"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=ScanSize_Frame,ScanSize_Frame,-1,Caption
Public Property Get Caption() As String
Attribute Caption.VB_Description = "Gibt den Text zurück, der in der Titelleiste eines Objekts oder unter dem Symbol eines Objekts angezeigt wird, oder legt diesen fest."
    Caption = ScanSize_Frame.Caption
End Property

Public Property Let Caption(ByVal New_Caption As String)
    ScanSize_Frame.Caption() = New_Caption
    PropertyChanged "Caption"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=ScanSize_Frame,ScanSize_Frame,-1,Enabled
Public Property Get Enabled() As Boolean
Attribute Enabled.VB_Description = "Gibt einen Wert zurück, der bestimmt, ob ein Objekt auf vom Benutzer erzeugte Ereignisse reagieren kann, oder legt diesen fest."
    Enabled = ScanSize_Frame.Enabled
End Property

Public Property Let Enabled(ByVal New_Enabled As Boolean)
    ScanSize.Enabled = New_Enabled
    ScanSizeScroll.Enabled = New_Enabled
    ScanSize_Frame.Enabled() = New_Enabled
    ScanSize2.Enabled = New_Enabled
    PropertyChanged "Enabled"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=UserControl,UserControl,-1,Font
Public Property Get Font() As Font
Attribute Font.VB_Description = "Gibt ein Font-Objekt zurück."
Attribute Font.VB_UserMemId = -512
    Set Font = UserControl.Font
End Property

Public Property Set Font(ByVal New_Font As Font)
    Set UserControl.Font = New_Font
    Set ScanSize.Font = New_Font
    Set ScanSize2.Font = New_Font
    PropertyChanged "Font"
End Property


'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=ScanSizeScroll,ScanSizeScroll,-1,SmallChange
Public Property Get SmallChange() As Integer
Attribute SmallChange.VB_Description = "Gibt den Umfang der Änderungen der Value-Eigenschaft einer Bildlaufleiste zurück, wenn der Benutzer auf einen Bildlaufpfeil klickt, oder legt diesen fest."
    SmallChange = ScanSizeScroll.SmallChange
End Property

Public Property Let SmallChange(ByVal New_SmallChange As Integer)
    ScanSizeScroll.SmallChange() = New_SmallChange
    PropertyChanged "SmallChange"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=ScanSizeScroll,ScanSizeScroll,-1,Value
Public Property Get value() As Long
Attribute value.VB_Description = "Gibt den Wert eines Objekts zurück oder legt diesen fest."
    value = ScanSizeScroll.value
End Property

Public Property Let value(ByVal New_Value As Long)
    ScanSizeScroll.value() = New_Value
    PropertyChanged "Value"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=ScanSizeScroll,ScanSizeScroll,-1,Max
Public Property Get Max() As Long
Attribute Max.VB_Description = "Gibt die maximale Einstellung für die Value-Eigenschaft der Position einer Bildlaufleiste zurück oder legt diese fest."
    Max = ScanSizeScroll.Max
End Property

Public Property Let Max(ByVal New_Max As Long)
    ScanSizeScroll.Max() = New_Max
    PropertyChanged "Max"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=ScanSizeScroll,ScanSizeScroll,-1,Min
Public Property Get Min() As Long
Attribute Min.VB_Description = "Gibt die maximale Einstellung für die Value-Eigenschaft der Position einer Bildlaufleiste zurück oder legt diese fest."
    Min = ScanSizeScroll.Min
End Property

Public Property Let Min(ByVal New_Min As Long)
    ScanSizeScroll.Min() = New_Min
    PropertyChanged "Min"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=ScanSizeScroll,ScanSizeScroll,-1,LargeChange
Public Property Get LargeChange() As Integer
Attribute LargeChange.VB_Description = "Gibt den Umfang der Änderung an der Value-Eigenschaft in einer Bildlaufleiste zurück, wenn der Benutzer auf den Bereich der Bildlaufleiste klickt, oder legt diesen fest."
    LargeChange = ScanSizeScroll.LargeChange
End Property

Public Property Let LargeChange(ByVal New_LargeChange As Integer)
    ScanSizeScroll.LargeChange() = New_LargeChange
    PropertyChanged "LargeChange"
End Property

'Eigenschaftenwerte vom Speicher laden
Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
    UserControl.BackColor = PropBag.ReadProperty("BackColor", &H8000000F)
    UserControl.BackStyle = PropBag.ReadProperty("BackStyle", 1)
    ScanSize_Frame.Caption = PropBag.ReadProperty("Caption", "Größe der Rasterbereichs")
    ScanSize_Frame.Enabled = PropBag.ReadProperty("Enabled", True)
    Set UserControl.Font = PropBag.ReadProperty("Font", Ambient.Font)
    ScanSize.Locked = PropBag.ReadProperty("Locked", False)
    ScanSizeScroll.SmallChange = PropBag.ReadProperty("SmallChange", 10)
    ScanSizeScroll.value = PropBag.ReadProperty("Value", 10)
    ScanSizeScroll.Max = PropBag.ReadProperty("Max", 400)
    ScanSizeScroll.Min = PropBag.ReadProperty("Min", 10)
    ScanSizeScroll.LargeChange = PropBag.ReadProperty("LargeChange", 50)
End Sub

'Eigenschaftenwerte in den Speicher schreiben
Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
    Call PropBag.WriteProperty("BackColor", UserControl.BackColor, &H8000000F)
    Call PropBag.WriteProperty("BackStyle", UserControl.BackStyle, 1)
    Call PropBag.WriteProperty("Caption", ScanSize_Frame.Caption, "Größe der Rasterbereichs")
    Call PropBag.WriteProperty("Enabled", ScanSize_Frame.Enabled, True)
    Call PropBag.WriteProperty("Font", UserControl.Font, Ambient.Font)
    Call PropBag.WriteProperty("Locked", ScanSize.Locked, False)
    Call PropBag.WriteProperty("SmallChange", ScanSizeScroll.SmallChange, 10)
    Call PropBag.WriteProperty("Value", ScanSizeScroll.value, 10)
    Call PropBag.WriteProperty("Max", ScanSizeScroll.Max, 400)
    Call PropBag.WriteProperty("Min", ScanSizeScroll.Min, 10)
    Call PropBag.WriteProperty("LargeChange", ScanSizeScroll.LargeChange, 50)
End Sub

