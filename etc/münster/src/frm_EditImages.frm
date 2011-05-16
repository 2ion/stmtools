VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Begin VB.Form frm_EditImages 
   Caption         =   "Schul - STM  --  Bildbearbeitung"
   ClientHeight    =   8835
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   3870
   LinkTopic       =   "Form1"
   ScaleHeight     =   8835
   ScaleWidth      =   3870
   Begin TabDlg.SSTab Tabulator 
      Height          =   7935
      Left            =   0
      TabIndex        =   1
      Top             =   0
      Width           =   3855
      _ExtentX        =   6800
      _ExtentY        =   13996
      _Version        =   393216
      Tab             =   1
      TabHeight       =   520
      TabCaption(0)   =   "Datei"
      TabPicture(0)   =   "frm_EditImages.frx":0000
      Tab(0).ControlEnabled=   0   'False
      Tab(0).Control(0)=   "ShowImage"
      Tab(0).Control(1)=   "FileComment"
      Tab(0).Control(2)=   "Files"
      Tab(0).Control(3)=   "Drives"
      Tab(0).Control(4)=   "Dirs"
      Tab(0).ControlCount=   5
      TabCaption(1)   =   "Tools"
      TabPicture(1)   =   "frm_EditImages.frx":001C
      Tab(1).ControlEnabled=   -1  'True
      Tab(1).Control(0)=   "Image1"
      Tab(1).Control(0).Enabled=   0   'False
      Tab(1).Control(1)=   "Image2"
      Tab(1).Control(1).Enabled=   0   'False
      Tab(1).Control(2)=   "RowColNr"
      Tab(1).Control(2).Enabled=   0   'False
      Tab(1).Control(3)=   "SaveImage"
      Tab(1).Control(3).Enabled=   0   'False
      Tab(1).Control(4)=   "RePaintImage"
      Tab(1).Control(4).Enabled=   0   'False
      Tab(1).Control(5)=   "HideImage"
      Tab(1).Control(5).Enabled=   0   'False
      Tab(1).Control(6)=   "Scale_Frame"
      Tab(1).Control(6).Enabled=   0   'False
      Tab(1).Control(7)=   "ReloadImage"
      Tab(1).Control(7).Enabled=   0   'False
      Tab(1).Control(8)=   "SaveSTMData"
      Tab(1).Control(8).Enabled=   0   'False
      Tab(1).Control(9)=   "Cdlg"
      Tab(1).Control(9).Enabled=   0   'False
      Tab(1).Control(10)=   "ShowLineScan"
      Tab(1).Control(10).Enabled=   0   'False
      Tab(1).Control(11)=   "LineForLineScan"
      Tab(1).Control(11).Enabled=   0   'False
      Tab(1).Control(12)=   "SwitchZeileSpalte"
      Tab(1).Control(12).Enabled=   0   'False
      Tab(1).Control(13)=   "Frame1"
      Tab(1).Control(13).Enabled=   0   'False
      Tab(1).ControlCount=   14
      TabCaption(2)   =   "Manipulation"
      TabPicture(2)   =   "frm_EditImages.frx":0038
      Tab(2).ControlEnabled=   0   'False
      Tab(2).Control(0)=   "ReduceLine"
      Tab(2).Control(1)=   "FlattenData"
      Tab(2).Control(2)=   "DatenLogarithmieren"
      Tab(2).Control(3)=   "SmoothData"
      Tab(2).ControlCount=   4
      Begin VB.Frame Frame1 
         Caption         =   "Auflösung"
         Height          =   735
         Left            =   120
         TabIndex        =   29
         Top             =   5280
         Width           =   3615
         Begin VB.OptionButton res 
            Caption         =   "512"
            Height          =   375
            Index           =   512
            Left            =   2640
            TabIndex        =   32
            Top             =   240
            Width           =   855
         End
         Begin VB.OptionButton res 
            Caption         =   "256"
            Height          =   375
            Index           =   256
            Left            =   1320
            TabIndex        =   31
            Top             =   240
            Width           =   855
         End
         Begin VB.OptionButton res 
            Caption         =   "128"
            Height          =   375
            Index           =   128
            Left            =   120
            TabIndex        =   30
            Top             =   240
            Width           =   855
         End
      End
      Begin VB.CommandButton ReduceLine 
         Caption         =   "Linie abziehen"
         Height          =   372
         Left            =   -74880
         TabIndex        =   27
         Top             =   1920
         Width           =   3612
      End
      Begin VB.CommandButton FlattenData 
         Caption         =   "Ebene abziehen"
         Height          =   375
         Left            =   -74880
         TabIndex        =   26
         Top             =   1440
         Width           =   3612
      End
      Begin VB.CommandButton DatenLogarithmieren 
         Caption         =   "Daten logarithmieren"
         Height          =   312
         Left            =   -74880
         TabIndex        =   25
         Top             =   960
         Width           =   3612
      End
      Begin VB.CommandButton SmoothData 
         Caption         =   "Daten glätten"
         Height          =   375
         Left            =   -74880
         TabIndex        =   24
         Top             =   480
         Width           =   3615
      End
      Begin VB.CommandButton SwitchZeileSpalte 
         Caption         =   "Spalte"
         Height          =   345
         Left            =   1200
         TabIndex        =   22
         Top             =   2760
         Width           =   612
      End
      Begin VB.HScrollBar LineForLineScan 
         Height          =   195
         LargeChange     =   10
         Left            =   1860
         Max             =   128
         Min             =   1
         TabIndex        =   21
         Top             =   3000
         Value           =   1
         Width           =   1875
      End
      Begin VB.CheckBox ShowLineScan 
         Caption         =   "LineScan :"
         Height          =   312
         Left            =   120
         TabIndex        =   20
         Top             =   2760
         Width           =   1212
      End
      Begin MSComDlg.CommonDialog Cdlg 
         Left            =   3240
         Top             =   7320
         _ExtentX        =   847
         _ExtentY        =   847
         _Version        =   393216
      End
      Begin VB.CommandButton SaveSTMData 
         Caption         =   "Als STM-Datenfile speichern"
         Height          =   492
         Left            =   1980
         Style           =   1  'Grafisch
         TabIndex        =   15
         Top             =   3840
         Width           =   1752
      End
      Begin VB.CommandButton ReloadImage 
         Caption         =   "Bild erneut einladen / Änderungen verwerfen"
         Height          =   375
         Left            =   120
         TabIndex        =   14
         Top             =   4440
         Width           =   3615
      End
      Begin VB.Frame Scale_Frame 
         Caption         =   "Skala abändern"
         Height          =   2055
         Left            =   240
         TabIndex        =   10
         Top             =   480
         Width           =   3375
         Begin SchulSTMKlassen.SngScrollControl MinScaleScroll 
            Height          =   252
            Left            =   120
            TabIndex        =   19
            Top             =   600
            Width           =   3132
            _ExtentX        =   5530
            _ExtentY        =   450
            LargeChange     =   500
            Max             =   32767
            Min             =   0
            SmallChange     =   10
         End
         Begin SchulSTMKlassen.SngScrollControl MaxScaleScroll 
            Height          =   252
            Left            =   120
            TabIndex        =   18
            Top             =   1200
            Width           =   3132
            _ExtentX        =   5530
            _ExtentY        =   450
            LargeChange     =   500
            Max             =   32767
            Min             =   0
            SmallChange     =   10
         End
         Begin VB.CommandButton OptScaleSetting 
            Caption         =   "Optimale Skalenwerte"
            Height          =   375
            Left            =   120
            TabIndex        =   11
            Top             =   1560
            Width           =   3135
         End
         Begin VB.Label MaxScaleValue 
            Caption         =   "1024"
            Height          =   255
            Left            =   1680
            TabIndex        =   17
            Top             =   960
            Width           =   975
         End
         Begin VB.Label MinScaleValue 
            Caption         =   "0"
            Height          =   255
            Left            =   1680
            TabIndex        =   16
            Top             =   360
            Width           =   975
         End
         Begin VB.Label MinScaleLabel 
            Caption         =   "kleinster Skalenwert: "
            Height          =   255
            Left            =   120
            TabIndex        =   13
            Top             =   360
            Width           =   1815
         End
         Begin VB.Label MaxScaleLabel 
            Caption         =   "größter Skalenwert: "
            Height          =   255
            Left            =   120
            TabIndex        =   12
            Top             =   960
            Width           =   1815
         End
      End
      Begin VB.CommandButton HideImage 
         Caption         =   "Bild ausblenden"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   312
         Left            =   120
         Style           =   1  'Grafisch
         TabIndex        =   9
         Top             =   4920
         Width           =   3612
      End
      Begin VB.CommandButton RePaintImage 
         Caption         =   "Bild aktualisieren"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   120
         TabIndex        =   8
         Top             =   3360
         Width           =   3615
      End
      Begin VB.CommandButton SaveImage 
         Caption         =   "Als BMP speichern"
         Height          =   492
         Left            =   120
         TabIndex        =   7
         Top             =   3840
         Width           =   1752
      End
      Begin VB.CommandButton ShowImage 
         Caption         =   "Bild anzeigen"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Left            =   -74880
         TabIndex        =   6
         Top             =   7320
         Width           =   3615
      End
      Begin VB.TextBox FileComment 
         Height          =   645
         Left            =   -74880
         Locked          =   -1  'True
         TabIndex        =   5
         Top             =   6600
         Width           =   3615
      End
      Begin VB.FileListBox Files 
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   3015
         Left            =   -74880
         TabIndex        =   4
         Top             =   3540
         Width           =   3615
      End
      Begin VB.DriveListBox Drives 
         Height          =   315
         Left            =   -74880
         TabIndex        =   3
         Top             =   3060
         Width           =   3615
      End
      Begin VB.DirListBox Dirs 
         Height          =   2115
         Left            =   -74880
         TabIndex        =   2
         Top             =   900
         Width           =   3615
      End
      Begin VB.Label RowColNr 
         Caption         =   "512 anzeigen"
         Height          =   315
         Left            =   2280
         TabIndex        =   23
         Top             =   2760
         Width           =   1155
      End
      Begin VB.Image Image2 
         Height          =   735
         Left            =   480
         Picture         =   "frm_EditImages.frx":0054
         Stretch         =   -1  'True
         Top             =   7080
         Width           =   1410
      End
      Begin VB.Image Image1 
         Height          =   1695
         Left            =   1440
         Picture         =   "frm_EditImages.frx":1712
         Stretch         =   -1  'True
         Top             =   6120
         Width           =   1860
      End
   End
   Begin VB.CommandButton quit 
      Caption         =   "zurück zum Hauptfenster"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   0
      TabIndex        =   0
      Top             =   8160
      Width           =   3855
   End
   Begin ComctlLib.ProgressBar Progress 
      Height          =   135
      Left            =   0
      TabIndex        =   28
      Top             =   7995
      Visible         =   0   'False
      Width           =   3855
      _ExtentX        =   6800
      _ExtentY        =   238
      _Version        =   327682
      Appearance      =   1
      Max             =   1
   End
End
Attribute VB_Name = "frm_EditImages"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private Const ScaleStep = 0.01
Private WithEvents STMImage As CEdit_STM_Image
Attribute STMImage.VB_VarHelpID = -1




' ***********************************************************************************
' ****************************     FORM - METHODEN     ******************************
' ***********************************************************************************


Private Sub Form_Initialize()
End Sub

Private Sub Form_Terminate()
    Set STMImage = Nothing
End Sub

Private Sub Form_Load()
    Me.Icon = Main.Icon
    If STMImage Is Nothing Then Set STMImage = New CEdit_STM_Image
    STMImage.STMFilesDirectory = Main.Image_Path
    
    Files.Pattern = "*" & FileExt
    Dirs.path = Main.Image_Path
    Files.path = Dirs.path
    LineForLineScan = 1
  
            
    Tabulator.Tab = 0
    Tabulator.TabEnabled(1) = False
    Tabulator.TabEnabled(2) = False
    ResetScrollControls
End Sub

Private Sub Form_Unload(Cancel As Integer)
    STMImage.Hide
    Main.Show
End Sub


Private Sub res_Click(Index As Integer)
    STMImage.Hide
    STMImage.Resolution = Index
    STMImage.Show
    If Me.LineForLineScan.value > Index Then Me.LineForLineScan.value = Index \ 2
    Me.LineForLineScan.max = Index
End Sub

Private Sub ShowLineScan_Click()
    If ShowLineScan Then
        LineForLineScan_Change
    Else
        STMImage.HideLineScan
    End If
End Sub

Private Sub LineForLineScan_Change()
    RowColNr.Caption = CStr(LineForLineScan) & " anzeigen"
    If SwitchZeileSpalte.Caption = "Zeile" Then
        If ShowLineScan Then STMImage.ShowLineScanZeile LineForLineScan
    Else
        If ShowLineScan Then STMImage.ShowLineScanSpalte LineForLineScan
    End If
End Sub

Private Sub SwitchZeileSpalte_Click()
    If SwitchZeileSpalte.Caption = "Zeile" Then
        SwitchZeileSpalte.Caption = "Spalte"
    Else
        SwitchZeileSpalte.Caption = "Zeile"
    End If
    LineForLineScan_Change
End Sub

' ***********************************************************************************
' ************************      BUTTON -  METHODEN  - TAB datei     *****************
' ***********************************************************************************

Private Sub quit_Click()
    Unload Me
End Sub



Private Sub ShowImage_Click()
    If Files.ListIndex = -1 Then
        Beep
        MsgBox "Sie müssen zuerst eine STM-Daten-Datei auswählen", vbCritical + vbOK
        Exit Sub
    End If
    Tabulator.TabEnabled(1) = True
    Tabulator.TabEnabled(2) = True
    Tabulator.Tab = 1
    STMImage.ResetScale
    STMImage.Show
End Sub




' ***********************************************************************************
' ************************      BUTTON -  METHODEN  - TAB tools     *****************
' ***********************************************************************************


Private Sub SmoothData_Click()
    STMImage.SmoothData
End Sub

Private Sub RePaintImage_Click()
    STMImage.ImageScale.SetScaleValues MinScaleScroll.value, MaxScaleScroll.value
End Sub

Private Sub OptScaleSetting_Click()
    STMImage.OptimizeScale 0.8
End Sub

Private Sub DatenLogarithmieren_Click()
    STMImage.LnData 0.8
End Sub

Private Sub ReduceLine_Click()
    STMImage.SubtractLine 0.8
End Sub

Private Sub FlattenData_Click()
    STMImage.FlattenData 0.8
End Sub

Private Sub MinScaleScroll_Change()
    MaxScaleScroll.min = MinScaleScroll.value + ScaleStep
    MinScaleValue.Caption = Format(MinScaleScroll.value, "0.00 "" nA""")
End Sub
Private Sub MaxScaleScroll_Change()
    MinScaleScroll.max = MaxScaleScroll.value - ScaleStep
    MaxScaleValue.Caption = Format(MaxScaleScroll.value, "0.00 "" nA""")
End Sub

Private Sub ReloadImage_Click()
    STMImage.ReloadData
    STMImage.ResetScale
    STMImage.Show
End Sub

Private Sub HideImage_Click()
    Tabulator.Tab = 0
    Tabulator.TabEnabled(1) = False
    STMImage.Hide
End Sub

Private Sub SaveImage_Click()
    Set STMImage.CommonDialogControl = Me.Cdlg
    STMImage.STMFilesDirectory = Dirs.path
    STMImage.SaveBMPImage
End Sub


Private Sub SaveSTMData_Click()
    Set STMImage.CommonDialogControl = Me.Cdlg
    STMImage.STMFilesDirectory = Dirs.path
    STMImage.SaveSTMData
End Sub

' ***********************************************************************************
' ****************************     FILE - METHODEN       ****************************
' ***********************************************************************************

Private Function SelectedFile() As String
    Dim pfad As String
    pfad = Dirs.path
    If Right(pfad, 1) <> "\" Then pfad = pfad & "\"
    SelectedFile = pfad + Files.Filename
End Function

Private Sub Dirs_Change()
    Files.path = Dirs.path
End Sub

Private Sub Drives_Change()
    Dirs.path = Drives.Drive
End Sub

Private Sub Files_Click()
    STMImage.LoadSTMData SelectedFile()
    Select Case STMImage.MaxResolution
        Case 128: res(128).Enabled = True: res(256).Enabled = False: res(512).Enabled = False
        Case 256: res(128).Enabled = True: res(256).Enabled = True: res(512).Enabled = False
        Case 512: res(128).Enabled = True: res(256).Enabled = True: res(512).Enabled = True
    End Select
    res(128).value = True
    FileComment.text = STMImage.SampleInfo
End Sub

Private Sub Files_DblClick()
    ShowImage_Click
End Sub


' ***********************************************************************************
' ****************************         METHODEN        ******************************
' ***********************************************************************************



Private Sub ResetScrollControls()
    MinScaleScroll.min = STMImage.ADInfo.MinInputVoltage
    MinScaleScroll.max = STMImage.ADInfo.MaxInputVoltage - ScaleStep
    MinScaleScroll.value = STMImage.ADInfo.MinInputVoltage
    
    MaxScaleScroll.min = STMImage.ADInfo.MinInputVoltage + ScaleStep
    MaxScaleScroll.max = STMImage.ADInfo.MaxInputVoltage
    MaxScaleScroll.value = STMImage.ADInfo.MaxInputVoltage
End Sub




' ***********************************************************************************
' ****************************     EVENT - HANDLING    ******************************
' ***********************************************************************************



Private Sub STMImage_DataManipulationStarted(ByVal typ As DataManipulationMethods)
    Progress.value = 0
    Progress.Visible = True
    
    Select Case typ
        Case DMM_OptimizeScale
        Case DMM_FlattenData
    End Select
    DoEvents
End Sub

Private Sub STMImage_DataManipulationProgress(ByVal typ As DataManipulationMethods, ByVal Percent As Single)
    Progress.value = Percent
    
    Select Case typ
        Case DMM_OptimizeScale
        Case DMM_FlattenData
    End Select
    DoEvents
End Sub

Private Sub STMImage_DataManipulationFinished(ByVal typ As DataManipulationMethods)
    Progress.Visible = False
    Progress.value = 0
    Select Case typ
        Case DMM_OptimizeScale
            
        Case DMM_FlattenData
    End Select
    Beep
    STMImage.Show
    DoEvents
End Sub

Private Sub STMImage_ScaleHasChanged(ByVal AbsMin As Single, ByVal min As Single, ByVal max As Single, ByVal AbsMax As Single)
    ResetScrollControls
    MinScaleScroll.min = AbsMin
    MinScaleScroll.value = min
    MinScaleScroll.max = max - ScaleStep
    MaxScaleScroll.min = min + ScaleStep
    MaxScaleScroll.value = max
    MaxScaleScroll.max = AbsMax
    
'    MinScaleScroll.Min = STMImage.ADInfo.MinInputVoltage
'    MinScaleScroll.value = MinScaleValue
'    MinScaleScroll.Max = MaxScaleValue - ScaleStep
    
'    MaxScaleScroll.value = MaxScaleValue
'    MaxScaleScroll.Min = MinScaleValue + ScaleStep
'    MaxScaleScroll.Max = STMImage.ADInfo.MaxInputVoltage
End Sub
