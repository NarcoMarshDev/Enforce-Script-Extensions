// ----- File Generated By ESE Plugin Generator ----- //

[WorkbenchPluginAttribute(name: "View Documentation...", description: "View official ESE documentation on github", shortcut: "", icon: "", wbModules: {"ScriptEditor"}, category: "ESE", awesomeFontCode: 0xf518)]
class ESE_ViewDocumentationPlugin: WorkbenchPlugin
{
	// Reference to workbench module
	protected ScriptEditor m_scriptEditor;

	override void Run()
	{
		m_scriptEditor = Workbench.GetModule(ScriptEditor);
		PlatformService service = new PlatformService();
		service.OpenBrowser("https://github.com/NarcoMarshDev/Enforce-Script-Extensions/wiki");
	}

	override void RunCommandline() {}

	override void Configure() {}

	void ESE_ViewDocumentationPlugin() {}
}
