VERSION 5.00
Begin VB.UserControl ScanFrameOffsetControl 
   ClientHeight    =   1116
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   3276
   ScaleHeight     =   1116
   ScaleWidth      =   3276
   ToolboxBitmap   =   "ScanFrameOffsetControl.ctx":0000
   Begin VB.Frame Frame2 
      Caption         =   "Verschiebung des Rasterrahmen"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   9.6
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1095
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   3255
      Begin VB.HScrollBar XScroll 
         Height          =   255
         LargeChange     =   20
         Left            =   960
         Max             =   200
         SmallChange     =   5
         TabIndex        =   3
         Top             =   360
         Width           =   1215
      End
      Begin VB.HScrollBar YScroll 
         Height          =   255
         LargeChange     =   20
         Left            =   960
         Max             =   200
         SmallChange     =   5
         TabIndex        =   2
         Top             =   720
         Width           =   1215
      End
      Begin VB.PictureBox MaxScanFrameRect 
         Appearance      =   0  '2D
         BackColor       =   &H80000005&
         ForeColor       =   &H80000008&
         Height          =   735
         Left            =   2400
         ScaleHeight     =   400
         ScaleMode       =   0  'Benutzerdefiniert
         ScaleWidth      =   400
         TabIndex        =   1
         Top             =   240
         Width           =   735
         Begin VB.Image ScanFrameRect 
            Appearance      =   0  '2D
            BorderStyle     =   1  'Fest Einfach
            DragMode        =   1  'Automatisch
            Height          =   352
            Left            =   0
            Picture         =   "ScanFrameOffsetControl.ctx":0312
            Stretch         =   -1  'True
            Top             =   0
            Width           =   352
         End
      End
      Begin VB.Label XLabel 
         Caption         =   "X: 0 nm"
         Height          =   255
         Left            =   120
         TabIndex        =   5
         Top             =   360
         Width           =   735
      End
      Begin VB.Label YLabel 
         Caption         =   "Y: 0 nm"
         Height          =   255
         Left            =   120
         TabIndex        =   4
         Top             =   720
         Width           =   735
      End
   End
End
Attribute VB_Name = "ScanFrameOffsetControl"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

'Ereignisdeklarationen:
Event Change() 'MappingInfo=XScroll,XScroll,-1,Change



' **********************************************************************************
' **********************             PROPERTIES        *****************************
' **********************************************************************************


'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=UserControl,UserControl,-1,BackColor
Public Property Get BackColor() As OLE_COLOR
Attribute BackColor.VB_Description = "Gibt die Hintergrundfarbe zurück, die verwendet wird, um Text und Grafik in einem Objekt anzuzeigen, oder legt diese fest."
    BackColor = UserControl.BackColor
End Property

Public Property Let BackColor(ByVal New_BackColor As OLE_COLOR)
    UserControl.BackColor() = New_BackColor
    Frame2.BackColor = New_BackColor
    XLabel.BackColor = New_BackColor
    YLabel.BackColor = New_BackColor
    PropertyChanged "BackColor"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=Frame2,Frame2,-1,ForeColor
Public Property Get ForeColor() As OLE_COLOR
Attribute ForeColor.VB_Description = "Gibt die Vordergrundfarbe zurück, die zum Anzeigen von Text und Grafiken in einem Objekt verwendet wird, oder legt diese fest."
    ForeColor = Frame2.ForeColor
End Property

Public Property Let ForeColor(ByVal New_ForeColor As OLE_COLOR)
    Frame2.ForeColor() = New_ForeColor
    XLabel.ForeColor = New_ForeColor
    YLabel.ForeColor = New_ForeColor
    PropertyChanged "ForeColor"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=Frame2,Frame2,-1,Enabled
Public Property Get Enabled() As Boolean
Attribute Enabled.VB_Description = "Gibt einen Wert zurück, der bestimmt, ob ein Objekt auf vom Benutzer erzeugte Ereignisse reagieren kann, oder legt diesen fest."
    Enabled = Frame2.Enabled
End Property

Public Property Let Enabled(ByVal New_Enabled As Boolean)
    Frame2.Enabled = New_Enabled
    XLabel.Enabled = New_Enabled
    YLabel.Enabled = New_Enabled
    XScroll.Enabled = New_Enabled
    YScroll.Enabled = New_Enabled
    MaxScanFrameRect.Enabled = New_Enabled
    ScanFrameRect.Enabled = New_Enabled
    PropertyChanged "Enabled"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=Frame2,Frame2,-1,Font
Public Property Get Font() As Font
Attribute Font.VB_Description = "Gibt ein Font-Objekt zurück."
Attribute Font.VB_UserMemId = -512
    Set Font = Frame2.Font
End Property

Public Property Set Font(ByVal New_Font As Font)
    Set Frame2.Font = New_Font
    Set XLabel.Font = New_Font
    Set YLabel.Font = New_Font
    
    PropertyChanged "Font"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=UserControl,UserControl,-1,BackStyle
Public Property Get BackStyle() As Integer
Attribute BackStyle.VB_Description = "Zeigt an, ob ein Bezeichnungsfeld oder der Hintergrund eines Figur-Steuerelements transparent oder undurchsichtig ist."
    BackStyle = UserControl.BackStyle
End Property

Public Property Let BackStyle(ByVal New_BackStyle As Integer)
    UserControl.BackStyle() = New_BackStyle
    XLabel.BackStyle = New_BackStyle
    YLabel.BackStyle = New_BackStyle
    PropertyChanged "BackStyle"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=Frame2,Frame2,-1,Caption
Public Property Get Caption() As String
Attribute Caption.VB_Description = "Gibt den Text zurück, der in der Titelleiste eines Objekts oder unter dem Symbol eines Objekts angezeigt wird, oder legt diesen fest."
    Caption = Frame2.Caption
End Property

Public Property Let Caption(ByVal New_Caption As String)
    Frame2.Caption = New_Caption
    PropertyChanged "Caption"
End Property


'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=XScroll,XScroll,-1,SmallChange
Public Property Get SmallChange() As Integer
Attribute SmallChange.VB_Description = "Gibt den Umfang der Änderungen der Value-Eigenschaft einer Bildlaufleiste zurück, wenn der Benutzer auf einen Bildlaufpfeil klickt, oder legt diesen fest."
    SmallChange = XScroll.SmallChange
End Property

Public Property Let SmallChange(ByVal New_SmallChange As Integer)
    XScroll.SmallChange = New_SmallChange
    YScroll.SmallChange = New_SmallChange
    PropertyChanged "SmallChange"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=XScroll,XScroll,-1,LargeChange
Public Property Get LargeChange() As Integer
Attribute LargeChange.VB_Description = "Gibt den Umfang der Änderung an der Value-Eigenschaft in einer Bildlaufleiste zurück, wenn der Benutzer auf den Bereich der Bildlaufleiste klickt, oder legt diesen fest."
    LargeChange = XScroll.LargeChange
End Property

Public Property Let LargeChange(ByVal New_LargeChange As Integer)
    XScroll.LargeChange = New_LargeChange
    YScroll.LargeChange = New_LargeChange
    PropertyChanged "LargeChange"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=YScroll,YScroll,-1,Value
Public Property Get y() As Long
Attribute y.VB_Description = "Gibt den Wert eines Objekts zurück oder legt diesen fest."
    y = YScroll.value
End Property

Public Property Let y(ByVal New_Y As Long)
    YScroll.value = New_Y
    PropertyChanged "Y"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=XScroll,XScroll,-1,Value
Public Property Get x() As Long
Attribute x.VB_Description = "Gibt den Wert eines Objekts zurück oder legt diesen fest."
    x = XScroll.value
End Property

Public Property Let x(ByVal New_X As Long)
    XScroll.value = New_X
    PropertyChanged "X"
End Property



Public Property Get MaxScanSize() As Long
    MaxScanSize = MaxScanFrameRect.ScaleWidth
End Property

Public Property Let MaxScanSize(ByVal New_MaxScanSize As Long)
    MaxScanFrameRect.ScaleWidth = New_MaxScanSize
    MaxScanFrameRect.ScaleHeight = New_MaxScanSize
    If New_MaxScanSize < ScanSize Then ScanSize = New_MaxScanSize
    XScroll.Max = New_MaxScanSize - ScanSize
    YScroll.Max = New_MaxScanSize - ScanSize
    PropertyChanged "MaxScanSize"
End Property


Public Property Get ScanSize() As Long
    ScanSize = ScanFrameRect.width
End Property

Public Property Let ScanSize(ByVal New_ScanSize As Long)
    Dim newy As Long, newx As Long
    If New_ScanSize > MaxScanSize Then New_ScanSize = MaxScanSize
    XScroll.Max = MaxScanSize - New_ScanSize
    YScroll.Max = MaxScanSize - New_ScanSize
    
    With ScanFrameRect
        newy = .top + .width \ 2 - New_ScanSize \ 2
        newx = .left + .width \ 2 - New_ScanSize \ 2
    End With
    
    If newy < 0 Then newy = 0
    If (newy + New_ScanSize) > MaxScanSize Then newy = MaxScanSize - New_ScanSize
    If newx < 0 Then newx = 0
    If (newx + New_ScanSize) > MaxScanSize Then newx = MaxScanSize - New_ScanSize
    YScroll = newy
    ScanFrameRect.width = New_ScanSize
    XScroll = newx
    ScanFrameRect.Height = New_ScanSize
    
    PropertyChanged "ScanSize"
End Property

' **********************************************************************************
' *****************          USERCONTROL - METHODEN                *****************
' **********************************************************************************

'Eigenschaftenwerte vom Speicher laden
Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
    UserControl.BackColor = PropBag.ReadProperty("BackColor", &H8000000F)
    Frame2.ForeColor = PropBag.ReadProperty("ForeColor", &H80000012)
    Frame2.Enabled = PropBag.ReadProperty("Enabled", True)
    Set Frame2.Font = PropBag.ReadProperty("Font", Ambient.Font)
    UserControl.BackStyle = PropBag.ReadProperty("BackStyle", 1)
    Frame2.Caption = PropBag.ReadProperty("Caption", "Verschiebung des Rasterrahmen")
    XScroll.SmallChange = PropBag.ReadProperty("SmallChange", 5)
    XScroll.LargeChange = PropBag.ReadProperty("LargeChange", 20)
    YScroll.value = PropBag.ReadProperty("Y", 0)
    XScroll.value = PropBag.ReadProperty("X", 0)
    MaxScanFrameRect.ScaleWidth = PropBag.ReadProperty("MaxScanSize", 400)
    MaxScanFrameRect.ScaleHeight = PropBag.ReadProperty("MaxScanSize", 400)
    ScanFrameRect.width = PropBag.ReadProperty("ScanSize", 200)
    ScanFrameRect.Height = PropBag.ReadProperty("ScanSize", 200)
End Sub


'Eigenschaftenwerte in den Speicher schreiben
Private Sub UserControl_WriteProperties(PropBag As PropertyBag)

    Call PropBag.WriteProperty("BackColor", UserControl.BackColor, &H8000000F)
    Call PropBag.WriteProperty("ForeColor", Frame2.ForeColor, &H80000012)
    Call PropBag.WriteProperty("Enabled", Frame2.Enabled, True)
    Call PropBag.WriteProperty("Font", Frame2.Font, Ambient.Font)
    Call PropBag.WriteProperty("BackStyle", UserControl.BackStyle, 1)
    Call PropBag.WriteProperty("Caption", Frame2.Caption, "Verschiebung des Rasterrahmen")
    Call PropBag.WriteProperty("SmallChange", XScroll.SmallChange, 5)
    Call PropBag.WriteProperty("LargeChange", XScroll.LargeChange, 20)
    Call PropBag.WriteProperty("Y", YScroll.value, 0)
    Call PropBag.WriteProperty("X", XScroll.value, 0)
    Call PropBag.WriteProperty("MaxScanSize", MaxScanFrameRect.ScaleWidth, 400)
    Call PropBag.WriteProperty("ScanSize", ScanFrameRect.width, 200)
End Sub


Private Sub UserControl_Resize()
    UserControl.width = 3270
    UserControl.Height = 1110
End Sub


' **********************************************************************************
' **********************              METHODEN         *****************************
' **********************************************************************************

Public Sub CenterFrame()
    XScroll = (MaxScanSize - ScanSize) \ 2
    YScroll = x
End Sub

Private Sub XScroll_Change()
    XLabel.Caption = "X: " & CStr(XScroll) & " nm"
    ScanFrameRect.left = XScroll
    RaiseEvent Change
End Sub
Private Sub YScroll_Change()
    YLabel.Caption = "Y: " & CStr(YScroll) & " nm"
    ScanFrameRect.top = YScroll
    RaiseEvent Change
End Sub

Private Sub MaxScanFrameRect_DragDrop(Source As Control, x As Single, y As Single)
    Dim newx As Long
    Dim newy As Long
    
    If Source = ScanFrameRect Then
        newx = CLng(MaxScanFrameRect.ScaleX(x, vbTwips, vbUser))
        newy = CLng(MaxScanFrameRect.ScaleY(y, vbTwips, vbUser))
        
        If newx < 0 Then newx = 0
        If newy < 0 Then newy = 0
        If (newx + ScanSize > MaxScanSize) Then newx = MaxScanSize - ScanSize
        If (newy + ScanSize > MaxScanSize) Then newy = MaxScanSize - ScanSize
        YScroll = newy
        XScroll = newx
    End If
End Sub

