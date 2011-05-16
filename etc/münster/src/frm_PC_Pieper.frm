VERSION 5.00
Begin VB.Form frm_PC_Pieper 
   Caption         =   "Form1"
   ClientHeight    =   675
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   1560
   LinkTopic       =   "Form1"
   ScaleHeight     =   675
   ScaleWidth      =   1560
   StartUpPosition =   3  'Windows-Standard
   Visible         =   0   'False
End
Attribute VB_Name = "frm_PC_Pieper"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Load()
    PCTone1.ToneOn 300
    Sleep 150
    PCTone1.ToneOff
End Sub

Private Sub Form_Unload(Cancel As Integer)
    PCTone1.ToneOff
End Sub


