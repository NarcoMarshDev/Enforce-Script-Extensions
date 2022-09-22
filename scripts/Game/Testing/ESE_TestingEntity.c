class ESE_TestingEntityClass : SCR_BaseTriggerEntityClass
{
}

class ESE_TestingEntity : SCR_BaseTriggerEntity
{
	protected override void EOnInit(IEntity owner)
	{
		Print("" + this + "loaded");
		
		array<IEntity> arr = ESE.GetAllChildrenByType(this, GenericEntity);
		
		Print("arr: " + arr);
		Print("len: " + arr.Count());
		
		
	}
	
	protected override void EOnFrame(IEntity owner, float timeSlice)
	{
		
		ResourceName test = ESE_Aliases.WEP_M21;
		//bool onScreen = ESE.IsEntityOnScreen(owner);
		//Print("onScreen: " + onScreen);
	}
}