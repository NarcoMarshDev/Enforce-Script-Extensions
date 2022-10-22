// -----------------------------------------------------------------------------------------------------------
// Enforce Script Extensions - By NarcoMarshmallow
// 
// Message me @narcoleptic marshmallow #1188 on discord to give feedback or go to https://github.com/NarcoMarshDev
// -----------------------------------------------------------------------------------------------------------
class ESE_IO
{	
	static int ReadFileAsArray(string path, inout array<string> arr, int length)
	{
		FileHandle f = FileIO.OpenFile(path, FileMode.READ);
		int readLen = f.ReadFile(arr, length);
		f.CloseFile();
		return readLen;
	}
	
	// Works like csv reader but using space delimiters instead of commas
	static int ReadSpaceDelimitedFileAsArray(string path, inout array<array<string>> output)
	{
		output.Clear();
		ParseHandle file = FileIO.BeginParse(path);
		int lineNumber = 0;
		int charNum = 0;
		while (true)
		{
			array<string> line = {};
			charNum = file.ParseLine(lineNumber, line);
			if (charNum == -1) {break;} // if end of file, break and dont push line to output
			
			output.Insert(line);
			lineNumber++;
		}
		file.EndParse();
		return lineNumber;
	}
	
	// -----------------------------------------------------------------------------------------------------------
	#ifdef ESE_ENABLE_WIP
	static string ReadFileAsString(string path)
	{
		// TODO
	}
	#endif
	// -----------------------------------------------------------------------------------------------------------
	/**
	Generate globally unique id, returns a string that can be used as a token
	This code comes from armazac's Overthrow mod, credit:
	https://github.com/ArmaOverthrow/Overthrow.Arma4/blob/main/Scripts/Game/Components/Player/OVT_PlayerIdentityComponent.c
	*/
	static string GenerateGUID()
	{
			
		int year = 0;
		int month = 0;
		int day = 0;	
		System.GetYearMonthDayUTC(year, month, day);
	
		int hour = 0;
		int minute = 0;
		int second = 0;			
		System.GetHourMinuteSecondUTC(hour, minute, second);
		
		string s = ""+year+month+day+hour+minute+second;
	
		//Add some random numbers (Reference: https://eager.io/blog/how-long-does-an-id-need-to-be/)
		int i = s_AIRandomGenerator.RandFloatXY(0, 16777215);
		s += i.ToString();
	
		i = s_AIRandomGenerator.RandFloatXY(0, 16777215);
		s += i.ToString();
		
		return s;
	}
}