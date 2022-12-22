[WorkbenchPluginAttribute(name: "ESE Configuration", description: "Settings for setting up ESE.", shortcut: "ctrl+e", wbModules: null, category: "ESE", awesomeFontCode: 0xf7d9)]
class ESE_ConfigurationPlugin: WorkbenchPlugin
{
	[Attribute()]
	protected bool m_bEnableDiscordRichPresence;
	
	
	
	protected ScriptEditor scriptEditor;
	
	override void Run()
	{
		Print("Config Opened (HIII :3)");	
		scriptEditor = Workbench.GetModule(ScriptEditor);
		if (Workbench.ScriptDialog("ESE Configuration", "", this) && Workbench.OpenModule(ScriptEditor))
		{
			// -------------------------------- DiscordRP -------------------------------- //
			if (DISCORD_RICH_PRESENCE_ENABLED == m_bEnableDiscordRichPresence)
			{
				Print("Doing nothing");
				// do nothing
			}
			else if (m_bEnableDiscordRichPresence)
			{
				DISCORD_RICH_PRESENCE_ENABLED = m_bEnableDiscordRichPresence;
				DiscordRP.WriteEnabledState(DISCORD_RICH_PRESENCE_ENABLED);
				
				// kill any potential existing process
				Workbench.KillProcess(DISCORD_RICH_PRESENCE_HANDLE);
				DISCORD_RICH_PRESENCE_RUNNING = false;
				
				// launch new rich presence executable
				DISCORD_RICH_PRESENCE_HANDLE = Workbench.RunProcess(DiscordRP.GetExecutablePath(true));
				DISCORD_RICH_PRESENCE_RUNNING = true;
				thread DiscordRP_Run();
			}
			else
			{
				DISCORD_RICH_PRESENCE_ENABLED = m_bEnableDiscordRichPresence;
				DiscordRP.WriteEnabledState(DISCORD_RICH_PRESENCE_ENABLED);
				Workbench.KillProcess(DISCORD_RICH_PRESENCE_HANDLE);
				DISCORD_RICH_PRESENCE_RUNNING = false;
			}
			// ------------------------------------   ------------------------------------ //
		}
	}
	
	void ESE_ConfigurationPlugin() {}
	
	[ButtonAttribute("Close")]
	bool ButtonClose() {return false;}
	[ButtonAttribute("OK")]
	bool ButtonOk() {return true;}
}