class ESE_ScriptParser
{	
	static string GetFunctionName(string line)
	{
		if (!line.Contains("("))
			return string.Empty;
		
		line.Replace("\t", "");
		
		array<string> tokens = {};
		line.Split(" ", tokens, true);
		
		for (int i = 0; i < tokens.Count(); i++)
		{
			if (tokens[i].ToType())
			{
				if (tokens[i + 1].Contains("("))
				{
					string name = tokens[i + 1];
					name = name.Substring(0, name.IndexOf("("));
					return name;
				}
				return string.Empty;
			}
		}
		return string.Empty;
	}
	
	// -----------------------------------------------------------------------------------------------------------
	static void GenerateInvokers()
	// -----------------------------------------------------------------------------------------------------------
	//static string GetMember()
}