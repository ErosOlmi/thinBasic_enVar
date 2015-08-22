'
' Module for thinBASIC
'

' -----------------------------------------------------------------------------

#COMPILE DLL
#REGISTER NONE
#DIM ALL

' -- The version itself should reflect the targetted thinBasic version
#RESOURCE VERSIONINFO
#RESOURCE FILEVERSION 1, 9, 16, 0
#RESOURCE PRODUCTVERSION 1, 9, 16, 0

#RESOURCE STRINGINFO "0409", "04B0"

#RESOURCE VERSION$ "CompanyName",      "Petr Schreiber"
#RESOURCE VERSION$ "FileDescription",  "Module for Environment Variables handling"
#RESOURCE VERSION$ "FileVersion",      "1.9.16.0"
#RESOURCE VERSION$ "InternalName",     "EnVars"
#RESOURCE VERSION$ "OriginalFilename", "ThinBASIC_EnVar.dll"
#RESOURCE VERSION$ "LegalCopyright",   "Copyright © Petr Schreiber 2015"
#RESOURCE VERSION$ "ProductName",      "thinBasic_EnVar"
#RESOURCE VERSION$ "ProductVersion",   "1.9.16.0"
#RESOURCE VERSION$ "Comments",         "Support site: http://www.thinbasic.com/"

' -----------------------------------------------------------------------------

' -- thinBASIC module SDK
#INCLUDE "thinCore.inc"

' -- functionality exposed to ThinBASIC
#INCLUDE "Module_thinBASICInterface.inc

'----------------------------------------------------------------------------

FUNCTION LoadLocalSymbols ALIAS "LoadLocalSymbols" (OPTIONAL BYVAL sPath AS STRING) EXPORT AS LONG

  ' -- exposes the functionality to thinBasic
  Module_LoadSymbols()

  FUNCTION = 0&

END FUNCTION

' -----------------------------------------------------------------------------

FUNCTION UnLoadLocalSymbols ALIAS "UnLoadLocalSymbols" () EXPORT AS LONG

  FUNCTION = 0&

END FUNCTION

' -----------------------------------------------------------------------------

%DLL_PROCESS_ATTACH   = 1
%DLL_THREAD_ATTACH    = 2
%DLL_THREAD_DETACH    = 3
%DLL_PROCESS_DETACH   = 0
FUNCTION LIBMAIN ALIAS "LibMain" (BYVAL hInstance   AS LONG, _
                                  BYVAL fwdReason   AS LONG, _
                                  BYVAL lpvReserved AS LONG) EXPORT AS LONG
  SELECT CASE fwdReason
    CASE %DLL_PROCESS_ATTACH

      FUNCTION = 1
      EXIT FUNCTION
    CASE %DLL_PROCESS_DETACH

      FUNCTION = 1
      EXIT FUNCTION
    CASE %DLL_THREAD_ATTACH

      FUNCTION = 1
      EXIT FUNCTION
    CASE %DLL_THREAD_DETACH

      FUNCTION = 1
      EXIT FUNCTION
  END SELECT

END FUNCTION
