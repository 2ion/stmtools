Attribute VB_Name = "API_Interface"
Option Explicit

Private Declare Function Sound Lib "kernel32" Alias "Beep" (ByVal dwFreq As Long, ByVal dwDuration As Long) As Long

Public Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)

Private Declare Function MessageBeep Lib "user32" (ByVal wType As Long) As Long



' ********************************************************************************
' ***********************    GET SPECIAL FOLDER    *******************************
' ********************************************************************************
Private Declare Function SHGetPathFromIDList Lib "Shell32" (ByVal pidList As Long, ByVal lpBuffer As String) As Long
Private Declare Function SHGetSpecialFolderLocation Lib "Shell32" (ByVal hwndOwner As Long, ByVal nFolder As Integer, ppidl As Long) As Long


Public Enum ShellSpecialFolderConstants
  CSIDL_DESKTOP = 0&                          'Alle Ressourcen ab Desktop
  CSIDL_PROGRAMS = &H2&                       'Startmenü Programme            <aktueller Benutzer>
  CSIDL_PRINTERS = &H4&                       'Drucker
  CSIDL_PERSONAL = &H5&                       'Eigene Dateien                 <aktueller Benutzer>
  CSIDL_FAVORITES = &H6&                      'Favoriten                      <aktueller Benutzer>
  CSIDL_STARTMENU = &HB&                      'Gesamtes Startmenü             <aktueller Benutzer>
  CSIDL_DESKTOPDIRECTORY = &H10&              'Desktop (Ordner)               <aktueller Benutzer>
  CSIDL_DRIVES = &H11&                        'Arbeitsplatz
  CSIDL_NETWORK = &H12&                       'Netzwerkumgebung
  CSIDL_NETHOOD = &H13&                       'Netzwerkumgebung (Ordner)
  CSIDL_FONTS = &H14&                         'Fonts (Ordner)
  CSIDL_TEMPLATES = &H15&                     'Vorlagen (Ordner)
  CSIDL_COMMON_STARTMENU = &H16&              'Gesamtes Startmenü             <alle Benutzer>
  CSIDL_COMMON_PROGRAMS = &H17&               'Startmenü Programme            <alle Benutzer>
  CSIDL_COMMON_STARTUP = &H18&                'Autostart (Ordner)             <alle Benutzer>
  CSIDL_COMMON_DESKTOPDIRECTORY = &H18&       'Destop (Ordner)                <alle Benutzer>
  CSIDL_APPDATA = &H1A&                       'Anwendungsdaten        <aktueller Benutzer>
  CSIDL_PRINTHOOD = &H1B&                     'Druckumgebung (Ordner)
  CSIDL_ALTSTARTUP = &H1D&                    'alt. Autostart (Ordner)        <aktueller Benutzer>
  CSIDL_COMMON_ALTSTARTUP = &H1E&             'alt. Autostart (Ordner)        <alle Benutzer>
  CSIDL_COMMON_FAVORITES = &H1F&              'Favoriten              <alle Benutzer>
  CSIDL_INTERNET_CACHE = &H20&                'Temp. Internet Files
  CSIDL_COOKIES = &H21&                       'Internet Cookies (Ordner)
  CSIDL_HISTORY = &H22&                       'Internet Verlauf (Ordner)
End Enum


Public Function GetSpecialFolder(RootFolder As ShellSpecialFolderConstants) As String
    Dim pID     As Long
    Dim sPath   As String

    Call SHGetSpecialFolderLocation(0, RootFolder, pID)

    If pID Then
      sPath = Space(255)
      Call SHGetPathFromIDList(pID, sPath)
      sPath = left(sPath, InStr(sPath, Chr(0)) - 1)
    Else
      sPath = ""
    End If
   
    GetSpecialFolder = sPath
  End Function


' ********************************************************************************
' ***********************    BEEP    *******************************
' ********************************************************************************



Public Sub Beep()
    Sound 300, 100
End Sub

