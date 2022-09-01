//
// Enforce Script Extensions - By NarcoMarshmallow
// 
// Message me @narcoleptic marshmallow #1188 on discord to give feedback or go to https://github.com/NarcoMarshDev
//
#define ESE_VERBOSE
//#define ESE_ENABLE_WIP
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
	/**
	Creates new entity from prefab at a given position vector
	@code
		vector pos = someEntity.GetOrigin();
		ResourceName resName = "{3E413771E1834D2F}Prefabs/Weapons/Rifles/M16/Rifle_M16A2.et";
	
		IEntity newEntity = ESE.SpawnPrefab(pos, resource);
	@endcode
	*/
	static IEntity SpawnPrefab(vector origin, ResourceName prefabName)
	{
		if (!prefabName)
		{
			Print("Missing Prefab: " + prefabName, LogLevel.ERROR);
			return null;
		}
		Resource prefab = Resource.Load(prefabName);
		EntitySpawnParams spawnParams;
		spawnParams.TransformMode = ETransformMode.WORLD;
		spawnParams.Transform[3] = origin;
		
		return GetGame().SpawnEntityPrefab(prefab, GetGame().GetWorld(), spawnParams);
	}
	/**
	Creates new entity from prefab at a players position
	@code
		ResourceName resName = "{3E413771E1834D2F}Prefabs/Weapons/Rifles/M16/Rifle_M16A2.et";
	
		IEntity newEntity = ESE.SpawnPrefabOnPlayer(playerId, resName);
	@endcode
	*/
	static IEntity SpawnPrefabOnPlayer(int playerId, ResourceName prefabName)
	{
		if (!prefabName)
		{
			Print("Missing Prefab: " + prefabName, LogLevel.ERROR);
			return null;
		}
		ChimeraCharacter player = ESE.GetPlayerEntity(playerId);
		Resource prefab = Resource.Load(prefabName);
		EntitySpawnParams spawnParams;
		spawnParams.TransformMode = ETransformMode.WORLD;
		player.GetWorldTransform(spawnParams.Transform);
		
		return GetGame().SpawnEntityPrefab(prefab, player.GetWorld(), spawnParams);
	}
	// Deletes entity on server side
	static void DeleteEntity(IEntity ent)
	{
		RplComponent.DeleteRplEntity(ent, false);
	}
	
	
	// ================================ Player ================================
	
	// Returns player controlled entity
	static ChimeraCharacter GetPlayerEntity(int playerId)
	{
		return ChimeraCharacter.Cast( GetGame().GetPlayerManager().GetPlayerControlledEntity(playerId) );
	}
	// Returns player id of given entity, returns 0 if not controlled by player
	static int GetPlayerId(IEntity ent)
	{
		return GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(ent);
	}
	// Returns alive state of given entity
	static bool IsEntityAlive(IEntity entity)
	{
		DamageManagerComponent damageManager = DamageManagerComponent.Cast(entity.FindComponent(DamageManagerComponent));
		if (damageManager)
			return damageManager.GetState() != EDamageState.DESTROYED;
		else
			return true;
	}
	/**
	TODO - MAKE SURE THIS WORKS AS INTENDED ON LOCAL PLAYERS WHEN CALLED
	Returns if given entity is visible on local screen
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
	
	// ================================ WIP ================================
	#ifdef ESE_ENABLE_WIP
	
	//*
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