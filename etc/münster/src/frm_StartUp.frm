VERSION 5.00
Begin VB.Form frm_StartUp 
   Caption         =   "Schul-STM"
   ClientHeight    =   4800
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6735
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4800
   ScaleWidth      =   6735
   StartUpPosition =   2  'Bildschirmmitte
   Begin VB.Timer Timer1 
      Interval        =   5000
      Left            =   4440
      Top             =   4080
   End
   Begin VB.Label Label1 
      Caption         =   " WDR, Quarks && Co."
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Index           =   3
      Left            =   240
      TabIndex        =   3
      Top             =   1920
      Width           =   2775
   End
   Begin VB.Image Image3 
      Height          =   3150
      Index           =   0
      Left            =   3120
      Picture         =   "frm_StartUp.frx":0000
      Stretch         =   -1  'True
      ToolTipText     =   "Arbeitskreis Prof. H. Fuchs"
      Top             =   1320
      Width           =   3420
   End
   Begin VB.Label Label1 
      Caption         =   " Arbeitskreis Professor H. Fuchs, Uni Münster"
      Height          =   375
      Index           =   2
      Left            =   240
      TabIndex        =   2
      Top             =   1680
      Width           =   3375
   End
   Begin VB.Label Label1 
      Caption         =   "Präsentiert von"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Index           =   1
      Left            =   120
      TabIndex        =   1
      Top             =   1320
      Width           =   3015
   End
   Begin VB.Image Image3 
      Height          =   1215
      Index           =   1
      Left            =   600
      Picture         =   "frm_StartUp.frx":3E47
      Stretch         =   -1  'True
      ToolTipText     =   "Westfälische Wilhelms-Universität Münster"
      Top             =   2400
      Width           =   2730
   End
   Begin VB.Image Image3 
      Height          =   1050
      Index           =   2
      Left            =   240
      Picture         =   "frm_StartUp.frx":5505
      Stretch         =   -1  'True
      ToolTipText     =   "WDR, Quarks & Co."
      Top             =   3600
      Width           =   3750
   End
   Begin VB.Line Line1 
      BorderWidth     =   2
      Index           =   1
      X1              =   120
      X2              =   6600
      Y1              =   1080
      Y2              =   1080
   End
   Begin VB.Line Line1 
      BorderWidth     =   2
      Index           =   0
      X1              =   120
      X2              =   6600
      Y1              =   960
      Y2              =   960
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Zentriert
      Caption         =   "Schul - STM"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   36
         Charset         =   0
         Weight          =   700
         Underline       =   -1  'True
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Index           =   0
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   6495
   End
End
Attribute VB_Name = "frm_StartUp"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Click()
    Unload Me
End Sub

Private Sub Form_KeyPress(KeyAscii As Integer)
    Unload Me
End Sub

Private Sub Image3_Click(Index As Integer)
    Unload Me
End Sub

Private Sub Label1_Click(Index As Integer)
    Unload Me
End Sub

Private Sub Timer1_Timer()
    Unload Me
End Sub
