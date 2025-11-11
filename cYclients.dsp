# Microsoft Developer Studio Project File - Name="cYclients" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=cYclients - Win32
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cYclients.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cYclients.mak" CFG="cYclients - Win32"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cYclients - Win32" (based on "Win32 (x86) Static Library")
!MESSAGE "cYclients - WinnT" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "cYclients - Win32"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "build\win32"
# PROP BASE Intermediate_Dir "build\win32"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "build\win32"
# PROP Intermediate_Dir "build\win32"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "_MBCS" /D "_LIB" /YX /FD /c /I "win32\curl\include" /D "DEF:cYclients.def"
# ADD BASE RSC /l 0x419
# ADD RSC /l 0x419
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "cYclients - Winnt"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "build\winnt"
# PROP BASE Intermediate_Dir "build\winnt"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "build\winnt"
# PROP Intermediate_Dir "build\winnt"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c /I "winnt\curl\include" /D "DEF:cYclients.def"
# ADD BASE RSC /l 0x419
# ADD RSC /l 0x419
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "cYclients - Win32"
# Name "cYclients - Winnt"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\cJSON.c
# End Source File
# Begin Source File

SOURCE=.\src\log.c
# End Source File
# Begin Source File

SOURCE=.\src\curl_transport.c
# End Source File
# Begin Source File

SOURCE=.\src\structs.c
# End Source File
# Begin Source File

SOURCE=.\src\categories.c
# End Source File
# Begin Source File

SOURCE=.\src\services.c
# End Source File
# Begin Source File

SOURCE=.\src\users.c
# End Source File
# Begin Source File

SOURCE=.\src\auth.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\src\config.h
# End Source File
# Begin Source File

SOURCE=.\src\log.h
# End Source File
# Begin Source File

SOURCE=.\src\cJSON.h
# End Source File
# Begin Source File

SOURCE=.\src\curl_transport.h
# End Source File
# Begin Source File

SOURCE=.\src\structs.h
# End Source File
# Begin Source File

SOURCE=.\cYclients.h
# End Source File
# Begin Source File

SOURCE=.\partner_token.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.md
# End Source File 
# End Target
# End Project
