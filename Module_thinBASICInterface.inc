'
' Module thinBASIC interface
'

#INCLUDE "Module_Implementation.inc"

' -----------------------------------------------------------------------------

FUNCTION Module_LoadSymbols() AS LONG

  thinBasic_LoadSymbol  "EnVar_List"        , %thinBasic_ReturnString  , CODEPTR( Exec_EnVar_List )                 , %thinBasic_ForceOverWrite
  thinBasic_LoadSymbol  "EnVar_Set"         , %thinBasic_ReturnCodeLong, CODEPTR( Exec_EnVar_Set )                  , %thinBasic_ForceOverWrite
  thinBasic_LoadSymbol  "EnVar_Get"         , %thinBasic_ReturnString  , CODEPTR( Exec_EnVar_Get )                  , %thinBasic_ForceOverWrite
  thinBasic_LoadSymbol  "EnVar_GetItem"     , %thinBasic_ReturnString  , CODEPTR( Exec_EnVar_GetItem )              , %thinBasic_ForceOverWrite
  thinBasic_LoadSymbol  "EnVar_GetItemCount", %thinBasic_ReturnCodeLong, CODEPTR( Exec_EnVar_GetItemCount )         , %thinBasic_ForceOverWrite
  thinBasic_LoadSymbol  "EnVar_Remove"      , %thinBasic_ReturnCodeLong, CODEPTR( Exec_EnVar_Remove )               , %thinBasic_ForceOverWrite
  thinBasic_LoadSymbol  "EnVar_Exists"      , %thinBasic_ReturnCodeLong, CODEPTR( Exec_EnVar_Exists )               , %thinBasic_ForceOverWrite

END FUNCTION

FUNCTION Exec_EnVar_List() AS STRING

  LOCAL sSeparator AS STRING
  IF thinBasic_CheckOpenParens_Optional() = %TRUE THEN
    thinBasic_ParseString(sSeparator)
    IF thinBasic_CheckCloseParens_Mandatory = %FALSE THEN
      thinBasic_RunTimeError(%ERR__MODULE_SPECIFIC, "You forgot enclosing brackets after separator")
    END IF
  ELSE
    sSeparator = ","
  END IF

  IF thinBasic_ErrorFree THEN
    FUNCTION = EnvironmentVariable_List(sSeparator)
  END IF

END FUNCTION

FUNCTION Exec_EnVar_Set() AS LONG

  LOCAL varName, varValue AS STRING
  LOCAL parensSpecified   AS LONG

  parensSpecified = thinBasic_CheckOpenParens_Optional

  thinBasic_ParseString(varName)
  IF thinBasic_CheckComma_Mandatory THEN
    thinBasic_ParseString(varValue)

    IF parensSpecified THEN
      thinBasic_CheckCloseParens_Mandatory
    END IF
  ELSE
    ' -- Run time error will be triggered
  END IF


  IF thinBasic_ErrorFree THEN
    FUNCTION = EnvironmentVariable_Set(varName, varValue)
  END IF

END FUNCTION

FUNCTION Exec_EnVar_Get() AS STRING

  LOCAL varName AS STRING

  IF TryParseSingleStringParameter(varName) THEN
    FUNCTION = EnvironmentVariable_Get(varName)
  END IF

END FUNCTION

FUNCTION Exec_EnVar_GetItem() AS STRING

  REGISTER parensSpecified AS LONG

  LOCAL varName AS STRING
  LOCAL itemIndex AS LONG
  LOCAL itemSeparator AS STRING

  parensSpecified = thinBasic_CheckOpenParens_Optional
  thinBasic_ParseString(varName)
  IF thinBasic_CheckComma_Mandatory AND thinBasic_ErrorFree THEN
    thinBasic_ParseString(itemSeparator)
    IF thinBasic_CheckComma_Mandatory AND thinBasic_ErrorFree THEN
      itemIndex = thinBasic_Parse1Number

      IF parensSpecified THEN
        thinBasic_CheckCloseParens_Mandatory
      END IF

      FUNCTION = EnvironmentVariable_GetItem(varName, itemSeparator, itemIndex)

    END IF

  END IF

END FUNCTION

FUNCTION Exec_EnVar_GetItemCount() AS LONG

  REGISTER parensSpecified AS LONG

  LOCAL varName AS STRING
  LOCAL itemSeparator AS STRING

  parensSpecified = thinBasic_CheckOpenParens_Optional
  thinBasic_ParseString(varName)
  IF thinBasic_CheckComma_Optional AND thinBasic_ErrorFree THEN
    thinBasic_ParseString(itemSeparator)
  END IF

  IF parensSpecified THEN
    thinBasic_CheckCloseParens_Mandatory
  END IF

  FUNCTION = EnvironmentVariable_GetItemCount(varName, itemSeparator)

END FUNCTION

FUNCTION Exec_EnVar_Remove() AS LONG

  LOCAL varName AS STRING

  IF TryParseSingleStringParameter(varName) THEN
    FUNCTION = EnvironmentVariable_Remove(varName)
  END IF

END FUNCTION

FUNCTION Exec_EnVar_Exists() AS LONG

  LOCAL varName AS STRING

  IF TryParseSingleStringParameter(varName) THEN
    FUNCTION = IIF(EnvironmentVariable_Exists(varName), 1, 0)
  END IF

END FUNCTION

FUNCTION TryParseSingleStringParameter(BYREF parsedValue AS STRING) AS LONG
  REGISTER parensSpecified AS LONG

  parensSpecified = thinBasic_CheckOpenParens_Optional
  thinBasic_ParseString(parsedValue)
  IF parensSpecified THEN
    thinBasic_CheckCloseParens_Mandatory
  END IF

  FUNCTION = thinBasic_ErrorFree

END FUNCTION
