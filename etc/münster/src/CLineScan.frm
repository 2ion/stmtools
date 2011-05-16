VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Begin VB.Form CLineScan 
   BorderStyle     =   4  'Festes Werkzeugfenster
   Caption         =   "LineScan"
   ClientHeight    =   1530
   ClientLeft      =   3885
   ClientTop       =   9015
   ClientWidth     =   4770
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   102
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   318
   Begin ComctlLib.Slider LinesPerView 
      Height          =   255
      Left            =   1080
      TabIndex        =   5
      Top             =   1215
      Width           =   2655
      _ExtentX        =   4683
      _ExtentY        =   450
      _Version        =   327682
      LargeChange     =   1
      Min             =   1
      Max             =   5
      SelStart        =   1
      Value           =   1
   End
   Begin VB.PictureBox Chart 
      Height          =   975
      Left            =   600
      ScaleHeight     =   61
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   252
      TabIndex        =   0
      Top             =   240
      Width           =   3840
   End
   Begin VB.Label yOrigin 
      Caption         =   "500nm"
      Height          =   255
      Left            =   0
      TabIndex        =   4
      Top             =   1080
      Width           =   495
   End
   Begin VB.Label Y_Axis 
      Caption         =   "500nm"
      Height          =   375
      Left            =   0
      TabIndex        =   3
      Top             =   120
      Width           =   495
   End
   Begin VB.Label x_Axis 
      Caption         =   "400 nm"
      Height          =   255
      Left            =   4080
      TabIndex        =   2
      Top             =   1320
      Width           =   735
   End
   Begin VB.Label xOrigin 
      Caption         =   "0 nm"
      Height          =   255
      Left            =   480
      TabIndex        =   1
      Top             =   1320
      Width           =   615
   End
End
Attribute VB_Name = "CLineScan"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private PPL As Long
Private SS As Long
Private MyScale As CScale
Private LinesShowed As Integer
Private ActLine As Integer

' ===============================================================================
' ========================       PROPERTIES           ===========================
' ===============================================================================

Friend Property Set ADInfo(ByVal newADInfo As CADInfo)
    Set MyScale.ADInfo = newADInfo
    Form_Paint
End Property
Friend Property Get ADInfo() As CADInfo
    Set ADInfo = MyScale.ADInfo
End Property


Friend Property Let Resolution(ByVal vdata As Long)
    PPL = vdata
    Resize_Form
End Property
Friend Property Get Resolution() As Long
    Resolution = PPL
End Property


Friend Property Let ScanSize(ByVal vdata As Long)
    SS = vdata
    Form_Paint
End Property
Friend Property Get ScanSize() As Long
    ScanSize = SS
End Property


Friend Property Set ImageScale(ByVal vdata As CScale)
    Set MyScale = vdata
    Form_Paint
End Property
Friend Property Get ImageScale() As CScale
    Set ImageScale = MyScale
End Property


' ===============================================================================
' ========================       METHODEN              ==========================
' ===============================================================================

Private Sub Form_Initialize()
    Set MyScale = New CScale
End Sub

Private Sub Form_Paint()
    x_Axis.Caption = CStr(SS) & " nm"
    yOrigin.Caption = MyScale.ScaleMinLabel
    Y_Axis.Caption = MyScale.ScaleMaxLabel
    Chart.ScaleHeight = MyScale.ScaleMaxValue - MyScale.ScaleMinValue
    Chart.ScaleTop = 0
End Sub

Private Sub Form_Terminate()
    Me.Hide
    Set MyScale = Nothing
End Sub


Private Sub Form_Load()
    Me.Icon = Main.Icon
    Resize_Form
    ActLine = 0
    LinesShowed = 0
End Sub

Private Sub Resize_Form()
    Me.width = ScaleX(PPL + 318 - 256, vbPixels, vbTwips)
    Chart.width = PPL
    x_Axis.left = PPL - 256 + 272
End Sub
Friend Sub DrawPoint(x As Long, y As Long, signal As Single)
    If y <> ActLine Then
        If LinesShowed = LinesPerView Then
            LinesShowed = 0
            Chart.Cls
        End If
        ActLine = y
        LinesShowed = LinesShowed + 1
        Chart.CurrentX = x: Chart.CurrentY = Chart.ScaleHeight \ 2
    End If
    Chart.Line Step(0, 0)-(x, MyScale.ScaleMaxValue - signal), QBColor(y Mod 5)
    'Chart.PSet (x, MyScale.ScaleMaxValue - signal), QBColor(y Mod 5)
End Sub
