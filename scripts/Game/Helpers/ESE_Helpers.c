class ESE_GetComponent<Class T>
{
	static T FindFirst(IEntity ent)
	{
		return T.Cast(ent.FindComponent(T));
	}
	
	static array<T> FindAll(IEntity ent)
	{
		array<Managed> managedArray = {};
		ent.FindComponents(T, managedArray);
		
		array<T> castedArray = {};
		foreach (Managed item: managedArray)
		{
			castedArray.Insert(T.Cast(item));
		}
		return castedArray;
	}
}
//------------------------------------------------------------------------------------------------

class ESE_InventoryHelper
{
	static SCR_InventoryStorageManagerComponent GetInventoryStorageManager(IEntity ent)
	{
		return SCR_InventoryStorageManagerComponent.Cast(ent.FindComponent(SCR_InventoryStorageManagerComponent));
	}
	
	static array<ResourceName> GetItemResources(SCR_InventoryStorageManagerComponent manager)
	{
		if (!manager)
			return null;
		
		array<IEntity> entities = {};
		array<ResourceName> resources = {};
		if (manager.GetItems(entities) > 0)
		{
			foreach (IEntity item: entities)
			{
				resources.Insert(item.GetPrefabData().GetPrefabName());
			}
		}
		return resources;
	}
}
//------------------------------------------------------------------------------------------------