// -----------------------------------------------------------------------------------------------------------
// Enforce Script Extensions - By NarcoMarshmallow
// 
// Message me @narcoleptic marshmallow #1188 on discord to give feedback or go to https://github.com/NarcoMarshDev
// -----------------------------------------------------------------------------------------------------------


// Different functionality of ESE can be enabled or disabled by defining some different values, go to ESE_Config.c to see how
/**
ESE Class

Class containing generic static methods and constants

For full documentation check the wiki @ https://github.com/NarcoMarshDev/Enforce-Script-Extensions/wiki/ESE-Class

Code example:
@code
	TODO
@endcode
*/
class ESE
{	
	static const int VERSION_MAJOR = 0;
	static const int VERSION_MINOR = 1;
	static const int VERSION_PATCH = 2;
	// initialize ese on startup, called in !ESE_CORE.c
	static bool Init()
	{
		if (ESE_IS_INITIALIZED)
		{
			Print("ESE.Init() already called", LogLevel.WARNING);
			return true;
		}
		
		// print version info on init
		Print("Loaded ESE v" + VERSION_MAJOR + "." + VERSION_MINOR + "." + VERSION_PATCH);
		if (VERSION_MAJOR == 0)
		{
		Print("WARNING: This is a pre-release version of Enforce Script Extensions, future compatibility is not guaranteed!", LogLevel.WARNING);
		}
		
		// get all addons and find the first one (the currently open project)
		array<string> availableAddons = {};
		GameProject.GetAvailableAddons(availableAddons);
		string mainProjectName = GameProject.GetAddonTitle(availableAddons[0]);
		if (mainProjectName == "Enforce Script Extensions")
		{
			#ifdef ESE_DEVMODE
			Print("ESE is in development mode, remember to goto !ESE_Config_EnforceScriptExtensions.c and disable before release", LogLevel.WARNING);
			#endif
			#ifndef ESE_DEVMODE
			Print("ESE is not in development mode, goto !ESE_Config_EnforceScriptExtensions.c and enable it to access all features", LogLevel.WARNING);
			#endif
		}
				
		return true;
	}
	
	// Base class for all ESE static methods, if we ever get modding support for core types many of these will get added to their respective classes as well
	
	// ================================ Entities ================================
	
	/**
	Outputs array of all child entities of a given parent, children must have "Hierarchy" component to be picked up
	@code
		array<IEntity> arr = {};
		ESE.GetAllChildren(this, arr);
	@endcode
	*/
	static array<IEntity> GetAllChildren(IEntity parent)
	{
		if (!parent)
		{
			#ifdef ESE_VERBOSE
			Print("GetAllChildren("+parent+") : NULL parent", LogLevel.VERBOSE);
			#endif
			return null;
		}
		array<IEntity> allChildren = {};
		IEntity child = parent.GetChildren();
		while (child)
		{
			allChildren.Insert(child);
			child = child.GetSibling();
		}
		return allChildren;
	}
	// -----------------------------------------------------------------------------------------------------------
	// See ESE.GetAllChildren - Returns only entities of given type
	static array<IEntity> GetAllChildrenByType(IEntity parent, typename childClass)
	{
		if (!parent || !childClass)
		{
			#ifdef ESE_VERBOSE
			Print("GetAllChildrenByClass("+parent+", "+childClass+") : NULL parent or childClass", LogLevel.VERBOSE);
			#endif
			return null;
		}
		array<IEntity> allChildren = {};
		IEntity child = parent.GetChildren();
		while (child)
		{
			if (child.IsInherited(childClass))
			{
				allChildren.Insert(child);
			}
			child = child.GetSibling();
		}
		return allChildren;
	}
	
	// ================================ Player ================================
	
	// Returns player controlled entity from given playerId
	static ChimeraCharacter GetPlayerEntity(int playerId)
	{
		return ChimeraCharacter.Cast( GetGame().GetPlayerManager().GetPlayerControlledEntity(playerId) );
	}
	// -----------------------------------------------------------------------------------------------------------
	// Returns player controlled entity of local machine
	static ChimeraCharacter GetLocalPlayerEntity()
	{
		return ChimeraCharacter.Cast( GetGame().GetPlayerController().GetControlledEntity() );
	}
	// -----------------------------------------------------------------------------------------------------------
	// Returns player id of given entity, returns 0 if not controlled by player
	static int GetPlayerId(IEntity ent)
	{
		return GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(ent);
	}
	// -----------------------------------------------------------------------------------------------------------
	// Returns currently equipped weapon of given player character, returns null if weapon is holstered
	static BaseWeaponComponent GetCurrentWeapon(ChimeraCharacter player)
	{
		return player.GetCharacterController().GetWeaponManagerComponent().GetCurrentWeapon();
	}
	// -----------------------------------------------------------------------------------------------------------
	// Pretty obvious
	static void HolsterCurrentWeapon(ChimeraCharacter player)
	{
		player.GetCharacterController().SelectWeapon(null);
	}
	// -----------------------------------------------------------------------------------------------------------
	/**
	Outputs all available magazines for a given weapon and character into a MagazineComponent array
	@code
		ChimeraCharacter player = ESE.GetLocalPlayerEntity();
		BaseWeaponComponent weapon = ESE.GetCurrentWeapon(player);
		array<MagazineComponent> arr = {};
	
		ESE.FetchMagazines(player, weapon, arr);
	@endcode
	*/
	static void FetchMagazines(ChimeraCharacter character, BaseWeaponComponent weapon, inout array<MagazineComponent> magazines)
	{
		magazines.Clear();
		if (!character || !weapon || !weapon.GetCurrentMuzzle())
			return;

		InventoryStorageManagerComponent inventory = character.GetCharacterController().GetInventoryStorageManager();
		if (!inventory)
			return;

		BaseMuzzleComponent currentMuzzle = weapon.GetCurrentMuzzle();
		if (!currentMuzzle)
			return;

		array<typename> components = {};
		array<IEntity> foundItems = {};
        components.Insert(MagazineComponent);

		BaseMagazineWell targetWell = currentMuzzle.GetMagazineWell(); // Well, well, well
		if (!targetWell)
			return;

		for (int i = inventory.FindItemsWithComponents(foundItems,components, EStoragePurpose.PURPOSE_ANY) -1; i > -1; i--)
		{
			MagazineComponent magComp = MagazineComponent.Cast(foundItems[i].FindComponent(MagazineComponent));
			if (!magComp)
				continue;
			
			BaseMagazineWell well = magComp.GetMagazineWell();
			if (!well)
				continue;
			
			if (!well.Type().IsInherited(targetWell.Type()))
				continue;

			magazines.Insert(magComp);
		}
	}
	// ================================ WIP ================================
	#ifdef ESE_ENABLE_WIP
	
	/**
	TODO - Not sure why it's not working but don't use it for now, may have to go back to the GetParent() -> GetAllChildren() type system
	*/
	static void GetAllSiblings(IEntity ent, notnull inout array<IEntity> allSiblings)
	{
		if (!ent)
		{
			#ifdef ESE_VERBOSE
			Print("GetAllSiblings("+ent+", "+allSiblings+") : NULL ent", LogLevel.VERBOSE);
			#endif
			return;
		}
			
		IEntity sibling = ent.GetSibling();
		Print("siblingpre: " + sibling);
		while (sibling)
		{
			Print("sibling: " + sibling);
			allSiblings.Insert(sibling);
			sibling = sibling.GetSibling();
		}
	}
	
	
	#endif
}