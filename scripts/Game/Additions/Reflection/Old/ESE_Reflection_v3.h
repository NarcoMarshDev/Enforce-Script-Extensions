//#include "$EnforceScriptExtensions:scripts/Game/Reflection/ESE_Reflection_v1.h"
//#include "$EnforceScriptExtensions:scripts/Game/Reflection/ESE_Reflection_v2.h"

class ESE_Type<Class T>: Managed
{
	T Owner;
	typename Type;
	typename BaseType;
	bool 	 IsByRef;
	bool 	 IsArray;
	bool 	 IsClass;
	bool 	 IsEnum;
	
	ESE_EMemberTypes MemberType;
	string Name;
	
	bool EqualsObj(Class obj) 	{return Type && obj;}
	bool EqualsType(typename other) {return Type && other;}
	array<ESE_Type<Class>> FindMembers(ESE_EMemberTypes memberType = ESE_EMemberTypes.All, ESE_EBindingFlags bindingFlags = ESE_EBindingFlags.Default)
	{
		/**
		array<ESE_Type<Class>> output = new array<ESE_Type<Class>>();
		int varCount = Type.GetVariableCount();
		for (int i = 0; i < varCount; i++)
		{
			string name = Type.GetVariableName(i);
			typename type = Type.GetVariableType(i);
			void val;
			Type.GetVariableValue(Owner, i, val);
			Print("name: " + name);
			Print("type: " + type);
			Print("value: " + val);
			
			output.Insert( ESE_Reflection.TypeOf(val) );
		}
		return output;
		**/
		return null;
	}
		
	void ESE_Type(T inst, typename type = typename.Empty)
	{
		if (!type)
			return;
		
		Owner = inst;
		Type = type;
		BaseType = Type.super.ClassName().ToType();
		if (Type.IsInherited(Class)) 	{IsByRef = true; IsClass = true;}
		if (Type.IsInherited(array)) 	{IsArray = true;}
		if (Type.IsInherited(SCR_Enum)) {IsEnum = true;}
		Name = Type.ToString();
	}
}

// ---------------------------------------------------------------------------------------------------------------
class ESE_Reflection
{
	static const ESE_EMemberTypes 	EMemberTypes;
	static const ESE_EBindingFlags 	EBindingFlags;
	
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
	static void TestFunc(int in)
	{
		string valueStr = in.ToString();
		typename type = int;
		string typeStr = type.ToString();
		Print(typeStr + " " + valueStr);
	}
	static void TestFunc(float in)
	{
		string valueStr = in.ToString();
		typename type = float;
		string typeStr = type.ToString();
		Print(typeStr + " " + valueStr);
	}
	static void TestFunc(bool in)
	{
		string valueStr = in.ToString();
		typename type = bool;
		string typeStr = type.ToString();
		Print(typeStr + " " + valueStr);
	}
	static void TestFunc(string in)
	{
		string valueStr = in;
		typename type = string;
		string typeStr = type.ToString();
		Print(typeStr + " " + valueStr);
	}
	static void TestFunc(vector in)
	{
		string valueStr = in.ToString();
		typename type = vector;
		string typeStr = type.ToString();
		Print(typeStr + " " + valueStr);
	}
	static void TestFunc(Class in)
	{
		string valueStr = in.ToString();
		typename type = in.ClassName().ToType();
		string typeStr = type.ToString();
		Print(typeStr + " " + valueStr);
	}
	static void TestFunc(typename in)
	{
		string valueStr = in.ToString();
		typename type = in;
		string typeStr = type.ToString();
		Print(typeStr + " " + valueStr);
	}
	
	// -----------------------------------------------------------------------------------------------------------
	static ESE_Type<int> TypeOf(int in)
	{
		ESE_Type<int> T = new ESE_Type<int>(in);
		T.Type = int; T.BaseType = int;
		T.IsByRef = false; T.IsArray = false; T.IsClass = false; T.IsEnum = false;
		T.Name = in.ToString();
		return T;
	}
	static ESE_Type<float> TypeOf(float in)
	{
		ESE_Type<float> T = new ESE_Type<float>(in);
		T.Type = float; T.BaseType = float;
		T.IsByRef = false; T.IsArray = false; T.IsClass = false; T.IsEnum = false;
		T.Name = in.ToString();
		return T;
	}
	static ESE_Type<bool> TypeOf(bool in)
	{
		ESE_Type<bool> T = new ESE_Type<bool>(in);
		T.Type = bool; T.BaseType = bool;
		T.IsByRef = false; T.IsArray = false; T.IsClass = false; T.IsEnum = false;
		T.Name = in.ToString();
		return T;
	}
	static ESE_Type<string> TypeOf(string in)
	{
		ESE_Type<string> T = new ESE_Type<string>(in);
		T.Type = string; T.BaseType = string;
		T.IsByRef = false; T.IsArray = false; T.IsClass = false; T.IsEnum = false;
		T.Name = in;
		return T;
	}
	static ESE_Type<vector> TypeOf(vector in)
	{
		ESE_Type<vector> T = new ESE_Type<vector>(in);
		T.Type = vector; T.BaseType = vector;
		T.IsByRef = false; T.IsArray = false; T.IsClass = false; T.IsEnum = false;
		T.Name = in.ToString();
		return T;
	}
	static ESE_Type<Class> TypeOf(Class in)
	{
		ESE_Type<Class> T = new ESE_Type<Class>(in);
		T.Type = Class; T.BaseType = Class;
		T.IsByRef = true; T.IsArray = false; T.IsClass = true; T.IsEnum = false;
		T.Name = in.ToString();
		return T;
	}
	static ESE_Type<typename> TypeOf(typename in)
	{
		ESE_Type<typename> T = new ESE_Type<typename>(in);
		T.Type = typename; T.BaseType = typename;
		T.IsByRef = false; T.IsArray = false; T.IsClass = false; T.IsEnum = false;
		T.Name = in.ToString();
		return T;
	}
	// -----------------------------------------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------------------------------------
}