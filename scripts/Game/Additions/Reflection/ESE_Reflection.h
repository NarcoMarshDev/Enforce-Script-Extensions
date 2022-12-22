//#include "$EnforceScriptExtensions:scripts/Game/Additions/Reflection/Old/ESE_Reflection_v1.h"
//#include "$EnforceScriptExtensions:scripts/Game/Additions/Reflection/Old/ESE_Reflection_v2.h"
//#include "$EnforceScriptExtensions:scripts/Game/Additions/Reflection/Old/ESE_Reflection_v3.h"

// ---------------------------------------------------------------------------------------------------------------



// ---------------------------------------------------------------------------------------------------------------
class ESE_Reflection
{
	static const ESE_EMemberTypes 	EMemberTypes;
	static const ESE_EBindingFlags 	EBindingFlags;
	
	static ScriptModule 			scriptModule = ScriptModule.LoadScript(null, "", true);
	
	// -----------------------------------------------------------------------------------------------------------
	// This isn't private in case anyone wants to mess with it, but this should only be called at compile time via attribute call
	//[UpdateTypeReferences()]
	static void UpdateTypeReferences()
	{
		auto types = GetAllClasses();
		FileHandle classRefFile = FileIO.OpenFile("$EnforceScriptExtensions:scripts/Game/Reflection/ESE_ClassReferences.csv", FileMode.WRITE);
		foreach (string type: types)
		{
			classRefFile.FPrintln(type);
		}
		classRefFile.CloseFile();
	}
	
	// -----------------------------------------------------------------------------------------------------------
	static array<string> GetAllClasses()
	{	
		array<string> outArray = {};
		// go through all addons so we can find the files in each, like $core, $ArmaReforger, $EnforceScriptExtensions, etc.
		array<string> addons = {};
		GameProject.GetAvailableAddons(addons);
		array<string> duplicates = {};
		foreach (string addon: addons)
		{
			// find all the script files in the addon
			string addonID = GameProject.GetAddonID(addon);
			array<string> addonFiles = {};
			System.FindFiles(addonFiles.Insert, "$"+addonID+":scripts/", ".c");
			//addonFiles.Debug();
			
			foreach (string file: addonFiles)
			{
				string line;
				FileHandle fHandle = FileIO.OpenFile(file, FileMode.READ);
				bool commentedOff = false;
				while (fHandle.FGets(line) >= 0)
				{
					// handle commented off sections of code
					if (line.Contains("/*"))
					{
						commentedOff = true;
					}
					if (line.Contains("*/"))
					{
						commentedOff = false;
					}
					if (commentedOff || line.Contains("//")) // change to starts with
					{
						continue;
					}
					line.Replace(":", "");
					if (line.StartsWith("class") || line.StartsWith("sealed") || line.StartsWith("modded"))
					{
						array<string> tokens = {};
						line.Split(" ", tokens, true);
												
						tokens.RemoveItemOrdered("class");
						tokens.RemoveItemOrdered("sealed");
						tokens.RemoveItemOrdered("modded");
						tokens.RemoveItemOrdered("extends");
						
						// to handle template classes, since they have a space in their name like: Something<Class T>
						foreach (string element: tokens)
						{
							if (element.Contains(">") && !element.Contains("<"))
							{
								tokens[0] = tokens[0] + " " + element;
								break;
							}
						}
						
						tokens.Insert(file);
						//Print(tokens);
						if (outArray.Contains(tokens[0]))
						{
							duplicates.Insert(tokens[0] + " : " + file);
						}
						outArray.Insert(tokens[0] + "," + file);
					}
				}
				fHandle.CloseFile();
			}
		}
		Print(duplicates);
		return outArray;
	}

	// -----------------------------------------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------------------------------------
}