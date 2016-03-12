'
' Module internal implementation
'

#INCLUDE "Win32Api.inc"

FUNCTION EnvironmentVariable_Set( sName AS STRING, sValue AS STRING ) AS LONG

  FUNCTION = SetEnvironmentVariable(BYCOPY sName, BYCOPY sValue)

END FUNCTION

FUNCTION EnvironmentVariable_Get( sName AS STRING ) AS STRING

  LOCAL azBuffer AS ASCIIZ * 32768
  LOCAL realLen  AS LONG
  realLen = GetEnvironmentVariable(BYCOPY sName, BYVAL VARPTR(azBuffer), SIZEOF(azBuffer))

  FUNCTION = LEFT$(azBuffer, realLen)

END FUNCTION

FUNCTION EnvironmentVariable_GetItem( sName AS STRING, itemSeparator AS STRING, itemIndex AS LONG ) AS STRING

  LOCAL allItems AS STRING
  allItems = EnvironmentVariable_Get(sName)

  FUNCTION = PARSE$(allItems, itemSeparator, itemIndex)

END FUNCTION

FUNCTION EnvironmentVariable_GetItemCount( sName AS STRING, itemSeparator AS STRING ) AS LONG

  LOCAL allItems AS STRING
  allItems = EnvironmentVariable_Get(sName)

  FUNCTION = PARSECOUNT(allItems, itemSeparator)

END FUNCTION

FUNCTION EnvironmentVariable_Exists( sName AS STRING ) AS LONG

  FUNCTION = LEN(EnvironmentVariable_Get(sName)) > 0

END FUNCTION

FUNCTION EnvironmentVariable_Remove( sName AS STRING ) AS LONG

  FUNCTION = SetEnvironmentVariable(BYCOPY sName, BYCOPY "")

END FUNCTION

FUNCTION EnvironmentVariable_List( sSeparator AS STRING ) AS STRING

  sSeparator = IIF$(LEN(sSeparator), sSeparator, ",")

  LOCAL listBuffer AS ISTRINGBUILDERA
  listBuffer = CLASS "StringBuilderA"

  LOCAL pEnvBlock, pEnvString AS ASCIIZ PTR
  LOCAL envStringLen AS DWORD

  pEnvBlock  = GetEnvironmentStrings()
  pEnvString = pEnvBlock
  DO
    envStringLen = LEN(@pEnvString)
    listBuffer.Add(EXTRACT$(@pEnvString, "=") + sSeparator)
    pEnvString += envStringLen + 1
  LOOP WHILE envStringLen

  FreeEnvironmentStrings(BYVAL pEnvBlock)

  FUNCTION = RTRIM$(listBuffer.String, ",")

END FUNCTION
