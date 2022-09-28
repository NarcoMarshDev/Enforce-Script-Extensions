// -----------------------------------------------------------------------------------------------------------
// Enforce Script Extensions - By NarcoMarshmallow
// 
// Message me @narcoleptic marshmallow #1188 on discord to give feedback or go to https://github.com/NarcoMarshDev
//
// All static methods for working with entities and the hierarchy
// -----------------------------------------------------------------------------------------------------------

class ESE_Entities
{
	// ESE static methods for handling entities. Will add to IEntity if we get modded class support for core classes
	
	// ---------------------------------------------------------------- SPAWNING ---------------------------------------------------------------- //
	
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
		if (!origin)
		{
			origin = Vector(0,0,0);
		}
		Resource prefab = Resource.Load(prefabName);
		EntitySpawnParams spawnParams;
		spawnParams.TransformMode = ETransformMode.WORLD;
		spawnParams.Transform[3] = origin;
		
		return GetGame().SpawnEntityPrefab(prefab, GetGame().GetWorld(), spawnParams);
	}
	// -----------------------------------------------------------------------------------------------------------
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
	// -----------------------------------------------------------------------------------------------------------
	// Deletes entity on server side
	static void DeleteEntity(IEntity ent)
	{
		RplComponent.DeleteRplEntity(ent, false);
	}
	// -----------------------------------------------------------------------------------------------------------
	static void DeleteEntityByRplId(RplId id)
	{
		IEntity ent = IEntity.Cast(Replication.FindItem(id));
		RplComponent.DeleteRplEntity(ent, false);
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
	
	// ------------------------------------------------------------- PHYSICS & COLLISION ------------------------------------------------------------- //
	
	static void DisableCollisions(IEntity ent)
	{
		Physics parentPhys = ent.GetPhysics();
		if (parentPhys)
		{
			parentPhys.Destroy();
		}
		IEntity child = ent.GetChildren();
		int i = 0;
		while (child)
		{
			Physics p = child.GetPhysics();
			if (!p)
			{
				Print("child: " + child + " no p " + i);
				i++;
				child = child.GetSibling();
				continue;
			}
			Print("child: " + child + " yes p " + i);
			i++;
			p.Destroy();
			child = child.GetSibling();
		}
	}
	// -----------------------------------------------------------------------------------------------------------
	static void EnableCollisions(IEntity ent, int layerMask = 0xffffffff)
	{
		Physics.CreateStatic(ent, layerMask);
		IEntity child = ent.GetChildren();
		while (child)
		{
			Physics.CreateStatic(child, layerMask);
			child = child.GetSibling();
		}
	}
	
	// ------------------------------------------------------------- MODELS & MATERIALS ------------------------------------------------------------- //
	
	// See SCR_Global.SetMaterial() - A copy to help with readability
	static void SetMaterial(IEntity entity, ResourceName material, bool recursively = true)
	{
		//--- Remap textures of the current mesh
		VObject mesh = entity.GetVObject();
		if (mesh)
		{
			string remap;
			string materials[256];
			int numMats = mesh.GetMaterials(materials);
			for (int i = 0; i < numMats; i++)
			{
				remap += string.Format("$remap '%1' '%2';", materials[i], material);
			}
			entity.SetObject(mesh, remap);
		}
		
		//--- Iterate through children
		if (recursively)
		{
			IEntity child = entity.GetChildren();
			while (child)
			{
				SetMaterial(child, material);
				child = child.GetSibling();
			}
		}
	}
	// -----------------------------------------------------------------------------------------------------------
	/**
	Restores materials of entity and optionally it's children back to its original state
	\param entity - entity to have materials reset
	\param restoreChildren - true to reset the material of all children too
	*/
	static void RestoreMaterial(IEntity entity, bool restoreChildren)
	{
		switch (restoreChildren)
		{
			case true:
				
				IEntity child = entity;
				while (child)
				{
					VObject vobj = child.GetVObject();
					if (!vobj)
					{
						child = child.GetChildren();
						continue;
					}
					ResourceName resName;
					string remap;
					SCR_Global.GetModelAndRemapFromResource(vobj.GetResourceName(), resName, remap);
					child.SetObject( Resource.Load(resName).GetResource().ToVObject(), "");
					child = child.GetChildren();
				}
				break;
			
			case false:
				VObject vobj = entity.GetVObject();
				if (!vobj)
				{
					return;
				}
				ResourceName resName;
				string remap;
				SCR_Global.GetModelAndRemapFromResource(vobj.GetResourceName(), resName, remap);
				entity.SetObject( Resource.Load(resName).GetResource().ToVObject(), "");
				break;
		}
	}
		
	// ================================ WIP ================================
	#ifdef ESE_ENABLE_WIP
	
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
	// -----------------------------------------------------------------------------------------------------------
	//TODO - Not sure why it's not working but don't use it for now, may have to go back to the GetParent() -> GetAllChildren() type system
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