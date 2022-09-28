// -----------------------------------------------------------------------------------------------------------
// Enforce Script Extensions - By NarcoMarshmallow
// 
// Message me @narcoleptic marshmallow #1188 on discord to give feedback or go to https://github.com/NarcoMarshDev
// -----------------------------------------------------------------------------------------------------------

/**
ESE_Aliases Class

Class containing all constants and methods for the alias system, providing shortcuts for accessing the game's
resources such as weapons, vehicles, materials, etc.

For full documentation check the wiki @ https://github.com/NarcoMarshDev/Enforce-Script-Extensions/wiki/ESE_Aliases-Class

Code example:
@code
	Resource res = Resource.Load(ESE_Aliases.AR_WEP_AK74);
	if (res.IsValid())
		// do something
		return true;
@endcode
*/

// For all resource types, right click -> Goto Declaration : ESE_ResourceType

class ESE_Aliases
{
// -------------------------------------------------------------- Public Methods ------------------------------------------------------------- //
	
	static void AddBlacklist(array<ResourceName> blackList)
	{
		foreach (ResourceName res : blackList)
		{
			m_pAliasRegister.Remove(res);
		}
	}
	
	static void RemoveAliasFromRegister(ResourceName alias)
	{
		m_pAliasRegister.Remove(alias);
	}
	
	static void DebugRegister()
	{
		int count = m_pAliasRegister.Count();
		Print("Register Count: " + count);
		for (int i = 0; i < count; i++)
		{
			#ifdef ESE_ALIASES_DEBUG
			Print("["+i+"] Key: " + m_pAliasRegister.GetKey(i) + "\t\t Val: " + m_pEnumLookupArray[m_pAliasRegister.GetElement(i)]);
			#endif
			
			#ifndef ESE_ALIASES_DEBUG
			Print("["+i+"] Key: " + m_pAliasRegister.GetKey(i) + "\t\t Val: " + m_pAliasRegister.GetElement(i));
			#endif
		}
	}
	
	// ------------------------------------------------------------- Private Methods ------------------------------------------------------------- //
	
	/**
	Map that all aliases and their types are registered to so they can be sorted and worked with as a group, such as methods for
	getting all resources of a certain category e.g get all assault rifles.
	*/
	private static ref map<ResourceName, ESE_ResourceType> m_pAliasRegister = new map<ResourceName, ESE_ResourceType>();
	
	/**
	Use in modded class to create new custom aliases, see: https://github.com/NarcoMarshDev/Enforce-Script-Extensions/wiki/Adding-Custom-Aliases-In-Your-Mod
	
	@code
		modded class ESE_Aliases
		{
			static const ResourceName newAlias = CreateAlias("{3C10D749A4E84B38}Common/Materials/Default.emat", ESE_ResourceType.EntityMaterial);
		}
	@endcode
	*/
	private static ResourceName CreateAlias(ResourceName path, ESE_ResourceType type = ESE_ResourceType.None)
	{
		m_pAliasRegister.Insert(path, type);
		return path;
	}
	
	// ---------------------------------------------------------------- MATERIALS ---------------------------------------------------------------- //
	
	#ifdef ESE_ALIASES_MATERIALS
	static const ResourceName AR_MAT_CANBUILD 		= CreateAlias("{56EBF5038622AC95}Assets/Conflict/CanBuild.emat", 						ESE_ResourceType.EntityMaterial);
	static const ResourceName AR_MAT_CANNOTBUILD	= CreateAlias("{14A9DCEA57D1C381}Assets/Conflict/CannotBuild.emat", 					ESE_ResourceType.EntityMaterial);
	#endif
	
	// ----------------------------------------------------------------- WEAPONS ---------------------------------------------------------------- //
	
	#ifdef ESE_ALIASES_WEAPONS
	// RIFLES
	static const ResourceName AR_WEP_AK74			= CreateAlias("{FA5C25BF66A53DCF}Prefabs/Weapons/Rifles/AK74/Rifle_AK74.et", 			ESE_ResourceType.AssaultRifle);
	static const ResourceName AR_WEP_AK74_GP25		= CreateAlias("{63E8322E2ADD4AA7}Prefabs/Weapons/Rifles/AK74/Rifle_AK74_GP25.et", 		ESE_ResourceType.AssaultRifle);
	static const ResourceName AR_WEP_M21			= CreateAlias("{B31929F65F0D0279}Prefabs/Weapons/Rifles/M14/Rifle_M21.et", 				ESE_ResourceType.MarksmanRifle);
	static const ResourceName AR_WEP_M21_ARTII		= CreateAlias("{81EB948E6414BD6F}Prefabs/Weapons/Rifles/M14/Rifle_M21_ARTII.et", 		ESE_ResourceType.MarksmanRifle);
	static const ResourceName AR_WEP_M16A2 			= CreateAlias("{3E413771E1834D2F}Prefabs/Weapons/Rifles/M16/Rifle_M16A2.et",  			ESE_ResourceType.AssaultRifle);
	static const ResourceName AR_WEP_M16A2_M203 	= CreateAlias("{5A987A8A13763769}Prefabs/Weapons/Rifles/M16/Rifle_M16A2_M203.et",  		ESE_ResourceType.AssaultRifle);
	static const ResourceName AR_WEP_SVD 			= CreateAlias("{3EB02CDAD5F23C82}Prefabs/Weapons/Rifles/SVD/Rifle_SVD.et",  			ESE_ResourceType.MarksmanRifle);
	static const ResourceName AR_WEP_SVD_PSO 		= CreateAlias("{6415B7923DE28C1B}Prefabs/Weapons/Rifles/SVD/Rifle_SVD_PSO.et",  		ESE_ResourceType.MarksmanRifle);
	// LMGS
	static const ResourceName AR_WEP_M249 			= CreateAlias("{D2B48DEBEF38D7D7}Prefabs/Weapons/MachineGuns/M249/MG_M249.et",  		ESE_ResourceType.SquadAutomaticWeapon);
	static const ResourceName AR_WEP_M60 			= CreateAlias("{D182DCDD72BF7E34}Prefabs/Weapons/MachineGuns/M60/MG_M60.et",  			ESE_ResourceType.MachineGun);
	static const ResourceName AR_WEP_PKM 			= CreateAlias("{A89BC9D55FFB4CD8}Prefabs/Weapons/MachineGuns/PKM/MG_PKM.et",  			ESE_ResourceType.MachineGun);
	static const ResourceName AR_WEP_RPK74 			= CreateAlias("{A7AF84C6C58BA3E8}Prefabs/Weapons/MachineGuns/RPK74/MG_RPK74.et",  		ESE_ResourceType.SquadAutomaticWeapon);
	// HANDGUNS
	static const ResourceName AR_WEP_M9 			= CreateAlias("{1353C6EAD1DCFE43}Prefabs/Weapons/Handguns/M9/Handgun_M9.et",  			ESE_ResourceType.Handgun);
	static const ResourceName AR_WEP_PM 			= CreateAlias("{C0F7DD85A86B2900}Prefabs/Weapons/Handguns/PM/Handgun_PM.et",  			ESE_ResourceType.Handgun);
	// LAUNCHERS
	static const ResourceName AR_WEP_M72A3 			= CreateAlias("{9C5C20FB0E01E64F}Prefabs/Weapons/Launchers/M72/Launcher_M72A3.et",  	ESE_ResourceType.RocketLauncher);
	static const ResourceName AR_WEP_RPG7 			= CreateAlias("{7A82FE978603F137}Prefabs/Weapons/Launchers/RPG7/Launcher_RPG7.et", 		ESE_ResourceType.RocketLauncher);
	// FRAG GRENADES
	static const ResourceName AR_WEP_M67 			= CreateAlias("{E8F00BF730225B00}Prefabs/Weapons/Grenades/Grenade_M67.et",  			ESE_ResourceType.LethalGrenade);
	static const ResourceName AR_WEP_RGD5 			= CreateAlias("{645C73791ECA1698}Prefabs/Weapons/Grenades/Grenade_RGD5.et",  			ESE_ResourceType.LethalGrenade);
	// SMOKE GRENADES
	static const ResourceName AR_WEP_ANM8HC 		= CreateAlias("{9DB69176CEF0EE97}Prefabs/Weapons/Grenades/Smoke_ANM8HC.et",  			ESE_ResourceType.SmokeGrenade);
	static const ResourceName AR_WEP_RDG2 			= CreateAlias("{77EAE5E07DC4678A}Prefabs/Weapons/Grenades/Smoke_RDG2.et",  				ESE_ResourceType.SmokeGrenade);
	static const ResourceName AR_WEP_M18_WHITE 		= CreateAlias("{AD2709F5F6F0D871}Prefabs/Weapons/Grenades/M18/Smoke_M18_Base.et",  		ESE_ResourceType.SmokeGrenade);
	static const ResourceName AR_WEP_M18_GREEN 		= CreateAlias("{D41D22DD1B8E921E}Prefabs/Weapons/Grenades/M18/Smoke_M18_Green.et",  	ESE_ResourceType.SmokeGrenade);
	static const ResourceName AR_WEP_M18_RED 		= CreateAlias("{3343A055A83CB30D}Prefabs/Weapons/Grenades/M18/Smoke_M18_Red.et",  		ESE_ResourceType.SmokeGrenade);
	static const ResourceName AR_WEP_M18_VIOLET 	= CreateAlias("{14C1A0F061D9DDEE}Prefabs/Weapons/Grenades/M18/Smoke_M18_Violet.et",  	ESE_ResourceType.SmokeGrenade);
	static const ResourceName AR_WEP_M18_YELLOW 	= CreateAlias("{9BBDEE253A16CC66}Prefabs/Weapons/Grenades/M18/Smoke_M18_Yellow.et",  	ESE_ResourceType.SmokeGrenade);
	#endif
	
	// ---------------------------------------------------------------- ATTACHMENTS ---------------------------------------------------------------- //
	
	#ifdef ESE_ALIASES_ATTACHMENTS
	// SCOPES
	static const ResourceName AR_OPTIC_ARTII 		= CreateAlias("{D2018EDB1BBF4C88}Prefabs/Weapons/Attachments/Optics/Optic_ARTII.et",  	ESE_ResourceType.Optic);
	static const ResourceName AR_OPTIC_PSO1 		= CreateAlias("{C850A33226B8F9C1}Prefabs/Weapons/Attachments/Optics/Optic_PSO1.et",  	ESE_ResourceType.Optic);
	// UGL'S
	static const ResourceName AR_UGL_M203 			= CreateAlias("{43FDAF3FA0FF2299}Prefabs/Weapons/Attachments/Underbarrel/UGL_M203.et",  ESE_ResourceType.UnderbarrelWeapon);
	static const ResourceName AR_UGL_GP25 			= CreateAlias("{1ABABE3551512B0A}Prefabs/Weapons/Attachments/Underbarrel/UGL_GP25.et",  ESE_ResourceType.UnderbarrelWeapon);
	// BAYONETS
	static const ResourceName AR_BAYONET_M9 		= CreateAlias("{A4AF9C38A4179880}Prefabs/Weapons/Attachments/Bayonets/Bayonet_M9.et",  	ESE_ResourceType.Bayonet);
	static const ResourceName AR_BAYONET_6KH4 		= CreateAlias("{C7534F7A79EA3331}Prefabs/Weapons/Attachments/Bayonets/Bayonet_6Kh4.et", ESE_ResourceType.Bayonet);
	// HANDGUARDS
	static const ResourceName AR_HGUARD_M16A2 		= CreateAlias("{FB1A7F5BC7D935E2}Prefabs/Weapons/Attachments/Handguards/Handguard_M16A2/Handguard_M16.et", ESE_ResourceType.Handguard);
	#endif
	
	// ----------------------------------------------------------------- MAGAZINES ---------------------------------------------------------------- //
	
	#ifdef ESE_ALIASES_MAGAZINES
	// HANDGUNS
	static const ResourceName AR_MAG_PM_BASE 		= CreateAlias("{9B5AA2C731485ACA}Prefabs/Weapons/Magazines/Magazine_9x18_PM_8rnd_Base.et", 					ESE_ResourceType.Magazine);
	static const ResourceName AR_MAG_PM_BALL 		= CreateAlias("{8B853CDD11BA916E}Prefabs/Weapons/Magazines/Magazine_9x18_PM_8rnd_Ball.et", 					ESE_ResourceType.Magazine);
	static const ResourceName AR_MAG_M9_BASE 		= CreateAlias("{DFFBF5F097FCF797}Prefabs/Weapons/Magazines/Magazine_9x19_M9_15rnd_Base.et", 				ESE_ResourceType.Magazine);
	static const ResourceName AR_MAG_M9_BALL 		= CreateAlias("{9C05543A503DB80E}Prefabs/Weapons/Magazines/Magazine_9x19_M9_15rnd_Ball.et", 				ESE_ResourceType.Magazine);
	// RIFLES
	static const ResourceName AR_MAG_AK74_BALL 		= CreateAlias("{BBB50A815A2F916B}Prefabs/Weapons/Magazines/Magazine_545x39_AK_30rnd_Ball.et", 				ESE_ResourceType.Magazine);
	static const ResourceName AR_MAG_AK74_TRACER	= CreateAlias("{E5912E45754CD421}Prefabs/Weapons/Magazines/Magazine_545x39_AK_30rnd_Tracer.et", 			ESE_ResourceType.Magazine);
	static const ResourceName AR_MAG_AK74_ENDTRACER	= CreateAlias("{0A84AA5A3884176F}Prefabs/Weapons/Magazines/Magazine_545x39_AK_30rnd_Last_5Tracer.et", 		ESE_ResourceType.Magazine);
	static const ResourceName AR_MAG_M16_BALL 		= CreateAlias("{2EBF60EF24B108FC}Prefabs/Weapons/Magazines/Magazine_556x45_STANAG_30rnd_Ball.et", 			ESE_ResourceType.Magazine);
	static const ResourceName AR_MAG_M16_TRACER		= CreateAlias("{A9A385FE1F7BF4BD}Prefabs/Weapons/Magazines/Magazine_556x45_STANAG_30rnd_Tracer.et", 		ESE_ResourceType.Magazine);
	static const ResourceName AR_MAG_M16_ENDTRACER	= CreateAlias("{D8F2CA92583B23D3}Prefabs/Weapons/Magazines/Magazine_556x45_STANAG_30rnd_Last_5Tracer.et", 	ESE_ResourceType.Magazine);
	// MARKSMAN RIFLES
	static const ResourceName AR_MAG_M14_BASE 		= CreateAlias("{6D18CC33708EE712}Prefabs/Weapons/Magazines/Magazine_762x51_M14_20rnd_Base.et", 				ESE_ResourceType.Magazine);
	static const ResourceName AR_MAG_M14_SPECIAL 	= CreateAlias("{627255315038152A}Prefabs/Weapons/Magazines/Magazine_762x51_M14_20rnd_SpecialBall.et", 		ESE_ResourceType.Magazine);
	static const ResourceName AR_MAG_SVD_BASE 		= CreateAlias("{761A03A9C5BA8D68}Prefabs/Weapons/Magazines/Magazine_762x54_SVD_10rnd_Base.et", 				ESE_ResourceType.Magazine);
	static const ResourceName AR_MAG_SVD_SNIPER		= CreateAlias("{9CCB46C6EE632C1A}Prefabs/Weapons/Magazines/Magazine_762x54_SVD_10rnd_Sniper.et", 			ESE_ResourceType.Magazine);
	// SAW'S
	static const ResourceName AR_MAG_M249_BALL 		= CreateAlias("{4FCBBDF274FD2157}Prefabs/Weapons/Magazines/Box_556x45_M249_200rnd_Ball.et", 				ESE_ResourceType.LMGBelt);
	static const ResourceName AR_MAG_M249_TRACER 	= CreateAlias("{4EEDDB27C023B8B9}Prefabs/Weapons/Magazines/Box_556x45_M249_200rnd_Tracer.et", 				ESE_ResourceType.LMGBelt);
	static const ResourceName AR_MAG_M249_MIX 		= CreateAlias("{06D722FC2666EB83}Prefabs/Weapons/Magazines/Box_556x45_M249_200rnd_4Ball_1Tracer.et", 		ESE_ResourceType.LMGBelt);
	static const ResourceName AR_MAG_RPK74_BALL 	= CreateAlias("{BC74DAC891D48540}Prefabs/Weapons/Magazines/Magazine_545x39_RPK_45rnd_Ball.et", 				ESE_ResourceType.Magazine);
	static const ResourceName AR_MAG_RPK74_TRACER 	= CreateAlias("{5897D01F41DB5D2D}Prefabs/Weapons/Magazines/Magazine_545x39_RPK_45rnd_Tracer.et", 			ESE_ResourceType.Magazine);
	static const ResourceName AR_MAG_RPK74_MIX 		= CreateAlias("{D78C667F59829717}Prefabs/Weapons/Magazines/Magazine_545x39_RPK_45rnd_4Ball_1Tracer.et", 	ESE_ResourceType.Magazine);
	// LMG'S
	static const ResourceName AR_MAG_M60_BALL 		= CreateAlias("{982F5BA41A3738CF}Prefabs/Weapons/Magazines/Box_762x51_M60_100rnd_Ball.et", 					ESE_ResourceType.LMGBelt);
	static const ResourceName AR_MAG_M60_AP 		= CreateAlias("{75632A0CA07D3817}Prefabs/Weapons/Magazines/Box_762x51_M60_100rnd_AP.et", 					ESE_ResourceType.LMGBelt);
	static const ResourceName AR_MAG_M60_TRACER 	= CreateAlias("{AD8AB93729348C3E}Prefabs/Weapons/Magazines/Box_762x51_M60_100rnd_Tracer.et", 				ESE_ResourceType.LMGBelt);
	static const ResourceName AR_MAG_M60_BALL_MIX	= CreateAlias("{4D2C1E8F3A81F894}Prefabs/Weapons/Magazines/Box_762x51_M60_100rnd_4Ball_1Tracer.et", 		ESE_ResourceType.LMGBelt);
	static const ResourceName AR_MAG_M60_AP_MIX		= CreateAlias("{AAF51CFA75A9CF8B}Prefabs/Weapons/Magazines/Box_762x51_M60_100rnd_4AP_1Tracer.et", 			ESE_ResourceType.LMGBelt);
	static const ResourceName AR_MAG_PKM_100_BALL 	= CreateAlias("{A6737DA00653A39C}Prefabs/Weapons/Magazines/Box_762x54_PK_100rnd_Ball.et",					ESE_ResourceType.LMGBelt);
	static const ResourceName AR_MAG_PKM_100_TRACER = CreateAlias("{BEEA49E27174B224}Prefabs/Weapons/Magazines/Box_762x54_PK_100rnd_Tracer.et", 				ESE_ResourceType.LMGBelt);
	static const ResourceName AR_MAG_PKM_100_MIX 	= CreateAlias("{E5E9C5897CF47F44}Prefabs/Weapons/Magazines/Box_762x54_PK_100rnd_4Ball_1Tracer.et", 			ESE_ResourceType.LMGBelt);
	static const ResourceName AR_MAG_PKM_250_BALL 	= CreateAlias("{1C260E65B7F290BA}Prefabs/Weapons/Magazines/Box_762x54_PK_250rnd_Ball.et", 					ESE_ResourceType.LMGBelt);
	static const ResourceName AR_MAG_PKM_250_TRACER = CreateAlias("{B386EEE8AED8E386}Prefabs/Weapons/Magazines/Box_762x54_PK_250rnd_Tracer.et", 				ESE_ResourceType.LMGBelt);
	static const ResourceName AR_MAG_PKM_250_MIX 	= CreateAlias("{D8421F6E70B2FB4F}Prefabs/Weapons/Magazines/Box_762x54_PK_250rnd_4Ball_1Tracer.et", 			ESE_ResourceType.LMGBelt);
	// HMG'S
	static const ResourceName AR_MAG_M2HB_BALL 		= CreateAlias("{B8921B7BFE8CAEF0}Prefabs/Weapons/Magazines/Box_127x99_M2_100rnd_Ball.et", 					ESE_ResourceType.HeavyWeaponAmmo);
	static const ResourceName AR_MAG_M2HB_AP 		= CreateAlias("{25CE9A2A7EAD5B9D}Prefabs/Weapons/Magazines/Box_127x99_M2_100rnd_AP.et", 					ESE_ResourceType.HeavyWeaponAmmo);
	static const ResourceName AR_MAG_M2HB_TRACER 	= CreateAlias("{4068585808DF8DF2}Prefabs/Weapons/Magazines/Box_127x99_M2_100rnd_Tracer.et", 				ESE_ResourceType.HeavyWeaponAmmo);
	static const ResourceName AR_MAG_M2HB_APT_MIX	= CreateAlias("{50A242E5D9742C62}Prefabs/Weapons/Magazines/Box_127x99_M2_100rnd_4AP_1Tracer.et", 			ESE_ResourceType.HeavyWeaponAmmo);
	static const ResourceName AR_MAG_M2HB_APIT_MIX	= CreateAlias("{C820846B0521423B}Prefabs/Weapons/Magazines/Box_127x99_M2_100rnd_4AP_1APIT.et", 				ESE_ResourceType.HeavyWeaponAmmo);
	static const ResourceName AR_MAG_M2HB_BALLT_MIX	= CreateAlias("{CC7F787C3ECF678F}Prefabs/Weapons/Magazines/Box_127x99_M2_100rnd_4Ball_1Tracer.et", 			ESE_ResourceType.HeavyWeaponAmmo);
	static const ResourceName AR_MAG_KPVT_BASE 		= CreateAlias("{0261DDFDDD21D614}Prefabs/Weapons/Magazines/Box_145x114_KPVT_50rnd_Base.et", 				ESE_ResourceType.HeavyWeaponAmmo);
	static const ResourceName AR_MAG_KPVT_API 		= CreateAlias("{BFD6872B1C069136}Prefabs/Weapons/Magazines/Box_145x114_KPVT_50rnd_API.et", 					ESE_ResourceType.HeavyWeaponAmmo);
	static const ResourceName AR_MAG_KPVT_APIT 		= CreateAlias("{EA806763FE4EDDDF}Prefabs/Weapons/Magazines/Box_145x114_KPVT_50rnd_APIT.et", 				ESE_ResourceType.HeavyWeaponAmmo);
	static const ResourceName AR_MAG_KPVT_MIX 		= CreateAlias("{8257B5AFDE7AE5CB}Prefabs/Weapons/Magazines/Box_145x114_KPVT_50rnd_4API_1APIT.et", 			ESE_ResourceType.HeavyWeaponAmmo);
	#endif
	
	// ----------------------------------------------------------------- UNIFORMS ----------------------------------------------------------------- //
	#ifdef ESE_ALIASES_UNIFORMS
	// TODO
	#endif
	
	// ---------------------------------------------------------------- EQUIPMENT ----------------------------------------------------------------- //
	
	#ifdef ESE_ALIASES_EQUIPMENT
	// TODO
	#endif
	
	// ----------------------------------------------------------------- VEHICLES ----------------------------------------------------------------- //
	
	#ifdef ESE_ALIASES_VEHICLES
	// LIGHT VEHICLES
	static const ResourceName AR_VEH_M151A2					= CreateAlias("{F649585ABB3706C4}Prefabs/Vehicles/Wheeled/M151A2/M151A2.et",  						ESE_ResourceType.MilitaryCar);
	static const ResourceName AR_VEH_M151A2_TRANSPORT		= CreateAlias("{47D94E1193A88497}Prefabs/Vehicles/Wheeled/M151A2/M151A2_transport.et",  			ESE_ResourceType.MilitaryCar);
	static const ResourceName AR_VEH_M151A2_M2HB			= CreateAlias("{F6B23D17D5067C11}Prefabs/Vehicles/Wheeled/M151A2/M151A2_M2HB.et",  					ESE_ResourceType.MilitaryCarArmed);
	
	static const ResourceName AR_VEH_UAZ469					= CreateAlias("{259EE7B78C51B624}Prefabs/Vehicles/Wheeled/UAZ469/UAZ469.et",  						ESE_ResourceType.MilitaryCar);
	// TRUCKS
	static const ResourceName AR_VEH_M923A1					= CreateAlias("{9A0D72816DFFDB7F}Prefabs/Vehicles/Wheeled/M923A1/M923A1.et",  						ESE_ResourceType.MilitaryTruck);
	static const ResourceName AR_VEH_M923A1_TRANSPORT		= CreateAlias("{F1FBD0972FA5FE09}Prefabs/Vehicles/Wheeled/M923A1/M923A1_transport.et",  			ESE_ResourceType.MilitaryTruck);
	static const ResourceName AR_VEH_M923A1_COVERED			= CreateAlias("{81FDAD5EB644CC3D}Prefabs/Vehicles/Wheeled/M923A1/M923A1_transport_covered.et",  	ESE_ResourceType.MilitaryTruck);
	static const ResourceName AR_VEH_M923A1_TANKER			= CreateAlias("{2BE1F8B9299B67C1}Prefabs/Vehicles/Wheeled/M923A1/M923A1_tanker.et",  				ESE_ResourceType.UtilityTruck);
	static const ResourceName AR_VEH_M923A1_COMMAND			= CreateAlias("{36BDCC88B17B3BFA}Prefabs/Vehicles/Wheeled/M923A1/M923A1_command.et",  				ESE_ResourceType.UtilityTruck);
	static const ResourceName AR_VEH_URAL4320				= CreateAlias("{4597626AF36C0858}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320.et",  					ESE_ResourceType.MilitaryTruck);
	static const ResourceName AR_VEH_URAL4320_TRANSPORT		= CreateAlias("{16C1F16C9B053801}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320_transport.et",  		ESE_ResourceType.MilitaryTruck);
	static const ResourceName AR_VEH_URAL4320_COVERED		= CreateAlias("{D9B91FAB817A6033}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320_transport_covered.et",	ESE_ResourceType.MilitaryTruck);
	static const ResourceName AR_VEH_URAL4320_TANKER		= CreateAlias("{4C81D7ED8F8C0D87}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320_tanker.et",  			ESE_ResourceType.UtilityTruck);
	static const ResourceName AR_VEH_URAL4320_COMMAND		= CreateAlias("{1BABF6B33DA0AEB6}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320_command.et",  			ESE_ResourceType.UtilityTruck);
	// MEDIUM VEHICLES
	static const ResourceName AR_VEH_M998					= CreateAlias("{5674FAEB9AB7BDD0}Prefabs/Vehicles/Wheeled/M998/M998.et",  							ESE_ResourceType.ArmouredCar);
	static const ResourceName AR_VEH_M998_COVERED			= CreateAlias("{B55C6990A6A9411B}Prefabs/Vehicles/Wheeled/M998/M998_covered.et",  					ESE_ResourceType.ArmouredCar);
	static const ResourceName AR_VEH_M998_COVERED_LONG		= CreateAlias("{9B1BF9644E0378D6}Prefabs/Vehicles/Wheeled/M998/M998_covered_long.et",  				ESE_ResourceType.ArmouredCar);
	
	static const ResourceName AR_VEH_M1025					= CreateAlias("{4A71F755A4513227}Prefabs/Vehicles/Wheeled/M998/M1025.et",  							ESE_ResourceType.ArmouredCar);
	static const ResourceName AR_VEH_M1025_ARMED_EMPTY		= CreateAlias("{B120CDDBEF8DB007}Prefabs/Vehicles/Wheeled/M998/M1025_armed_base.et",  				ESE_ResourceType.ArmouredCar);
	static const ResourceName AR_VEH_M1025_ARMED_M2HB		= CreateAlias("{3EA6F47D95867114}Prefabs/Vehicles/Wheeled/M998/M1025_armed_M2HB.et",  				ESE_ResourceType.ArmouredCarArmed);
	
	static const ResourceName AR_VEH_BTR70					= CreateAlias("{C012BB3488BEA0C2}Prefabs/Vehicles/Wheeled/BTR70/BTR70.et",  						ESE_ResourceType.APC);
	#endif
	
	#ifdef ESE_ALIASES_DEBUG
	private static const autoptr array<string> m_pEnumLookupArray = 
	{
	"Handgun",
	"SubmachineGun",
	"Shotgun",
	"AssaultRifle",
	"Carbine",
	"MarksmanRifle",
	"SniperRifle",
	"SquadAutomaticWeapon",
	"MachineGun",
	"GrenadeLauncher",
	"RocketLauncher",
	"AntiAirLauncher",
	"AntiTankLauncher",
	"LethalGrenade",
	"SmokeGrenade",
	"UtilityGrenade",
	"OtherWeapon",
	"Optic",
	"UnderbarrelWeapon",
	"Bayonet",
	"Handguard",
	"Grip",
	"RailAttachment",
	"Muzzle",
	"OtherAttachment",
	"Magazine",
	"LMGBelt",
	"UGLGrenade",
	"RocketAmmo",
	"MissileAmmo",
	"HeavyWeaponAmmo",
	"CivillianCar",
	"CivillianTruck",
	"MilitaryCar",
	"MilitaryCarArmed",
	"MilitaryTruck",
	"UtilityTruck",
	"ArmouredCar",
	"ArmouredCarArmed",
	"APC",
	"LightTank",
	"HeavyTank",
	"TankDestroyer",
	"OtherVehicle",
	"CivillianHeli",
	"LightTransportHeli",
	"LightAttackHeli",
	"TransportHeli",
	"AttackHeli",
	"OtherHeli",
	"CivillianPlane",
	"TransportPlane",
	"AttackPlane",
	"FighterPlane",
	"VTOLPlane",
	"OtherPlane",
	"CivillianUAV",
	"ReconUAV",
	"ArmedUAV",
	"ReconUGV",
	"ArmedUGV",
	"OtherDrone",
	"CivillianBoat",
	"LightBoat",
	"AttackBoat",
	"LandingCraft",
	"OtherBoat",
	"CivillianShip",
	"Cruiser",
	"Destroyer",
	"AircraftCarrier",
	"UtilityShip",
	"OtherShip",
	"EntityMaterial",
	"Generic",
	"None"
	}
	#endif
}

enum ESE_ResourceType
{
	// weapons
	Handgun,
	SubmachineGun,
	Shotgun,
	AssaultRifle,
	Carbine,
	MarksmanRifle,
	SniperRifle,
	SquadAutomaticWeapon,
	MachineGun,
	GrenadeLauncher,
	RocketLauncher,
	AntiAirLauncher,
	AntiTankLauncher,
	LethalGrenade,
	SmokeGrenade,
	UtilityGrenade,
	OtherWeapon,
	// attachments
	Optic,
	UnderbarrelWeapon,
	Bayonet,
	Handguard,
	Grip,
	RailAttachment,
	Muzzle,
	OtherAttachment,
	// magazines
	Magazine,
	LMGBelt,
	UGLGrenade,
	RocketAmmo,
	MissileAmmo,
	HeavyWeaponAmmo,
	// land vehicles
	CivillianCar,
	CivillianTruck,
	MilitaryCar,
	MilitaryCarArmed,
	MilitaryTruck,
	UtilityTruck,
	ArmouredCar,
	ArmouredCarArmed,
	APC,
	LightTank,
	HeavyTank,
	TankDestroyer,
	OtherVehicle,
	// helicopters
	CivillianHeli,
	LightTransportHeli,
	LightAttackHeli,
	TransportHeli,
	AttackHeli,
	OtherHeli,
	// planes
	CivillianPlane,
	TransportPlane,
	AttackPlane,
	FighterPlane,
	VTOLPlane,
	OtherPlane,
	// drones
	CivillianUAV,
	ReconUAV,
	ArmedUAV,
	ReconUGV,
	ArmedUGV,
	OtherDrone,
	// boats
	CivillianBoat,
	LightBoat,
	AttackBoat,
	LandingCraft,
	OtherBoat,
	// ships
	CivillianShip,
	Cruiser,
	Destroyer,
	AircraftCarrier,
	UtilityShip,
	OtherShip,
	// other
	EntityMaterial,
	Generic,
	None
}