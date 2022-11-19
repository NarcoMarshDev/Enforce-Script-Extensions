#ifdef ESE_DEVMODE

int globalInt;

[ExportCore()]
void ExportCore()
{
	array<string> paths = {};
	System.FindFiles(paths.Insert, "$core:scripts/", ".c");
	paths.Debug();
	
	foreach (string path: paths)
	{
		string stripped = FilePath.StripFileName(path);
		stripped.Replace("$core:", "$EnforceScriptExtensions:scripts/Game/Reflection/CoreExport/");
		Print(stripped);
		FileIO.MakeDirectory(stripped);
	}
}



class TestClass: Managed
{
	static int a = 1;
	
	private static void Bruh()
	{
		Print("private function");
	}
	
	static void Bruh2()
	{
		Print("public function");
	}
	
	void Bruh3()
	{
		Print("non-static function");
	}
}


class TestClass2: TestClass
{
	static int b = 2;
}

int somefunction()
{
	Print("SOME FUNCTION");
	return 0;
}

//[main()]
int main()
{
	auto types = ESE_Reflection.GetAllClasses();
	types.Debug();
	int size = types.GetSizeOf();
	Print(size);
	Print("BRUH");
	
	FileHandle classRefFile = FileIO.OpenFile("$EnforceScriptExtensions:scripts/Game/Reflection/ESE_ClassReferences.csv", FileMode.WRITE);
	foreach (string type: types)
	{
		classRefFile.FPrintln(type);
	}
	classRefFile.CloseFile();
	
	ScriptCallQueue q = new ScriptCallQueue();
	TestClass obj = new TestClass();
	
	
	return 0;
	
	
	
	
	
	
	
	
	
	
	
	Print("main");
	ESE_Queue<int> queue = new ESE_Queue<int>(5);
	for (int i = 0; i < 7; i++)
	{
		queue.Enqueue(i);
	}
	
	array<int> a = {1,2,3,4,5};
	
	ESE_Reflection.TestFunc(a);
	
	array<string> arr = {};
	//System.FindFiles(arr.Insert, "$core:scripts/Core/generated/Types", ".c");
	System.FindFiles(arr.Insert, "$core:scripts/", ".c");
	//arr.Debug();
	
	string typenameStr = "swag";
	typename bruh = typenameStr.ToType();
	Print(bruh);
	
	foreach (string file: arr)
	{
		FileHandle handle = FileIO.OpenFile(file, FileMode.READ);
		array<string> methods = {};
	
		typename currentClass;
		string str;
		while (handle.FGets(str) >= 0)
		{
			if ( str.Contains(" class ") && !str.Contains("'") && !str.Contains("//") )
			{
				Print(str);
			}
			
			if (!str.StartsWith("\t"))
				continue;
			
			//Print(str);
			array<string> tokens = {};
			str.Split(" ", tokens, true);
			//Print(tokens);
			
			
		}
		handle.CloseFile();
	}
	
	return 0;
}

int exitcode = main();
#endif