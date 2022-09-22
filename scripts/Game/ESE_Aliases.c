// -----------------------------------------------------------------------------------------------------------
// Enforce Script Extensions - By NarcoMarshmallow
// 
// Message me @narcoleptic marshmallow #1188 on discord to give feedback or go to https://github.com/NarcoMarshDev
// -----------------------------------------------------------------------------------------------------------
class ESE_Aliases
{
	// TESTING, REMOVE BEFORE RELEASE!!!
	//#define ESE_ALIASES_ALL
	
	// Pre-processor enable all other defs if ESE_ALIASES_ALL is defined
	#ifdef ESE_ALIASES_ALL
	#define ESE_ALIASES_MATERIALS
	#define ESE_ALIASES_WEAPONS
	#define ESE_ALIASES_ATTACHMENTS
	#define ESE_ALIASES_MAGAZINES
	#define ESE_ALIASES_VEHICLES
	#define ESE_ALIASES_MATH
	#endif
		
	// ---------------------------------------------------------------- MATERIALS ---------------------------------------------------------------- //
	
	#ifdef ESE_ALIASES_MATERIALS
	static ResourceName MAT_CANBUILD 	= "{56EBF5038622AC95}Assets/Conflict/CanBuild.emat";
	static ResourceName MAT_CANNOTBUILD	= "{14A9DCEA57D1C381}Assets/Conflict/CannotBuild.emat";
	#endif
	
	// ----------------------------------------------------------------- WEAPONS ---------------------------------------------------------------- //
	
	#ifdef ESE_ALIASES_WEAPONS
	// RIFLES
	static ResourceName WEP_AK74		= "{FA5C25BF66A53DCF}Prefabs/Weapons/Rifles/AK74/Rifle_AK74.et";
	static ResourceName WEP_AK74_GP25	= "{63E8322E2ADD4AA7}Prefabs/Weapons/Rifles/AK74/Rifle_AK74_GP25.et";
	static ResourceName WEP_M21			= "{B31929F65F0D0279}Prefabs/Weapons/Rifles/M14/Rifle_M21.et";
	static ResourceName WEP_M21_ARTII	= "{81EB948E6414BD6F}Prefabs/Weapons/Rifles/M14/Rifle_M21_ARTII.et";
	static ResourceName WEP_M16A2 		= "{3E413771E1834D2F}Prefabs/Weapons/Rifles/M16/Rifle_M16A2.et";
	static ResourceName WEP_M16A2_M203 	= "{5A987A8A13763769}Prefabs/Weapons/Rifles/M16/Rifle_M16A2_M203.et";
	static ResourceName WEP_SVD 		= "{3EB02CDAD5F23C82}Prefabs/Weapons/Rifles/SVD/Rifle_SVD.et";
	static ResourceName WEP_SVD_PSO 	= "{6415B7923DE28C1B}Prefabs/Weapons/Rifles/SVD/Rifle_SVD_PSO.et";
	// LMGS
	static ResourceName WEP_M249 		= "{D2B48DEBEF38D7D7}Prefabs/Weapons/MachineGuns/M249/MG_M249.et";
	static ResourceName WEP_M60 		= "{D182DCDD72BF7E34}Prefabs/Weapons/MachineGuns/M60/MG_M60.et";
	static ResourceName WEP_PKM 		= "{A89BC9D55FFB4CD8}Prefabs/Weapons/MachineGuns/PKM/MG_PKM.et";
	static ResourceName WEP_RPK74 		= "{A7AF84C6C58BA3E8}Prefabs/Weapons/MachineGuns/RPK74/MG_RPK74.et";
	// HANDGUNS
	static ResourceName WEP_M9 			= "{1353C6EAD1DCFE43}Prefabs/Weapons/Handguns/M9/Handgun_M9.et";
	static ResourceName WEP_PM 			= "{C0F7DD85A86B2900}Prefabs/Weapons/Handguns/PM/Handgun_PM.et";
	// LAUNCHERS
	static ResourceName WEP_M72A3 		= "{9C5C20FB0E01E64F}Prefabs/Weapons/Launchers/M72/Launcher_M72A3.et";
	static ResourceName WEP_RPG7 		= "{7A82FE978603F137}Prefabs/Weapons/Launchers/RPG7/Launcher_RPG7.et";
	// FRAG GRENADES
	static ResourceName WEP_M67 		= "{E8F00BF730225B00}Prefabs/Weapons/Grenades/Grenade_M67.et";
	static ResourceName WEP_RGD5 		= "{645C73791ECA1698}Prefabs/Weapons/Grenades/Grenade_RGD5.et";
	// SMOKE GRENADES
	static ResourceName WEP_ANM8HC 		= "{9DB69176CEF0EE97}Prefabs/Weapons/Grenades/Smoke_ANM8HC.et";
	static ResourceName WEP_RDG2 		= "{77EAE5E07DC4678A}Prefabs/Weapons/Grenades/Smoke_RDG2.et";
	static ResourceName WEP_M18_WHITE 	= "{AD2709F5F6F0D871}Prefabs/Weapons/Grenades/M18/Smoke_M18_Base.et";
	static ResourceName WEP_M18_GREEN 	= "{D41D22DD1B8E921E}Prefabs/Weapons/Grenades/M18/Smoke_M18_Green.et";
	static ResourceName WEP_M18_RED 	= "{3343A055A83CB30D}Prefabs/Weapons/Grenades/M18/Smoke_M18_Red.et";
	static ResourceName WEP_M18_VIOLET 	= "{14C1A0F061D9DDEE}Prefabs/Weapons/Grenades/M18/Smoke_M18_Violet.et";
	static ResourceName WEP_M18_YELLOW 	= "{9BBDEE253A16CC66}Prefabs/Weapons/Grenades/M18/Smoke_M18_Yellow.et";
	#endif
	
	// ---------------------------------------------------------------- ATTACHMENTS ---------------------------------------------------------------- //
	
	#ifdef ESE_ALIASES_ATTACHMENTS
	// SCOPES
	static ResourceName OPTIC_ARTII 	= "{D2018EDB1BBF4C88}Prefabs/Weapons/Attachments/Optics/Optic_ARTII.et";
	static ResourceName OPTIC_PSO1 		= "{C850A33226B8F9C1}Prefabs/Weapons/Attachments/Optics/Optic_PSO1.et";
	// UGL'S
	static ResourceName UGL_M203 		= "{43FDAF3FA0FF2299}Prefabs/Weapons/Attachments/Underbarrel/UGL_M203.et";
	static ResourceName UGL_GP25 		= "{1ABABE3551512B0A}Prefabs/Weapons/Attachments/Underbarrel/UGL_GP25.et";
	// BAYONETS
	static ResourceName BAYONET_M9 		= "{A4AF9C38A4179880}Prefabs/Weapons/Attachments/Bayonets/Bayonet_M9.et";
	static ResourceName BAYONET_6KH4 	= "{C7534F7A79EA3331}Prefabs/Weapons/Attachments/Bayonets/Bayonet_6Kh4.et";
	// HANDGUARDS
	static ResourceName HGUARD_M16A2 	= "{FB1A7F5BC7D935E2}Prefabs/Weapons/Attachments/Handguards/Handguard_M16A2/Handguard_M16.et";
	#endif
	
	// ----------------------------------------------------------------- MAGAZINES ---------------------------------------------------------------- //
	
	#ifdef ESE_ALIASES_MAGAZINES
	// MISSING FOR NOW BECAUSE THERE'S SO MANY OF THEM AND IT HURTS TO THINK ABOUT DOING
	#endif
	
	// ----------------------------------------------------------------- VEHICLES ----------------------------------------------------------------- //
	
	#ifdef ESE_ALIASES_VEHICLES
	// LIGHT VEHICLES
	static ResourceName VEH_M151A2				= "{F649585ABB3706C4}Prefabs/Vehicles/Wheeled/M151A2/M151A2.et";
	static ResourceName VEH_M151A2_TRANSPORT	= "{47D94E1193A88497}Prefabs/Vehicles/Wheeled/M151A2/M151A2_transport.et";
	static ResourceName VEH_M151A2_M2HB			= "{F6B23D17D5067C11}Prefabs/Vehicles/Wheeled/M151A2/M151A2_M2HB.et";
	
	static ResourceName VEH_UAZ469				= "{259EE7B78C51B624}Prefabs/Vehicles/Wheeled/UAZ469/UAZ469.et";
	// TRUCKS
	static ResourceName VEH_M923A1				= "{9A0D72816DFFDB7F}Prefabs/Vehicles/Wheeled/M923A1/M923A1.et";
	static ResourceName VEH_M923A1_TRANSPORT	= "{F1FBD0972FA5FE09}Prefabs/Vehicles/Wheeled/M923A1/M923A1_transport.et";
	static ResourceName VEH_M923A1_COVERED		= "{81FDAD5EB644CC3D}Prefabs/Vehicles/Wheeled/M923A1/M923A1_transport_covered.et";
	static ResourceName VEH_M923A1_TANKER		= "{2BE1F8B9299B67C1}Prefabs/Vehicles/Wheeled/M923A1/M923A1_tanker.et";
	static ResourceName VEH_M923A1_COMMAND		= "{36BDCC88B17B3BFA}Prefabs/Vehicles/Wheeled/M923A1/M923A1_command.et";
	static ResourceName VEH_URAL4320			= "{4597626AF36C0858}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320.et";
	static ResourceName VEH_URAL4320_TRANSPORT	= "{16C1F16C9B053801}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320_transport.et";
	static ResourceName VEH_URAL4320_COVERED	= "{D9B91FAB817A6033}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320_transport_covered.et";
	static ResourceName VEH_URAL4320_TANKER		= "{4C81D7ED8F8C0D87}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320_tanker.et";
	static ResourceName VEH_URAL4320_COMMAND	= "{1BABF6B33DA0AEB6}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320_command.et";
	// MEDIUM VEHICLES
	static ResourceName VEH_M998				= "{5674FAEB9AB7BDD0}Prefabs/Vehicles/Wheeled/M998/M998.et";
	static ResourceName VEH_M998_COVERED		= "{B55C6990A6A9411B}Prefabs/Vehicles/Wheeled/M998/M998_covered.et";
	static ResourceName VEH_M998_COVERED_LONG	= "{9B1BF9644E0378D6}Prefabs/Vehicles/Wheeled/M998/M998_covered_long.et";
	
	static ResourceName VEH_M1025				= "{4A71F755A4513227}Prefabs/Vehicles/Wheeled/M998/M1025.et";
	static ResourceName VEH_M1025_ARMED_EMPTY	= "{B120CDDBEF8DB007}Prefabs/Vehicles/Wheeled/M998/M1025_armed_base.et";
	static ResourceName VEH_M1025_ARMED_M2HB	= "{3EA6F47D95867114}Prefabs/Vehicles/Wheeled/M998/M1025_armed_M2HB.et";
	
	static ResourceName VEH_BTR70				= "{C012BB3488BEA0C2}Prefabs/Vehicles/Wheeled/BTR70/BTR70.et";
	#endif
}