VERSION 5.00
Begin VB.Form CSTM_Image 
   BackColor       =   &H00FFFFFF&
   BorderStyle     =   4  'Festes Werkzeugfenster
   Caption         =   "Schüler STM  --  Bild"
   ClientHeight    =   3195
   ClientLeft      =   4230
   ClientTop       =   285
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   213
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   312
End
Attribute VB_Name = "CSTM_Image"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

'==================================================================
' --------------------------     Events            ----------------
'==================================================================

Public Event ColormapHasChanged()
Public Event ScaleHasChanged(ByVal AbsMin As Single, ByVal min As Single, ByVal max As Single, ByVal AbsMax As Single)

'==================================================================
' ----------     Typen, Konstanten, Deklarationen      ------------
'==================================================================

Private Type TPoint
    x As Long
    y As Long
End Type

Private WithEvents MyScale As CScale
Attribute MyScale.VB_VarHelpID = -1
Private UserUnloadable As Boolean ' User Can Unload Form
Private PPL As Long 'PixelPerLine = Resolution
Private SS As Long 'ScanSize in nm
Private Comment As String 'SampleInfo
Private ImageOrigin As TPoint


'==================================================================
' -------------------------   Properties   ------------------------
'==================================================================

Friend Property Set ImageScale(ByVal vdata As CScale)
    Set MyScale = vdata
End Property
Friend Property Get ImageScale() As CScale
    Set ImageScale = MyScale
End Property

Friend Property Set ADInfo(new_ADInfo As CADInfo)
    Set MyScale.ADInfo = new_ADInfo
    If Me.Visible Then Form_Paint
End Property
Friend Property Get ADInfo() As CADInfo
    Set ADInfo = MyScale.ADInfo
End Property


Friend Property Let UserCanUnload(ByVal vdata As Boolean)
    UserUnloadable = vdata
End Property
Friend Property Get UserCanUnload() As Boolean
    UserCanUnload = UserUnloadable
End Property
Friend Property Let Resolution(ByVal PixelPerLine As Long)
    If PPL <> PixelPerLine Then Me.Cls
    PPL = PixelPerLine
End Property
Friend Property Get Resolution() As Long
    Resolution = PPL
End Property
Friend Property Let ScanSize(ByVal nm As Long)
    SS = nm
    If Me.Visible Then Form_Paint
End Property
Friend Property Get ScanSize() As Long
    ScanSize = SS
End Property
Friend Property Let SampleInfo(ByVal text As String)
    Comment = text
End Property
Friend Property Get SampleInfo() As String
    SampleInfo = Comment
End Property




' ***********************************************************************************
' ****************************      FORM - METHODEN    ******************************
' ***********************************************************************************


Private Sub Form_Initialize()
    Set MyScale = New CScale
    UserCanUnload = True
    ImageOrigin.x = 144: ImageOrigin.y = 24
    SS = 400
    PPL = 128
    Comment = ""
End Sub


Private Sub Form_Terminate()
    Me.Hide
    Set MyScale = Nothing
End Sub


Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
    Cancel = False
    If (UnloadMode = vbFormControlMenu) And (Not UserUnloadable) Then Cancel = True
End Sub

Private Sub Form_Size()
    Dim H As Long
    Dim W As Long
    W = ScaleX(PPL + 160, vbPixels, vbTwips)
    H = ScaleY(PPL + 110, vbPixels, vbTwips)
    If (H < ScaleY(390, vbPixels, vbTwips)) Then H = ScaleY(390, vbPixels, vbTwips)

    Me.width = W
    Me.Height = H
End Sub

Private Sub Form_Paint()
    Dim i As Long
    Dim factor As Double
    
    ' --------------------------    Resize Window ---------------------------------
    Form_Size
    
    ' --------------------------    Window Paint ----------------------------------
    WriteText 16, 0, "© Arbeitsgruppe Prof. Fuchs, WWU Münster"

    ' --------------- Skala erstellen
    WriteText 72, 56, MyScale.ScaleMaxLabel & "     ", True
    WriteText 72, 312, MyScale.ScaleMinLabel & "     ", True
    DrawBox 24, 64, 65, 64 + 257, vbBlack
    MyScale.DrawScale 25, 65, 40, Me
        
    
    
    ' ---------------- Image-Frame erstellen
    DrawBox ImageOrigin.x, ImageOrigin.y, (ImageOrigin.x + PPL + 1), (ImageOrigin.y + PPL + 1), vbBlack
    ' ---------------- Y-Achsen-Beschriftung
    
    WriteText ImageOrigin.x - 5 - TextWidth(CStr("   " & SS)), ImageOrigin.y, CStr("   " & SS), True
    WriteText ImageOrigin.x - 5 - TextWidth("nm"), ImageOrigin.y + TextHeight("400"), "nm"
    ' ---------------- X-Achsen-Beschriftung
    WriteText (ImageOrigin.x + 5 + PPL - TextWidth(CStr("   " & SS) & " nm")), (ImageOrigin.y + PPL + 5), CStr("   " & SS) & " nm", True
    ' ---------------- Origin-Beschriftung
    WriteText ImageOrigin.x - TextWidth("0 nm") \ 2, (ImageOrigin.y + PPL + 5), "0 nm"
    ' ---------------- Benutzer-Kommentar
    WriteText 16, Me.ScaleHeight - Me.TextHeight(SampleInfo) - 5, SampleInfo
End Sub




' ***********************************************************************************
' ****************************        METHODEN         ******************************
' ***********************************************************************************



Friend Sub RedrawScale()
    Form_Paint
End Sub

Friend Sub DrawPoint(ByVal x As Long, ByVal y As Long, ByVal signal As Single)
    PSet (ImageOrigin.x + x, ImageOrigin.y + y), MyScale.GetColor(signal)
End Sub

Private Sub DrawBox(x1 As Long, y1 As Long, x2 As Long, y2 As Long, color As Long, Optional ByVal cleaned As Boolean = False)
    Dim i As Long
    Line (x1, y1)-(x1, y2), color
    Line (x1, y2)-(x2, y2), color
    Line (x2, y2)-(x2, y1), color
    Line (x2, y1)-(x1, y1), color
    If cleaned Then
        If (x2 - x1) > (y2 - y1) Then
            For i = y1 To y2
                Line (x1 + 1, i)-(x2 - 1, i), vbWhite
            Next i
        Else
            For i = x1 To x2
                Line (i, y1 + 1)-(i, y2 - 1), vbWhite
            Next i
        End If
    End If
End Sub

Private Sub WriteText(ByVal x As Long, ByVal y As Long, ByVal t As String, Optional ByVal clean As Boolean = False)
    If clean Then
        DrawBox x, y, x + TextWidth(t), y + TextHeight(t), vbWhite, True
    End If
    CurrentX = x
    CurrentY = y
    Print t
End Sub




' ***********************************************************************************
' ****************************     EVENT - HANDLING    ******************************
' ***********************************************************************************


Private Sub MyScale_ColormapChanged()
    RaiseEvent ColormapHasChanged
End Sub

Private Sub myscale_ScaleHasChanged(ByVal AbsMin As Single, ByVal min As Single, ByVal max As Single, ByVal AbsMax As Single)
    RedrawScale
    RaiseEvent ScaleHasChanged(AbsMin, min, max, AbsMax)
End Sub
