// -----------------------------------------------------------------------------------------------------------
// Enforce Script Extensions - By NarcoMarshmallow
// 
// Message me @narcoleptic marshmallow #1188 on discord to give feedback or go to https://github.com/NarcoMarshDev
// -----------------------------------------------------------------------------------------------------------

// This is a custom config for developing ese internally, it can all be ignored

#define ESE_DEVMODE // remember to comment off before releases

#ifdef ESE_DEVMODE

//#define ESE_VERBOSE
//#define ESE_ENABLE_WIP
//#define ESE_EXPERIMENTAL
//#define ESE_OBSOLETE
#define ESE_ALIASES_ALL
//#define ESE_ALIASES_MATERIALS
//#define ESE_ALIASES_WEAPONS
//#define ESE_ALIASES_ATTACHMENTS
//#define ESE_ALIASES_MAGAZINES
//#define ESE_ALIASES_EQUIPMENT
//#define ESE_ALIASES_VEHICLES
#define ESE_ALIASES_DEBUG
//#define ESE_ENABLE_REFLECTION

#endif

// -------------------- DO NOT MODIFY BEYOND THIS POINT --------------------

#ifdef ESE_ENABLE_REFLECTION
// Include all reflection classes if enabled
#include "$EnforceScriptExtensions:scripts/Game/Additions/Reflection/ESE_Reflection.h"
#include "$EnforceScriptExtensions:scripts/Game/Additions/Reflection/ESE_ReflectionEnums.h"
#include "$EnforceScriptExtensions:scripts/Game/Additions/Reflection/ESE_Type.h"
#include "$EnforceScriptExtensions:scripts/Game/Additions/Reflection/ESE_MemberInfo.h"
#include "$EnforceScriptExtensions:scripts/Game/Additions/Reflection/ESE_ScriptParser.h"
#endif
// Pre-processor enable all other alias defines if ESE_ALIASES_ALL is defined
#ifdef ESE_ALIASES_ALL
#define ESE_ALIASES_MATERIALS
#define ESE_ALIASES_WEAPONS
#define ESE_ALIASES_ATTACHMENTS
#define ESE_ALIASES_MAGAZINES
#define ESE_ALIASES_EQUIPMENT
#define ESE_ALIASES_VEHICLES
#endif