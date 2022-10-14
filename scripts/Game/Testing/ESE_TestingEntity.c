class ESE_TestingEntityClass : SCR_BaseTriggerEntityClass
{
}

class ESE_TestingEntity : SCR_BaseTriggerEntity
{
	protected override void EOnInit(IEntity owner)
	{
		GetGame().GetGameMode();
	}
	
	protected override void EOnFrame(IEntity owner, float timeSlice)
	{
		
	}
}