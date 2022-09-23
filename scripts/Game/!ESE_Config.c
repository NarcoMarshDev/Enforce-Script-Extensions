// -----------------------------------------------------------------------------------------------------------
// Enforce Script Extensions - By NarcoMarshmallow
// 
// Message me @narcoleptic marshmallow #1188 on discord to give feedback or go to https://github.com/NarcoMarshDev
// -----------------------------------------------------------------------------------------------------------

// REMEMBER TO CHANGE THIS TO USING THE DEFINES IN THE PROJECT OPTIONS MENU OR PEOPLE WILL RIOT!!!

/** -------------------------------------------------------- READ THIS --------------------------------------------------------

	Different functionality of ESE can be enabled or disabled by defining some different values. To do so, duplicate this file
	and name it ' !ESE_Config.c ' and then uncomment whatever #define statements you want, to enable those features.

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
		#define ESE_ALIASES_VEHICLES	- All base game vehicle ResourceNames (almost, missing some odd variats)
		#define ESE_ALIASES_MATH 		- Useful mathematical constants and such like

@endcode
*/

//#define ESE_VERBOSE
//#define ESE_ENABLE_WIP
//#define ESE_EXPERIMENTAL
//#define ESE_OBSOLETE
#define ESE_ALIASES_ALL
//#define ESE_ALIASES_MATERIALS
//#define ESE_ALIASES_WEAPONS
//#define ESE_ALIASES_ATTACHMENTS
//#define ESE_ALIASES_MAGAZINES
//#define ESE_ALIASES_VEHICLES
//#define ESE_ALIASES_MATH

// Pre-processor enable all other alias defs if ESE_ALIASES_ALL is defined
#ifdef ESE_ALIASES_ALL
#define ESE_ALIASES_MATERIALS
#define ESE_ALIASES_WEAPONS
#define ESE_ALIASES_ATTACHMENTS
#define ESE_ALIASES_MAGAZINES
#define ESE_ALIASES_VEHICLES
#define ESE_ALIASES_MATH
#endif