Attribute VB_Name = "MathModul"
Option Explicit

' Die folgenden Funktionen sind aus
'  William H. Press et al.:
'  Numerical Recipies, The Art of Science Computing (Fortran Version)
 ' Cambridge University Press
' entnommen

Private XT() As Single, YT() As Single
Private NData As Integer
Private aa As Double
Private LB As Integer, UB As Integer


Private Function sign(ByVal v1 As Double, ByVal v2 As Double)
    sign = Abs(v1) * Sgn(v2)
End Function

' Seite 231

Private Sub Sort(n As Integer, ra() As Double)
    Dim l As Integer, ir As Integer
    Dim i As Integer, j As Integer
    Dim rra As Double
    Dim help As Double
    l = n \ 2 + 1
    ir = n
    help = frm_EditImages.Progress.value
    Do
        If (l > 1) Then
            l = l - 1
            rra = ra(l)
        Else
            rra = ra(ir)
            ra(ir) = ra(1)
            ir = ir - 1
            If (ir = 1) Then
                ra(1) = rra
                Exit Do
            End If
        End If
        i = l
        j = l + l
        While (j <= ir)
            If (j > ir) Then
                If (ra(j) > ra(j + 1)) Then j = j + 1
            End If
            If (rra > ra(j)) Then
                ra(i) = ra(j)
                i = j
                j = j + 1
            Else
                j = ir + 1
            End If
        Wend
        ra(i) = rra
        frm_EditImages.Progress.value = ir / n
        DoEvents
    Loop
    frm_EditImages.Progress.value = help
End Sub




' Seite 554f


Private Function R0Func(b As Double, x() As Single, y() As Single) As Double
    Dim i As Integer
    Dim N1 As Double, d As Double
    Dim NML As Double, NMH As Double
    Dim arr() As Double, sum As Double
    
    ReDim arr(LB To UB)
    
    N1 = NData + 1
    NML = N1 / 2
    NMH = N1 - NML
    For i = LB To UB
        arr(i) = y(i) - b * x(i)
    Next i
    Call Sort(NData, arr())
    aa = 0.5 * (arr(NML) + arr(NMH))
    sum = 0#
    For i = LB To UB
        d = y(i) - (b * x(i) + aa)
        sum = sum + x(i) * sign(1#, d)
    Next i
R0Func = sum
End Function

Public Sub MedFit(x() As Single, y() As Single, a As Single, b As Single)
    Dim sx As Double, sxx As Double
    Dim sy As Double, sxy As Double

    Dim del As Double, bb As Double
    Dim b1 As Double, f1 As Double, b2 As Double, f2 As Double
    Dim ChiSq As Double, sigb As Double, f As Double
    Dim i As Integer
    
    LB = LBound(x):    UB = UBound(x)
    NData = UB - LB + 1
    ReDim XT(LB To UB): ReDim YT(LB To UB)
    
    'As a first guess for A and B, we will find the least-squares fitting line
    sx = 0: sxx = 0: sy = 0: sxy = 0
    For i = LB To UB
        XT(i) = x(i):        YT(i) = y(i)
        sx = sx + x(i)
        sy = sy + y(i)
        sxx = sxx + x(i) ^ 2
        sxy = sxy + x(i) * y(i)
    Next i
    del = NData * sxx - sx ^ 2
    aa = (sxx * sy - sx * sxy) / del
    bb = (NData * sxy - sx * sy) / del
    ChiSq = 0
    For i = LB To UB
        ChiSq = ChiSq + (y(i) - (aa + bb * x(i))) ^ 2
    Next i
    sigb = (ChiSq / del) ^ 0.5
    b1 = bb
    f1 = R0Func(b1, x(), y())
    b2 = bb + sign(3# * sigb, f1)
    f2 = R0Func(b2, x(), y())
    
    While (f1 * f2 > 0)
        bb = 2# * b2 - b1
        b1 = b2
        f1 = f2
        b2 = bb
        f2 = R0Func(b2, x(), y())
    Wend
    sigb = 0.01 * sigb
    Do While (Abs(b2 - b1) > sigb)
        bb = 0.5 * (b1 + b2)
        If (bb = b1) Or (bb = b2) Then Exit Do
        f = R0Func(bb, x(), y())
        If (f * f1 >= 0) Then
            f1 = f
            b1 = bb
        Else
            f2 = f
            b2 = bb
        End If
        DoEvents
    Loop
    a = aa
    b = bb
End Sub


'Seite 508f

Public Sub Fit(x() As Single, y() As Single, a As Single, b As Single)
    Dim NData As Long, i As Long
    Dim LB As Long, UB As Long
    Dim sx As Double, sy As Double, st2 As Double, SS As Double
    Dim wt As Double, sxoss As Double, t As Double
    Const sig = 0.01
    
    LB = LBound(x):    UB = UBound(x)
    NData = UB - LB + 1
    
    
    For i = LB To UB
        sx = sx + x(i)
        sy = sy + y(i)
    Next i
    SS = CDbl(NData)
    sxoss = sx / SS
    For i = LB To UB
        t = x(i) - sxoss
        st2 = st2 + t ^ 2
        b = b + t * y(i)
    Next i
    b = b / st2
    a = (sy - sx * b) / SS
End Sub
