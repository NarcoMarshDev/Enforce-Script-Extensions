class ESE_TestingEntityClass : SCR_BaseTriggerEntityClass
{
}

class ESE_TestingEntity : SCR_BaseTriggerEntity
{
	protected override void EOnInit(IEntity owner)
	{
		ESE_Aliases.DebugRegister();
		ESE_Aliases.RemoveAliasFromRegister(ESE_Aliases.TEST_WEP_M18_RED);
		ESE_Aliases.DebugRegister();
	}
	
	protected override void EOnFrame(IEntity owner, float timeSlice)
	{
		
		ResourceName test = ESE_Aliases.WEP_M21;
		//bool onScreen = ESE.IsEntityOnScreen(owner);
		//Print("onScreen: " + onScreen);
	}
}