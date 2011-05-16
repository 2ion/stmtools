VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Begin VB.Form frm_coarseApproach 
   Caption         =   "Schul-STM  --  Grob-Annäherung"
   ClientHeight    =   1665
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5310
   LinkTopic       =   "Form1"
   ScaleHeight     =   1665
   ScaleWidth      =   5310
   StartUpPosition =   1  'Fenstermitte
   Begin ComctlLib.ProgressBar CurrentBar 
      Height          =   375
      Left            =   120
      TabIndex        =   2
      Top             =   600
      Width           =   5175
      _ExtentX        =   9128
      _ExtentY        =   661
      _Version        =   327682
      BorderStyle     =   1
      Appearance      =   0
   End
   Begin VB.CommandButton ExitApproach 
      Caption         =   "beenden"
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
      Left            =   120
      TabIndex        =   0
      Top             =   1080
      Width           =   5175
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Zentriert
      Caption         =   "Diese Anzeige dient nur als Untestützung."
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000C0&
      Height          =   375
      Left            =   240
      TabIndex        =   1
      Top             =   120
      Width           =   4815
   End
End
Attribute VB_Name = "frm_coarseApproach"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim Exit_Form As Boolean
Dim Running As Boolean
Dim OldSoundState As Boolean

Dim STMTip As CSTM_Tip
Private Sub ExitApproach_Click()
    Exit_Form = True
End Sub

Private Sub Form_Activate()
    CurrentBar.min = 0
    CurrentBar.max = STMTip.MaxInputVoltage - STMTip.MinInputVoltage
    
    If Not Running Then
        Running = True
        While Not Exit_Form
            CurrentBar.value = STMTip.getSignal() - STMTip.MinInputVoltage
            DoEvents
        Wend
        Unload Me
    End If
End Sub

Private Sub Form_Load()
    Set STMTip = New CSTM_Tip
    Me.Icon = Main.Icon
    Exit_Form = False
    Running = False
    CurrentBar.value = 0
End Sub


Private Sub Form_Unload(Cancel As Integer)
    Set STMTip = Nothing
End Sub

