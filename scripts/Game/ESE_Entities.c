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
		vector mat = someEntity.GetTransform();
		ResourceName resName = "{3E413771E1834D2F}Prefabs/Weapons/Rifles/M16/Rifle_M16A2.et";
	
		IEntity newEntity = ESE.SpawnPrefab(mat, resource);
	@endcode
	*/
	// #ESE_UPDATE_DOCUMENTATION - changed from using origin to transform
	static IEntity SpawnPrefab(vector transform[4], ResourceName prefabName)
	{
		if (!prefabName)
		{
			Print("Missing Prefab: " + prefabName, LogLevel.ERROR);
			return null;
		}
		if (!transform)
		{
			Print("No valid transform! Using default transform instead.", LogLevel.WARNING);
			Math3D.MatrixIdentity4(transform)
		}
		Resource prefab = Resource.Load(prefabName);
		EntitySpawnParams spawnParams = new EntitySpawnParams();
		spawnParams.TransformMode = ETransformMode.WORLD;
		spawnParams.Transform = transform;
		
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
	
	static void DisableCollisions(IEntity ent, bool applyToChildren=true)
	{
		Physics parentPhys = ent.GetPhysics();
		if (parentPhys)
			parentPhys.Destroy();
		
		if (!applyToChildren)
			return;
		
		IEntity child = ent.GetChildren();
		while (child)
		{
			Physics p = child.GetPhysics();
			if (!p)
			{
				child = child.GetSibling();
				continue;
			}
			p.Destroy();
			child = child.GetSibling();
		}
	}
	// -----------------------------------------------------------------------------------------------------------
	static void EnableCollisions(IEntity ent, bool applyToChildren=true, int layerMask = 0xffffffff)
	{
		Physics.CreateStatic(ent, layerMask);
		if (!applyToChildren)
			return;		
		
		IEntity child = ent.GetChildren();
		while (child)
		{
			Physics.CreateStatic(child, layerMask);
			child = child.GetSibling();
		}
	}
	// -----------------------------------------------------------------------------------------------------------
	// #ESE_ADD_DOCUMENTATION
	/**
	Snaps given entity to whatever is underneath it as long as it is less than maxHeight away.
	Similar to SCR_TerrainHelper.SnapToTerrain() but uses a trace so it will snap to any entity not just the world terrain
	
	\param ent - the entity to have it's position snapped
	\param maxHeight - the max distance the trace will move looking for a valid entity or terrain to snap to - HIGHER VALUES HAVE A HIGHER PERFORMANCE COST
	\param noUnderwater - whether the entity will get snapped to the water surface or sea floor if used over water - #ESE_TODO
	*/
	static void SnapToGround(out vector transform[4], IEntity ent, int maxHeight, bool noUnderwater = false)
	{
		BaseWorld world = GetGame().GetWorld();
		// if noUnderwater is true, check if terrain height at pos with noUnderwater true is the same as the ocean height
		// if this is true, we know we are over the ocean so can snap the entity to the water surface
		if (noUnderwater)
		{
			vector pos = transform[3];
			float terrainHeight = SCR_TerrainHelper.GetTerrainY(pos, world, true);
			if (terrainHeight == world.GetOceanBaseHeight())
			{
				pos[1] = world.GetOceanBaseHeight();
				transform[3] = pos;
				return;
			}
		}
		vector dir = "0 -1 0";
		dir[1] = dir[1] * maxHeight;
		vector startPos = transform[3];
		
		autoptr TraceParam trace = new TraceParam();
		trace.Start = startPos;
		trace.End = startPos + dir;
		trace.Flags = TraceFlags.WORLD | TraceFlags.ENTS;
		trace.LayerMask = TRACE_LAYER_CAMERA;
		trace.Exclude = ent;
		
		// #ESE_TODO - change this to whatever is needed now that noUnderwater is checked at the start
		if (startPos[1] > world.GetOceanBaseHeight())
		{
			trace.Flags = trace.Flags | TraceFlags.OCEAN;
		}
		float traceDist = world.TraceMove(trace, null);
		Print(traceDist);
		
		// check if trace reached maxHeight without hitting anything
		if (traceDist >= maxHeight)
		{
			Print("traceDist > maxHeight");
			return;
		}
		vector endpos = startPos + dir * traceDist;
		Print(startPos);
		Print(dir);
		Print(endpos);
		transform[3] = endpos;
	}
	// -----------------------------------------------------------------------------------------------------------
	// #ESE_ADD_DOCUMENTATION
	static void SnapAndOrientToGround(out vector transform[4], IEntity ent, int maxHeight, bool noUnderwater = false)
	{
		BaseWorld world = GetGame().GetWorld();
		// if noUnderwater is true, check if terrain height at pos with noUnderwater true is the same as the ocean height
		// if this is true, we know we are over the ocean so can snap the entity to the water surface
		if (noUnderwater)
		{
			vector pos = transform[3];
			float terrainHeight = SCR_TerrainHelper.GetTerrainY(pos, world, true);
			if (terrainHeight == world.GetOceanBaseHeight())
			{
				pos[1] = world.GetOceanBaseHeight();
				transform[3] = pos;
				return;
			}
		}
		vector dir = "0 -1 0";
		dir[1] = dir[1] * maxHeight;
		vector startPos = transform[3];
		
		autoptr TraceParam trace = new TraceParam();
		trace.Start = startPos;
		trace.End = startPos + dir;
		trace.Flags = TraceFlags.WORLD | TraceFlags.ENTS;
		trace.LayerMask = TRACE_LAYER_CAMERA;
		trace.Exclude = ent;
		
		// #ESE_TODO - change this to whatever is needed now that noUnderwater is checked at the start
		if (startPos[1] > world.GetOceanBaseHeight())
		{
			trace.Flags = trace.Flags | TraceFlags.OCEAN;
		}
		float traceDist = world.TraceMove(trace, null);
		// check if trace reached maxHeight without hitting anything
		if (traceDist >= maxHeight)
		{
			Print("traceDist > maxHeight");
			return;
		}
		vector endpos = startPos + dir * traceDist;
		transform[3] = endpos;
		
		// orient
		vector normal = trace.TraceNorm;
		vector perpend = normal.Perpend();
		vector result[4];
		
		Math3D.DirectionAndUpMatrix(perpend, normal, result);
		
		vector basis[4];
		Math3D.AnglesToMatrix(Vector(-perpend.VectorToAngles()[0], 0, 0), basis);
		Math3D.MatrixMultiply3(result, basis, result);
		result[3] = endpos;
		
		Math3D.MatrixMultiply3(result, transform, transform);
	}
	
	// ------------------------------------------------------------- MODELS & MATERIALS ------------------------------------------------------------- //
	
	// #ESE_ADD_DOCUMENTATION
	// To be safe, use a string[256] array as the input for materials, use less for memory optimasation though if needed
	static void GetMaterial(IEntity entity, out string materials[], out int numMaterials)
	{
		VObject mesh = entity.GetVObject();
		if (mesh)
		{
			numMaterials = mesh.GetMaterials(materials);
		}
	}
	
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