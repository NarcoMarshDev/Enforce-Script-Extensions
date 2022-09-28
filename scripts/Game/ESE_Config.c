// -----------------------------------------------------------------------------------------------------------
// Enforce Script Extensions - By NarcoMarshmallow
// 
// Message me @narcoleptic marshmallow #1188 on discord to give feedback or go to https://github.com/NarcoMarshDev
/** -------------------------------------------------------- READ THIS --------------------------------------------------------

	Different functionality of ESE can be enabled or disabled by defining some different values. To do so, duplicate this file
	and name it ' !ESE_Config.c ' and then uncomment whatever #define statements you want, to enable those features.

	Full documentation : https://github.com/NarcoMarshDev/Enforce-Script-Extensions/wiki/Setting-Up-ESE#making-your-ese-config

	-------------------------------------------------------- READ THIS --------------------------------------------------------

@code

#define ESE_VERBOSE
	- Enable verbose error logging on ESE methods

#define ESE_ENABLE_WIP
	- Enable work in progress methods, mostly broken but none should cause compilation errors or crash anything (hopefully).

#define ESE_EXPERIMENTAL
	- Enables experimental custom data types, this WILL PROBABLY CAUSE THE WORKBENCH TO CRASH ON STARTUP, despite compiling fine.
	  If this happens just open your script in notepad or something and remove the #define and it will launch fine again.

#define ESE_OBSOLETE
	- Enables old versions of certain methods, may get replaced with an ESE_Obsolete class in the future containing all of them.

#define ESE_ALIASES_ALL
	- Enables all ESE shorthand name aliases, if you only want to use a specific set of aliases, use any of the following ones:
		#define ESE_ALIASES_MATERIALS	- Useful material ResourceNames
		#define ESE_ALIASES_WEAPONS		- All base game weapon ResourceNames
		#define ESE_ALIASES_ATTACHMENTS	- All base game attachment ResourceNames
		#define ESE_ALIASES_MAGAZINES 	- All base game magazine ResourceNames
		#define ESE_ALIASES_UNIFORMS	- All base game uniform ResourceNames
		#define ESE_ALIASES_EQUIPMENT	- All base game equipment ResourceNames (wearables and tool items)
		#define ESE_ALIASES_VEHICLES	- All base game vehicle ResourceNames (almost, missing some odd variants)

#define ESE_ALIASES_DEBUG
	- Enables some extra debugging features to help with implementing custom aliases.

@endcode
*/

// ------------------ UNCOMMENT THESE TO ENABLE FEATURES -------------------

//#define ESE_VERBOSE
//#define ESE_ENABLE_WIP
//#define ESE_EXPERIMENTAL
//#define ESE_OBSOLETE
//#define ESE_ALIASES_ALL
//#define ESE_ALIASES_MATERIALS
//#define ESE_ALIASES_WEAPONS
//#define ESE_ALIASES_ATTACHMENTS
//#define ESE_ALIASES_MAGAZINES
//#define ESE_ALIASES_UNIFORMS
//#define ESE_ALIASES_EQUIPMENT
//#define ESE_ALIASES_VEHICLES
//#define ESE_ALIASES_DEBUG

// -------------------- DO NOT MODIFY BEYOND THIS POINT --------------------

// Pre-processor enable all other alias defines if ESE_ALIASES_ALL is defined
#ifdef ESE_ALIASES_ALL
#define ESE_ALIASES_MATERIALS
#define ESE_ALIASES_WEAPONS
#define ESE_ALIASES_ATTACHMENTS
#define ESE_ALIASES_MAGAZINES
#define ESE_ALIASES_EQUIPMENT
#define ESE_ALIASES_VEHICLES
#endif