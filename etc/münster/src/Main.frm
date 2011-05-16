VERSION 5.00
Begin VB.Form Main 
   Caption         =   "Schul-STM"
   ClientHeight    =   6825
   ClientLeft      =   60
   ClientTop       =   630
   ClientWidth     =   7335
   Icon            =   "Main.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   6825
   ScaleWidth      =   7335
   Begin VB.Frame Frame2 
      Caption         =   "Verstärkung des Tunnelverstärkers"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   3960
      TabIndex        =   10
      Top             =   1080
      Width           =   3135
      Begin VB.TextBox OPV_Gain 
         Alignment       =   1  'Rechts
         Height          =   285
         Left            =   840
         TabIndex        =   12
         Text            =   "1,000"
         Top             =   240
         Width           =   855
      End
      Begin VB.Label Label1 
         Caption         =   "V/nA"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   1800
         TabIndex        =   11
         Top             =   240
         Width           =   615
      End
   End
   Begin VB.CommandButton EditImages 
      Caption         =   "Bild-&Bearbeitung"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   15.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Left            =   3960
      TabIndex        =   9
      Top             =   4560
      Width           =   3135
   End
   Begin VB.CommandButton quit 
      Caption         =   "Programm b&eenden"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   3960
      Style           =   1  'Grafisch
      TabIndex        =   8
      Top             =   5880
      Width           =   3135
   End
   Begin VB.CommandButton GrobAnnäherung 
      Caption         =   "Hilfe für die &Grobannäherung"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Left            =   3960
      Style           =   1  'Grafisch
      TabIndex        =   7
      Top             =   2160
      Width           =   3135
   End
   Begin VB.Frame Frame3 
      Caption         =   "Informationen zur Probe"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   120
      TabIndex        =   5
      Top             =   120
      Width           =   7095
      Begin VB.TextBox SampleInfo 
         Height          =   285
         Left            =   120
         TabIndex        =   6
         Text            =   "Geben Sie hier z.B. ""Graphit"" ein"
         Top             =   240
         Width           =   6495
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Verzeichnis der STM-Bilder:"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   5535
      Left            =   120
      TabIndex        =   2
      Top             =   960
      Width           =   3615
      Begin VB.DriveListBox DriveBox 
         Height          =   315
         Left            =   120
         TabIndex        =   4
         Top             =   360
         Width           =   3375
      End
      Begin VB.DirListBox Image_Path 
         Height          =   4815
         Left            =   120
         TabIndex        =   3
         Top             =   720
         Width           =   3375
      End
   End
   Begin VB.CommandButton FrameScan 
      Caption         =   "Bild &aufnehmen"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Left            =   3960
      TabIndex        =   1
      Top             =   3360
      Width           =   3135
   End
   Begin VB.Label Label2 
      Caption         =   "© Arbeitsgruppe Prof. Fuchs, Westfälische Wilhelms-Universtität Münster, Physikalisches Insitut"
      Height          =   255
      Left            =   0
      TabIndex        =   0
      Top             =   6600
      Width           =   11295
   End
   Begin VB.Menu mnu_top 
      Caption         =   "&Datei"
      Index           =   1
      Begin VB.Menu mnu_quit 
         Caption         =   "&Beenden"
      End
   End
   Begin VB.Menu Show_Info 
      Caption         =   "&Info"
      NegotiatePosition=   3  'Rechts
   End
End
Attribute VB_Name = "Main"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit


Private Sub Form_Activate()
''    Unload frm_ScanFrame
'    Unload frm_EditImages
End Sub

' ************************************************************************************
' ********************       FORM - METHODEN           *******************************
' ************************************************************************************

Private Sub Form_Initialize()
    Dim ed As String
    ed = GetSpecialFolder(CSIDL_PERSONAL)
    DriveBox.Drive = left(ed, 2)
    Image_Path.path = ed
    frm_StartUp.Show vbModal
End Sub

Private Sub Form_Unload(Cancel As Integer)
    End
End Sub


' ************************************************************************************
' ********************       MENÜ - METHODEN           *******************************
' ************************************************************************************

'Private Sub OPV_Gain_KeyDown(KeyCode As Integer, Shift As Integer)
'    Select Case KeyCode
'        Case vbKey0 To vbKey9, vbKeyNumpad0 To vbKeyNumpad9
'            Exit Sub
'        Case vbKeyBack, vbKeyDelete
'            Exit Sub
'        Case vbKeyDecimal
'        Case vbKeySeparator, vbKeyTab, vbKeyExecute
'            OPV_Gain = Format(CSng(OPV_Gain), "0.000")
'            Exit Sub
'        Case Else
'            'KeyCode = 0
'            MsgBox "Bitte nur Zahlen eingeben!"
'    End Select
'End Sub

Private Sub OPV_Gain_KeyPress(KeyAscii As Integer)
Dim dummy As Boolean
    Select Case KeyAscii
        Case Asc("0") To Asc("9")
            Exit Sub
        Case Asc(",")
            If InStr(OPV_Gain, ",") <> 0 Then KeyAscii = 0
        Case vbKeyBack, vbKeyReturn
            Exit Sub
        Case Else
            KeyAscii = 0
    End Select

End Sub

Private Sub OPV_Gain_LostFocus()
    Dim s As Single
    s = CSng(OPV_Gain)
    If s = 0 Then s = 1
    OPV_Gain = Format(s, "0.000")
End Sub
Private Sub OPV_Gain_Validate(Cancel As Boolean)
    OPV_Gain_LostFocus
End Sub


' ************************************************************************************
' ********************      BUTTON - METHODEN          *******************************
' ************************************************************************************

Private Sub GrobAnnäherung_Click()
    Me.ValidateControls
    frm_coarseApproach.Show vbModal
End Sub

Private Sub FrameScan_Click()
    Me.ValidateControls
    If Image_Path_is_Read_Only() Then
        Beep
        MsgBox "Das aktuelle Bild-Verzeichnis ist schreibgschützt!", vbCritical + vbOK
        Exit Sub
    End If
    
    Me.Hide
    frm_ScanFrame.Show
End Sub

Private Sub EditImages_Click()
    Me.ValidateControls
    If Image_Path_is_Read_Only() Then
        Beep
        MsgBox "Das aktuelle Bild-Verzeichnis ist schreibgschützt!", vbCritical + vbOK
        Exit Sub
    End If
    
    Me.Hide
    frm_EditImages.Show
End Sub



Private Sub quit_Click()
    'Beep
    Unload Me
End Sub

' ************************************************************************************
' ********************              METHODEN           *******************************
' ************************************************************************************



Private Sub DriveBox_Change()
    Image_Path.path = DriveBox.Drive
End Sub


Private Function Image_Path_is_Read_Only() As Boolean
    Dim Fname As String
    Fname = Main.Image_Path
    If Right(Fname, 1) <> "\" Then Fname = Fname & "\"
    Fname = Fname & "test.bmp"

    On Error GoTo test_path_error
    Open Fname For Output Access Write As 2
    Close 2
    Kill Fname
    Image_Path_is_Read_Only = False
    GoTo test_path_ende
    
test_path_error:
    Image_Path_is_Read_Only = True
test_path_ende:
    On Error GoTo 0
End Function

Private Sub Show_Info_Click()
    frmAbout.Show vbModal
End Sub
