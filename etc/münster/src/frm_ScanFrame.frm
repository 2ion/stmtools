VERSION 5.00
Begin VB.Form frm_ScanFrame 
   BorderStyle     =   4  'Festes Werkzeugfenster
   Caption         =   "Schul-STM"
   ClientHeight    =   9525
   ClientLeft      =   225
   ClientTop       =   480
   ClientWidth     =   3450
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   635
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   230
   Begin VB.Frame ScanFrequenzFrame 
      Caption         =   "Scangeschwindigkeit"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   120
      TabIndex        =   19
      Top             =   1080
      Width           =   3255
      Begin VB.HScrollBar DelayPerPixel 
         Height          =   255
         LargeChange     =   1000
         Left            =   120
         Max             =   32000
         Min             =   -32000
         SmallChange     =   100
         TabIndex        =   20
         Top             =   240
         Value           =   -30000
         Width           =   2175
      End
      Begin VB.Label Scangeschwindigkeit 
         Alignment       =   1  'Rechts
         Caption         =   "? Hz"
         Height          =   255
         Left            =   2160
         TabIndex        =   21
         Top             =   240
         Width           =   975
      End
   End
   Begin SchulSTMKlassen.ScanFrameOffsetControl ScanFrameOffset 
      Height          =   1110
      Left            =   120
      TabIndex        =   17
      Top             =   3960
      Width           =   3270
      _ExtentX        =   5768
      _ExtentY        =   1958
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Times New Roman"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ScanSize        =   400
   End
   Begin SchulSTMKlassen.ScanSizeControl ScanSize 
      Height          =   1380
      Left            =   120
      TabIndex        =   16
      Top             =   1800
      Width           =   3285
      _ExtentX        =   5794
      _ExtentY        =   2434
      Caption         =   "Größe des Scanbereichs"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      SmallChange     =   1
      Value           =   400
      Min             =   0
   End
   Begin VB.Timer ExecuteToggleScan 
      Interval        =   100
      Left            =   3000
      Top             =   8280
   End
   Begin VB.CheckBox FitScaleToFirstLine 
      Caption         =   "Skala an die erste Zeile anpassen"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   360
      TabIndex        =   14
      Top             =   7500
      Width           =   3135
   End
   Begin VB.CheckBox ToggleScan 
      Caption         =   "Scan starten"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   21.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000C0&
      Height          =   735
      Left            =   120
      Style           =   1  'Grafisch
      TabIndex        =   13
      Top             =   8040
      Width           =   3135
   End
   Begin VB.Frame ScanDirectionFrame 
      Caption         =   "Scanrichtung"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Left            =   120
      TabIndex        =   9
      Top             =   120
      Width           =   3255
      Begin VB.OptionButton Scan_from_Left_to_Right 
         Caption         =   "von links"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   120
         TabIndex        =   12
         Top             =   240
         Value           =   -1  'True
         Width           =   1095
      End
      Begin VB.OptionButton Scan_from_Right_to_Left 
         Alignment       =   1  'Rechts ausgerichtet
         Caption         =   "von rechts"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   1920
         TabIndex        =   11
         Top             =   240
         Width           =   1095
      End
      Begin VB.OptionButton Scan_from_Both_Directions 
         Caption         =   "Bidirektional"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   840
         TabIndex        =   10
         Top             =   480
         Width           =   1335
      End
   End
   Begin VB.Frame PPL_Frame 
      Caption         =   "Auflösung"
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
      Top             =   3240
      Width           =   3255
      Begin VB.OptionButton Opt_PPL 
         Caption         =   "128"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   300
         Index           =   128
         Left            =   480
         TabIndex        =   8
         Top             =   240
         Value           =   -1  'True
         Width           =   735
      End
      Begin VB.OptionButton Opt_PPL 
         Caption         =   "256"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   300
         Index           =   256
         Left            =   1200
         TabIndex        =   7
         Top             =   240
         Width           =   615
      End
      Begin VB.OptionButton Opt_PPL 
         Caption         =   "512"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   300
         Index           =   512
         Left            =   1920
         TabIndex        =   6
         Top             =   240
         Width           =   735
      End
      Begin VB.Label Label3 
         Alignment       =   2  'Zentriert
         Caption         =   "(Punkte pro Linie)"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   1200
         TabIndex        =   15
         Top             =   0
         Width           =   1335
      End
   End
   Begin VB.CheckBox ShowLineScan 
      Caption         =   "LineScan sichtbar"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   360
      TabIndex        =   4
      Top             =   7200
      Width           =   2295
   End
   Begin VB.Frame Frame1 
      Caption         =   "Bilder speichern"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1935
      Left            =   120
      TabIndex        =   0
      Top             =   5160
      Width           =   3255
      Begin SchulSTMKlassen.SaveImageControl SaveImage 
         Height          =   1050
         Left            =   120
         TabIndex        =   18
         Top             =   360
         Width           =   3075
         _extentx        =   5318
         _extenty        =   1852
         font            =   "frm_ScanFrame.frx":0000
      End
      Begin VB.CommandButton SaveNow 
         Caption         =   "Aktuelles Bild sofort speichern"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   120
         TabIndex        =   1
         Top             =   1440
         Width           =   3015
      End
   End
   Begin VB.Label Label2 
      Caption         =   "© Arbeitsgruppe Prof. Fuchs"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   252
      Left            =   0
      TabIndex        =   3
      Top             =   8820
      Width           =   3252
   End
   Begin VB.Label Label1 
      Caption         =   "Westfälische Wilhelms-Universtität Münster, Physikalisches Insitut"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   492
      Left            =   240
      TabIndex        =   2
      Top             =   9060
      Width           =   3132
   End
   Begin VB.Menu mnu_ToggleScan 
      Caption         =   "&Scan starten"
   End
   Begin VB.Menu mnu_options 
      Caption         =   "&Optionen"
      Begin VB.Menu mnu_lnData 
         Caption         =   "Eingang &logarithmieren"
      End
      Begin VB.Menu mnu_CenterFrame 
         Caption         =   "Scanfenster &zentrieren"
      End
      Begin VB.Menu mnu_sw 
         Caption         =   "Scan&Winkel"
         Begin VB.Menu mnu_ScanAngle 
            Caption         =   "&0°"
            Index           =   0
         End
         Begin VB.Menu mnu_ScanAngle 
            Caption         =   "&45°"
            Index           =   45
         End
         Begin VB.Menu mnu_ScanAngle 
            Caption         =   "&90°"
            Index           =   90
         End
      End
      Begin VB.Menu mnu_TopScanSize 
         Caption         =   "Scan&bereich"
         Begin VB.Menu mnu_ScanSize 
            Caption         =   "    &1nm ×     1nm"
            Index           =   1
         End
         Begin VB.Menu mnu_ScanSize 
            Caption         =   "    &2nm ×     2nm"
            Index           =   2
         End
         Begin VB.Menu mnu_ScanSize 
            Caption         =   "    &4nm ×     4nm"
            Index           =   4
         End
         Begin VB.Menu mnu_ScanSize 
            Caption         =   "    &8nm ×     8nm"
            Index           =   8
         End
         Begin VB.Menu mnu_ScanSize 
            Caption         =   "  &10nm ×   10nm"
            Index           =   10
         End
         Begin VB.Menu mnu_ScanSize 
            Caption         =   "  &20nm ×   20nm"
            Index           =   20
         End
         Begin VB.Menu mnu_ScanSize 
            Caption         =   "  &30nm ×   30nm"
            Index           =   30
         End
         Begin VB.Menu mnu_ScanSize 
            Caption         =   "  &40nm ×   40nm"
            Index           =   40
         End
         Begin VB.Menu mnu_ScanSize 
            Caption         =   "  &50nm ×   50nm"
            Index           =   50
         End
         Begin VB.Menu mnu_ScanSize 
            Caption         =   "&100nm × 100nm"
            Index           =   100
         End
         Begin VB.Menu mnu_ScanSize 
            Caption         =   "&150nm × 150nm"
            Index           =   150
            Visible         =   0   'False
         End
         Begin VB.Menu mnu_ScanSize 
            Caption         =   "&200nm × 200nm"
            Index           =   200
            Visible         =   0   'False
         End
         Begin VB.Menu mnu_ScanSize 
            Caption         =   "&250nm × 250nm"
            Index           =   250
            Visible         =   0   'False
         End
         Begin VB.Menu mnu_ScanSize 
            Caption         =   "&300nm × 300nm"
            Index           =   300
            Visible         =   0   'False
         End
         Begin VB.Menu mnu_ScanSize 
            Caption         =   "&350nm × 350nm"
            Index           =   350
            Visible         =   0   'False
         End
      End
      Begin VB.Menu mnu_AD 
         Caption         =   "&AD"
         Begin VB.Menu mnu_VoltageRange 
            Caption         =   "-1.25V bis 1.25V"
            Index           =   1
         End
         Begin VB.Menu mnu_VoltageRange 
            Caption         =   "-2.5V bis 2.5V"
            Index           =   2
         End
         Begin VB.Menu mnu_VoltageRange 
            Caption         =   "-5V bis 5V"
            Index           =   5
         End
         Begin VB.Menu mnu_VoltageRange 
            Caption         =   "-10V bis 10V"
            Index           =   10
         End
      End
   End
   Begin VB.Menu mnu_exit 
      Caption         =   "&Exit"
      NegotiatePosition=   1  'Links
   End
End
Attribute VB_Name = "frm_ScanFrame"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit


Private WithEvents ScanImage As CScan_STM_Image
Attribute ScanImage.VB_VarHelpID = -1





' =================================================================================
' ===============================    METHODEN     =================================
' =================================================================================



' ********************************************    FORM


Private Sub Form_Initialize()
#If ME300 Or PC20TR Then
    mnu_AD.Enabled = True
#End If

End Sub

Private Sub Form_Load()
    Set ScanImage = Nothing
    Set ScanImage = New CScan_STM_Image
    ScanImage.DatafilePath = Main.Image_Path
    
    Me.Icon = Main.Icon
    ScanSize.min = 0
    ScanSize.max = 1
    ScanSize.max = Konstanten.MaxScanSize
    ScanFrameOffset.MaxScanSize = 1
    ScanFrameOffset.MaxScanSize = Konstanten.MaxScanSize
    mnu_ScanAngle_Click (0)
    
    #If ME300 Then
        mnu_VoltageRange_Click 10
    #End If
    #If PC20TR Then
        mnu_VoltageRange_Click 10
        Me.mnu_VoltageRange(1).Caption = "- 1V bis  1V"
        Me.mnu_VoltageRange(2).Caption = "- 2V bis  2V"
        Me.mnu_VoltageRange(5).Caption = "- 5V bis  5V"
        Me.mnu_VoltageRange(10).Caption = "-10V bis 10V"
    #End If
    
    Scan_from_Both_Directions.value = True
    mnu_ScanSize_Click 100
    ScanFrameOffset.CenterFrame
    Opt_PPL_Click 128
    SaveImage.value = SICSaveNone
    Me.ShowLineScan = False
    ScanImage.SampleInfo = Main.SampleInfo
    DelayPerPixel.value = DelayPerPixel.max
    DelayPerPixel.value = DelayPerPixel.min
    EnableInputFrames True
End Sub

Private Sub Form_Unload(Cancel As Integer)
    ScanImage.HideAll
    Set ScanImage = Nothing
    Main.Show
End Sub



Private Sub mnu_CenterFrame_Click()
    ScanFrameOffset.CenterFrame
End Sub

Private Sub mnu_exit_Click()
    Unload Me
End Sub


Private Sub mnu_lnData_Click()
    mnu_lnData.Checked = Not mnu_lnData.Checked
    ScanImage.LogarithmSignal = mnu_lnData.Checked
End Sub

Private Sub mnu_ScanAngle_Click(Index As Integer)
    mnu_ScanAngle(0).Checked = False
    mnu_ScanAngle(45).Checked = False
    mnu_ScanAngle(90).Checked = False
    mnu_ScanAngle(Index).Checked = True
    ScanImage.ScanAngle = Index
End Sub


Private Sub mnu_VoltageRange_Click(Index As Integer)
    mnu_VoltageRange(1).Checked = False
    mnu_VoltageRange(2).Checked = False
    mnu_VoltageRange(5).Checked = False
    mnu_VoltageRange(10).Checked = False
    mnu_VoltageRange(Index).Checked = True
    ScanImage.Tip.SetInputVoltageRange Index
End Sub



Private Sub DelayPerPixel_Change()
    ScanImage.DelayAfterPixel = DelayPerPixel
End Sub



' *********************************************** SCAN-DIRECTION

Private Sub Scan_from_Both_Directions_Click()
    ScanImage.ScanDirection = BothDirections
End Sub

Private Sub Scan_from_Left_to_Right_Click()
    ScanImage.ScanDirection = LeftToRight
End Sub

Private Sub Scan_from_Right_to_Left_Click()
    ScanImage.ScanDirection = 2 'RightToLeft
End Sub

' *********************************************** SCANSIZE

Private Sub mnu_ScanSize_Click(Index As Integer)
    ScanSize.value = Index
End Sub


Private Sub ScanFrameOffset_Change()
    ScanImage.XOffset = ScanFrameOffset.x
    ScanImage.YOffset = ScanFrameOffset.y
End Sub


Private Sub ScanSize_Change()
    ScanFrameOffset.ScanSize = ScanSize.value
    ScanImage.ScanSize = ScanSize.value
End Sub


' *************************************************   SaveImage

Private Sub SaveImage_Change()
    ScanImage.SaveData = SaveImage.value
End Sub

Private Sub SaveNow_Click()
    ScanImage.SaveSTMData
End Sub


' *************************************************  TOGGLE-BUTTON


Private Sub ShowLineScan_Click()
    If ShowLineScan Then
        ScanImage.ShowLineScan
    Else
        ScanImage.HideLineScan
    End If
End Sub

Private Sub EnableInputFrames(enable As Boolean)
    ScanDirectionFrame.Enabled = True
    ScanSize.Enabled = True
    PPL_Frame.Enabled = True 'enable
    SaveNow.Enabled = Not enable
    ScanFrequenzFrame.Enabled = Not enable
End Sub

Private Sub ExecuteToggleScan_Timer()
    If ToggleScan = vbChecked Then
        EnableInputFrames False
        ExecuteToggleScan.Enabled = False
        ToggleScan.Caption = "Scan beenden"
        mnu_ToggleScan.Caption = "&Scan beenden"
        ScanImage.ShowImage
        ScanImage.StartScan
    End If
End Sub

Private Sub ToggleScan_Click()
    If ToggleScan = vbUnchecked Then
        ToggleScan.Caption = "Scan starten"
        mnu_ToggleScan.Caption = "&Scan starten"
        ScanImage.StopScan
        ScanImage.HideImage
        EnableInputFrames True
        ExecuteToggleScan.Enabled = True
    End If
    ' Else -->> ExecuteToggleScan
End Sub
Private Sub mnu_ToggleScan_Click()
    If ToggleScan = vbChecked Then
        ToggleScan = vbUnchecked
    Else
        ToggleScan = vbChecked
    End If
    ToggleScan_Click
End Sub

Private Sub Opt_PPL_Click(Index As Integer)
    ScanImage.Resolution = Index
End Sub

Private Sub FitScaleToFirstLine_Click()
    ScanImage.FitScaleToFirstLine = FitScaleToFirstLine
End Sub


' =================================================================================
' ===============================    EVENT  HANDLE    =================================
' =================================================================================


Private Sub ScanImage_DataSaved()
    SaveImage.value = ScanImage.SaveData
End Sub

Private Sub ScanImage_NewScanVelocity(ByVal t As Double)
    t = 1 / (t + 0.01)
    Scangeschwindigkeit.Caption = Format(t, "0.0 "" Hz""")
End Sub

