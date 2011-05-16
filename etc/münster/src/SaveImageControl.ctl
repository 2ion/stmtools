VERSION 5.00
Begin VB.UserControl SaveImageControl 
   ClientHeight    =   1050
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   1155
   ScaleHeight     =   1050
   ScaleWidth      =   1155
   ToolboxBitmap   =   "SaveImageControl.ctx":0000
   Begin VB.OptionButton SaveThisImage 
      Caption         =   "dieses Bild"
      Height          =   300
      Left            =   0
      Style           =   1  'Grafisch
      TabIndex        =   2
      Top             =   720
      Width           =   1095
   End
   Begin VB.OptionButton SaveNextImage 
      Caption         =   "nächstes Bild"
      Height          =   300
      Left            =   0
      Style           =   1  'Grafisch
      TabIndex        =   1
      Top             =   360
      Width           =   1095
   End
   Begin VB.OptionButton SaveNoImage 
      Caption         =   "kein Bild"
      Height          =   300
      Left            =   0
      Style           =   1  'Grafisch
      TabIndex        =   0
      Top             =   0
      Value           =   -1  'True
      Width           =   1095
   End
End
Attribute VB_Name = "SaveImageControl"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public Enum SIC_SaveDataConstants
    SICSaveNone = 0
    SICSaveNext = 1
    SICSaveThis = 2
End Enum

Public Event Change()
Public Event Click()

'Standard-Eigenschaftswerte:
Const m_def_Value = SICSaveNone
'Eigenschaftsvariablen:
Dim m_Value As SaveDataConstants



'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=SaveNextImage,SaveNextImage,-1,BackColor
Public Property Get BackColor() As OLE_COLOR
Attribute BackColor.VB_Description = "Gibt die Hintergrundfarbe zurück, die verwendet wird, um Text und Grafik in einem Objekt anzuzeigen, oder legt diese fest."
    BackColor = SaveNextImage.BackColor
End Property

Public Property Let BackColor(ByVal New_BackColor As OLE_COLOR)
    SaveNextImage.BackColor = New_BackColor
    SaveThisImage.BackColor = New_BackColor
    SaveNoImage.BackColor = New_BackColor
    PropertyChanged "BackColor"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=SaveNextImage,SaveNextImage,-1,ForeColor
Public Property Get ForeColor() As OLE_COLOR
Attribute ForeColor.VB_Description = "Gibt die Vordergrundfarbe zurück, die zum Anzeigen von Text und Grafiken in einem Objekt verwendet wird, oder legt diese fest."
    ForeColor = SaveNextImage.ForeColor
End Property

Public Property Let ForeColor(ByVal New_ForeColor As OLE_COLOR)
    SaveNextImage.ForeColor = New_ForeColor
    SaveThisImage.ForeColor = New_ForeColor
    SaveNoImage.ForeColor = New_ForeColor
    PropertyChanged "ForeColor"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=UserControl,UserControl,-1,Enabled
Public Property Get Enabled() As Boolean
Attribute Enabled.VB_Description = "Gibt einen Wert zurück, der bestimmt, ob ein Objekt auf vom Benutzer erzeugte Ereignisse reagieren kann, oder legt diesen fest."
    Enabled = UserControl.Enabled
End Property

Public Property Let Enabled(ByVal New_Enabled As Boolean)
    UserControl.Enabled = New_Enabled
    SaveNextImage.Enabled = New_Enabled
    SaveThisImage.Enabled = New_Enabled
    SaveNoImage.Enabled = New_Enabled
    
    PropertyChanged "Enabled"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MappingInfo=SaveNextImage,SaveNextImage,-1,Font
Public Property Get Font() As Font
Attribute Font.VB_Description = "Gibt ein Font-Objekt zurück."
Attribute Font.VB_UserMemId = -512
    Set Font = SaveNextImage.Font
End Property

Public Property Set Font(ByVal New_Font As Font)
    Set SaveNextImage.Font = New_Font
    Set SaveThisImage.Font = New_Font
    Set SaveNoImage.Font = New_Font

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
    PropertyChanged "BackStyle"
End Property

'ACHTUNG! DIE FOLGENDEN KOMMENTIERTEN ZEILEN NICHT ENTFERNEN ODER VERÄNDERN!
'MemberInfo=0,0,0,0
Public Property Get value() As SIC_SaveDataConstants
Attribute value.VB_Description = "Gibt den Wert eines Objekts zurück oder legt diesen fest."
    value = m_Value
End Property

Public Property Let value(ByVal New_Value As SIC_SaveDataConstants)
    If m_Value = New_Value Then Exit Property
    Select Case New_Value
        Case SICSaveNone: SaveNoImage.value = True
        Case SICSaveNext: SaveNextImage.value = True
        Case SICSaveThis: SaveThisImage.value = True
    End Select
    m_Value = New_Value
    RaiseEvent Change
    RaiseEvent Click
    PropertyChanged "Value"
End Property

Private Sub SaveNextImage_Click()
    value = SICSaveNext
End Sub

Private Sub SaveNoImage_Click()
    value = SICSaveNone
End Sub

Private Sub SaveThisImage_Click()
    value = SICSaveThis
End Sub

'Eigenschaften für Benutzersteuerelement initialisieren
Private Sub UserControl_InitProperties()
    m_Value = m_def_Value
End Sub

'Eigenschaftenwerte vom Speicher laden
Private Sub UserControl_ReadProperties(PropBag As PropertyBag)

    SaveNextImage.BackColor = PropBag.ReadProperty("BackColor", &H8000000F)
    SaveNextImage.ForeColor = PropBag.ReadProperty("ForeColor", &H80000012)
    UserControl.Enabled = PropBag.ReadProperty("Enabled", True)
    Set SaveNextImage.Font = PropBag.ReadProperty("Font", Ambient.Font)
    UserControl.BackStyle = PropBag.ReadProperty("BackStyle", 1)
    m_Value = PropBag.ReadProperty("Value", m_def_Value)
End Sub

Private Sub UserControl_Resize()
    If UserControl.width < 1155 Then UserControl.width = 1155
    UserControl.Height = 1050
    SaveNextImage.width = UserControl.width - (1155 - 1095)
    SaveThisImage.width = UserControl.width - (1155 - 1095)
    SaveNoImage.width = UserControl.width - (1155 - 1095)
    
End Sub

'Eigenschaftenwerte in den Speicher schreiben
Private Sub UserControl_WriteProperties(PropBag As PropertyBag)

    Call PropBag.WriteProperty("BackColor", SaveNextImage.BackColor, &H8000000F)
    Call PropBag.WriteProperty("ForeColor", SaveNextImage.ForeColor, &H80000012)
    Call PropBag.WriteProperty("Enabled", UserControl.Enabled, True)
    Call PropBag.WriteProperty("Font", SaveNextImage.Font, Ambient.Font)
    Call PropBag.WriteProperty("BackStyle", UserControl.BackStyle, 1)
    Call PropBag.WriteProperty("Value", m_Value, m_def_Value)
End Sub

