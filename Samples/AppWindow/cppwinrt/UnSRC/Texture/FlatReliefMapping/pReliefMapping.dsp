# Microsoft Developer Studio Project File - Name="pReliefMapping" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=pReliefMapping - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "pReliefMapping.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "pReliefMapping.mak" CFG="pReliefMapping - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pReliefMapping - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "pReliefMapping - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "pReliefMapping - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(CG_INC_PATH)" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "NDEBUG"
# ADD RSC /l 0x416 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 opengl32.lib glu32.lib winmm.lib cg.lib cgGL.lib user32.lib gdi32.lib comdlg32.lib /nologo /subsystem:windows /machine:I386 /out:"../pReliefMapping.exe" /libpath:"$(CG_LIB_PATH)"

!ELSEIF  "$(CFG)" == "pReliefMapping - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(CG_INC_PATH)" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "_DEBUG"
# ADD RSC /l 0x416 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib glu32.lib winmm.lib cg.lib cgGL.lib user32.lib gdi32.lib comdlg32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"../pReliefMapping.exe" /pdbtype:sept /libpath:"$(CG_LIB_PATH)"

!ENDIF 

# Begin Target

# Name "pReliefMapping - Win32 Release"
# Name "pReliefMapping - Win32 Debug"
# Begin Group "shaders"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\shaders\cg_relief_map.cg

!IF  "$(CFG)" == "pReliefMapping - Win32 Release"

# Begin Custom Build
InputPath=..\shaders\cg_relief_map.cg
InputName=cg_relief_map

"..\shaders\$(InputName).fp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(CG_BIN_PATH)\cgc.exe"  "$(InputPath)" -entry main_relief -profile arbfp1 -o ..\shaders\$(InputName).fp

# End Custom Build

!ELSEIF  "$(CFG)" == "pReliefMapping - Win32 Debug"

# Begin Custom Build
InputPath=..\shaders\cg_relief_map.cg
InputName=cg_relief_map

"..\shaders\$(InputName).fp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(CG_BIN_PATH)\cgc.exe"  "$(InputPath)" -entry main_relief -profile arbfp1 -o ..\shaders\$(InputName).fp

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\glWin32.cpp
# End Source File
# Begin Source File

SOURCE=.\glWin32.rc
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\main.ico
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=..\..\p3d\lib\Paralelo3D.lib
# End Source File
# End Target
# End Project
