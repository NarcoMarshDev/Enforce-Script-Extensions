// ----- File Generated By ESE Plugin Generator ----- //

[WorkbenchPluginAttribute(name: "Read-Only File Exporter", description: "Tool for making a non read-only copy of a file", shortcut: "", icon: "", wbModules: {"ScriptEditor"}, category: "ESE", awesomeFontCode: 0xf56e)]
class ESE_ReadOnlyFileExporterPlugin: WorkbenchPlugin
{
	[Attribute(defvalue: "File Name...", uiwidget: UIWidgets.FileNamePicker, params: "c et layout conf")]
	protected string m_sFile;
	
	[Attribute(defvalue: "$AddonName:scripts/Game/SomeFolder/", uiwidget: UIWidgets.Auto)]
	protected string m_sExportPath;
	
	// Reference to workbench module
	protected ScriptEditor m_scriptEditor;

	override void Run()
	{
		m_scriptEditor = Workbench.GetModule(ScriptEditor);
		if (Workbench.ScriptDialog("Read-Only File Exporter", "Tool for creating a modifiable copy of a read-only file, best used for stripping down prefabs and UI layouts\n\nCurrently supported file formats are:\n- .c (script source files)\n- .et (entity prefabs)\n- .layout (UI widget layouts)\n- .conf (configuration files)", this) && Workbench.OpenModule(ScriptEditor))
		{
			if (!m_sExportPath.EndsWith("/"))
				m_sExportPath += "/";
			
			string m_sExportPathWithFile = m_sExportPath + FilePath.StripPath(m_sFile);
			
			if (FileIO.FileExist(m_sExportPathWithFile))
			{
				Workbench.Dialog("File already exists!", string.Format("The file '%1' already exists at the export location, either change the export path or delete the file.", m_sExportPath));
				return;
			}
			
			FileHandle readHandle = FileIO.OpenFile(m_sFile, FileMode.READ);
			if (!readHandle)
			{
				Workbench.Dialog("Invalid file selected for export!", string.Format("The file '%1' does not exist.", m_sFile));
				return;
			}
			
			array<string> allLines = {};
			string line;
			while (readHandle.FGets(line) >= 0)
			{
				allLines.Insert(line);
			}
			readHandle.CloseFile();
			
			FileHandle writeHandle = FileIO.OpenFile(m_sExportPathWithFile, FileMode.WRITE);
			if (!writeHandle)
			{
				Workbench.Dialog("Invalid export location!", string.Format("The file path '%1' does not exist or is read-only.", m_sExportPath));
				return;
			}
			foreach (string writeLine: allLines)
			{
				writeHandle.FPrintln(writeLine);
			}
			writeHandle.CloseFile();
			Workbench.Dialog("File export successful!", string.Format("File successfully created at '%1'", m_sExportPathWithFile));
		}
	}

	override void RunCommandline() {}

	override void Configure() {}

	[ButtonAttribute("Close")]
	bool ButtonClose() {return false;}

	[ButtonAttribute("Ok")]
	bool ButtonOk() {return true;}

	void ESE_ReadOnlyFileExporterPlugin() {}
}