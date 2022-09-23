// -----------------------------------------------------------------------------------------------------------
// Enforce Script Extensions - By NarcoMarshmallow
// 
// Message me @narcoleptic marshmallow #1188 on discord to give feedback or go to https://github.com/NarcoMarshDev
// -----------------------------------------------------------------------------------------------------------


// Different functionality of ESE can be enabled or disabled by defining some different values, go to ESE_Config.c to see how

class ESE
{
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
	// -----------------------------------------------------------------------------------------------------------
	// Deletes entity on server side
	static void DeleteEntity(IEntity ent)
	{
		RplComponent.DeleteRplEntity(ent, false);
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
	// Returns alive state of given entity
	static bool IsEntityAlive(IEntity entity)
	{
		DamageManagerComponent damageManager = DamageManagerComponent.Cast(entity.FindComponent(DamageManagerComponent));
		if (damageManager)
			return damageManager.GetState() != EDamageState.DESTROYED;
		else
			return true;
	}
	// -----------------------------------------------------------------------------------------------------------
	#ifdef ESE_ENABLE_WIP
	/**
	TODO - MAKE SURE THIS WORKS AS INTENDED ON LOCAL PLAYERS WHEN CALLED
	Returns true if given entity is visible on local screen, false otherwise
	@code
	@endcode
	*/
	static bool IsEntityOnScreen(IEntity ent)
	{
		WorkspaceWidget workspace = GetGame().GetWorkspace();
		float width, height;
		workspace.GetScreenSize(width, height);
		
		vector worldPos = ent.GetOrigin();
		if (!worldPos)
			return false;
		
		vector screenPos = workspace.ProjWorldToScreenNative(worldPos, GetGame().GetWorld());
		return screenPos[2] > 0 && screenPos[0] > 0 && screenPos[0] < width && screenPos[1] > 0 && screenPos[1] < height);
	}
	#endif
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