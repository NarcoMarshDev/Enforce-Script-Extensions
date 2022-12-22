/**
ESE Additions - ExportAddonScripts

Include path - "$EnforceScriptExtensions:scripts/Game/Additions/ExportModule.h"

Function for making a copy of all script files from a given addon, recreating the complete file structure of the addon.
This is obviously not a function to be used in actual scripts, so call it once via either a temporary global function
or as an attribute, Examples below.

--------------------------------------------------------------------------------------------------------------------------------
Calling in a function:
You can use GameProject.GetAvailableAddons() to get the GUID's of all addons, and check for the right name if you're unsure.
--------------------------------------------------------------------------------------------------------------------------------

int main()
{
	array<string> addonGUIDs = {};
	GameProject.GetAvailableAddons(addonGUIDs);
	
	foreach (string addon: addonGUIDs)
	{
		if (GameProject.GetAddonID(addon) == "AddonYouWant")
		{
			ESE_ExportAddonScripts(addon, "C:\Some\Path\AddonName");
			break;
		}
	}
	return 0;
}
int exitcode = main()

--------------------------------------------------------------------------------------------------------------------------------
Calling as an attribute:
Simply call the function like an attribute on a temporary global function or class definition, and manually write in the params.
Note that this will run at compile time not runtime, so just hit F7, let it run, then remove the code again.
--------------------------------------------------------------------------------------------------------------------------------

[ESE_ExportAddonScripts("58D0FB3206B6F859", "C:\Some\Path\AddonName")] // GUID of "$ArmaReforger:" used here
void Temp()

--------------------------------------------------------------------------------------------------------------------------------
**/

// NOTE - As of ESE v0.2.3 this function's behavior with invalid export locations is weird, double check your file paths!
void ESE_ExportAddonScripts(string addonGUID, string exportLocation)
{
	if (!exportLocation.EndsWith("/")){
		exportLocation += "/";
	}
	// need to check export location exists, just don't know how :/
	
	string addonRoot = string.Format("$%1:", GameProject.GetAddonID(addonGUID));
	Print(addonRoot);
	
	string divider = "\n-------------------------------------------------------------------------------------------------\n";
	Debug.Error2("Are you sure?", string.Format("Please Confirm!%3Exporting scripts from addon :  '%1' \nTo path : '%2' %3Press debug and close the workbench to cancel before files are created, or ignore to proceed.%3If you're seeing this message when starting the workbench, task manager close the program and launch again with -noGameScriptsOnInit launch parameter", addonRoot, exportLocation, divider));
	
	array<string> paths = {};
	System.FindFiles(paths.Insert, addonRoot+"scripts/", ".c");
	
	foreach (string path: paths)
	{
		string fileName = FilePath.StripPath(path);
		
		string stripped = FilePath.StripFileName(path);
		stripped.Replace(addonRoot, string.Empty);
		stripped = stripped.Substring(0, stripped.Length() - 1);
		
		array<string> tokens = {};
		stripped.Split("/", tokens, true);
		
		string str = exportLocation;
		foreach (string token: tokens)
		{
			str += token + "/";
			FileIO.MakeDirectory(str);
		}
		
		array<string> allLines = {};
		FileHandle readHandle = FileIO.OpenFile(path, FileMode.READ);
		string line;
		while (readHandle.FGets(line) >= 0)
		{
			allLines.Insert(line);
		}
		readHandle.CloseFile();
		
		FileHandle writeHandle = FileIO.OpenFile(str + fileName, FileMode.WRITE);
		foreach (string writeLine: allLines)
		{
			writeHandle.FPrintln(writeLine);
		}
		writeHandle.CloseFile();
	}
}