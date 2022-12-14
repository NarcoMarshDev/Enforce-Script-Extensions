enum EWorkbenchModules
{
	ParticleEditor,
	AnimEditor,
	AudioEditor,
	BehaviorEditor,
	NavmeshGeneratorMain,
	ProcAnimEditor,
	ScriptEditor,
	ResourceManager,
	WorldEditor,
	LocalizationEditor
}

[WorkbenchPluginAttribute(name: "Generate New Workbench Plugin", description: "Creates a new plugin class", shortcut: "", wbModules: {"ScriptEditor"}, category: "ESE", awesomeFontCode: 0xf1c9)]
class ESE_GenerateNewPlugin: WorkbenchPlugin
{
	[Attribute(defvalue: "$ArmaReforger (change me!)", category: "Location")]
	protected string m_sAddon;
	
	[Attribute(defvalue: "scripts/WorkbenchGame/", category: "Location")]
	protected string m_sFilePath;
	
	[Attribute(defvalue: "NewPlugin", category: "Setup")]
	protected string m_sName;
	
	[Attribute(defvalue: "Plugin Description", category: "Setup")]
	protected string m_sDescription;
	
	[Attribute(desc: "Key combination shortcut to open or run the plugin", category: "Setup")]
	protected string m_sShortcut;
	
	[Attribute(desc: "The icon used for the plugin (Optional)", uiwidget: UIWidgets.FileNamePicker, params: "edds", category: "Setup")]
	protected string m_sIcon;
	
	[Attribute(defvalue: "ScriptEditor", desc: "The workbench modules the plugin is available in.", uiwidget: UIWidgets.ComboBox, enums: ParamEnumArray.FromEnum(EWorkbenchModules), category: "Setup")]
	protected string m_sModule;
	
	[Attribute(desc: "The sub menu the plugin appears under in the 'Plugins' menu. Will share if one already exists or create a new one", category: "Setup")]
	protected string m_sSubMenu;
	
	[Attribute(defvalue: "f7d9", desc: "Check 'fontawesome.com/cheatsheet' for text symbols to reference here via integer", uiwidget: UIWidgets.LocaleEditBox, category: "Setup")]
	protected int m_sAwesomeFontCode;
	
	[Attribute(uiwidget: UIWidgets.Button, category: "Setup")]
	protected bool m_bCreateWithUI;
	
	[Attribute(uiwidget: UIWidgets.Object, category: "Attributes - Write as 'Type name;' (optional)")]
	protected ref array<string> m_sAttributes = {};
	
	protected ScriptEditor scriptEditor;
	protected string doubleQuote;
	
	string Quotify(string str)
	{
		return doubleQuote + str + doubleQuote;
	}
	
	string VarNameFromType(string str)
	{
		string firstChar = str.Get(0);
		firstChar.ToLower();
		str = str.Substring(1, str.Length() - 1);
		return "m_" + firstChar + str;
	}
	
	override void Run()
	{
		scriptEditor = Workbench.GetModule(ScriptEditor);
		if (Workbench.ScriptDialog("Plugin Generator", "Creates a new plugin class with a basic template for an easier start to making new plugins", this) && Workbench.OpenModule(ScriptEditor))
		{	
			if (FileIO.FileExist(m_sAddon + m_sFilePath + m_sName + ".c"))
			{
				Workbench.Dialog("File Already Exists!", "The given file path already exists, either change the path or delete the existing file.");
				return;
			}
			
			string ln_PluginAttribute = string.Format("[WorkbenchPluginAttribute(name: %1, description: %2, shortcut: %3, icon: %4, wbModules: {%5}, category: %6, awesomeFontCode: %7)]",
			Quotify(m_sName),
			Quotify(m_sDescription),
			Quotify(m_sShortcut),
			Quotify(m_sIcon),
			Quotify(m_sModule),
			Quotify(m_sSubMenu),
			m_sAwesomeFontCode);
			
			string ln_Class = string.Format("class %1: WorkbenchPlugin", m_sName);
			
			if (!m_sAddon.EndsWith(":"))
				m_sAddon += ":";
			
			if (!m_sFilePath.EndsWith("/"))
				m_sFilePath += "/";
			
			FileHandle handle = FileIO.OpenFile(m_sAddon + m_sFilePath + m_sName + ".c", FileMode.WRITE);
			if (!handle)
			{
				Print("File path: ' " + m_sAddon + m_sFilePath + " ' doesn't exist or is read-only! (check the '$Addon:' name)", LogLevel.ERROR);
				Workbench.Dialog("Invalid File Path!", "File path given is invalid, either it doesn't exist or the location is read-only. (Such as in another addon other than your own)");
				return;
			}			
			handle.FPrintln("// ----- File Generated By ESE Plugin Generator ----- //\n");
			handle.FPrintln(ln_PluginAttribute);
			handle.FPrintln(ln_Class);
			handle.FPrintln("{");
			
			if (m_sAttributes && !m_sAttributes.IsEmpty())
			{
				foreach (string entry: m_sAttributes)
				{
					if (!entry.EndsWith(";")){
						entry += ";";
					}
					handle.FPrintln("\t[Attribute()]");
					handle.FPrintln("\t" + "protected "	+ entry + "\n");
				}
			}
			handle.FPrintln("\t" + "// Reference to workbench module");
			handle.FPrintln("\t" + "protected " + m_sModule + " " + VarNameFromType(m_sModule) + ";");
				
			handle.FPrintln("\n\t" + "override void Run()");
			handle.FPrintln("\t" + "{");

			handle.FPrintln("\t\t" + VarNameFromType(m_sModule) + " = Workbench.GetModule(" + m_sModule + ");");
						
			if (m_bCreateWithUI)
			{
				handle.FPrintln("\t\t" + "if (Workbench.ScriptDialog(" + doubleQuote + "Plugin Title" + doubleQuote + ", " + doubleQuote + "Plugin Description" + doubleQuote + ", this) && Workbench.OpenModule(" + m_sModule + "))");
				handle.FPrintln("\t\t" + "{");
				handle.FPrintln("\t\t\t" + "// Add code here...");
				handle.FPrintln("\t\t" + "}");
			}
			else
			{
				handle.FPrintln("\t\t// Add code here...");	
			} 
			handle.FPrintln("\t" + "}");
				
			handle.FPrintln("\n\t" + "override void RunCommandline() {}");
			handle.FPrintln("\n\t" + "override void Configure() {}");
				
			if (m_bCreateWithUI)
			{
				handle.FPrintln("\n\t" + "[ButtonAttribute("+doubleQuote+"Close"+doubleQuote+")]");
				handle.FPrintln("\t" + "bool ButtonClose() {return false;}");
				handle.FPrintln("\n\t" + "[ButtonAttribute("+doubleQuote+"Ok"+doubleQuote+")]");
				handle.FPrintln("\t" + "bool ButtonOk() {return true;}");
			}
			
			handle.FPrintln("\n\t" + "void " + m_sName + "() {}");
				
			handle.FPrintln("}");
			handle.CloseFile();
			
			Workbench.Dialog("Success!", string.Format("New plugin '%1' successfully created.\n\nPath: %2%3%1.c", m_sName, m_sAddon, m_sFilePath));
		}
	}
	
	[ButtonAttribute("Close")]
	bool ButtonClose() {return false;}
	[ButtonAttribute("OK")]
	bool ButtonOk() {return true;}
	
	void ESE_GenerateNewPlugin()
	{
		int doubleQuoteInt = 0x22;
		doubleQuote = doubleQuoteInt.AsciiToString();
	}
}