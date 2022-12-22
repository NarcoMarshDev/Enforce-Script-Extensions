//[AnotherMainFunc()]
void AnotherMainFunc()
{
	#ifdef ESE_ENABLE_REFLECTION
	Print("AMainFunc");
	typename currentClass = TestClass;
	
	string path = "$EnforceScriptExtensions:scripts/Game/Testing/MainFunc.c";
	FileHandle readHandle = FileIO.OpenFile(path, FileMode.READ);
	array<string> allLines = {};
	string line;
	string funcName = "ESE_NO_FUNCTION";
	while (readHandle.FGets(line) >= 0)
	{
		if (line.Contains("#FUNCTION"))
		{
			funcName = ESE_ScriptParser.GetFunctionName(line);
			Print(funcName);
		}
		if (line.Contains("#INVOKER"))
		{
			int start = line.IndexOf("(");
			int end   = line.IndexOf(")");
			string param = line.Substring(start, end-start);
			line.Replace("param", currentClass.ToString()+"."+funcName);
		}
		allLines.Insert(line);
	}
	readHandle.CloseFile();
	//allLines.Debug();
	
	return;
	
	FileHandle writeHandle = FileIO.OpenFile(path, FileMode.WRITE);
	foreach (string writeLine: allLines)
	{
		writeHandle.FPrintln(writeLine);
	}
	writeHandle.CloseFile();
	#endif
}