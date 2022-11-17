Namespace_Core Core = "$core:scripts/Core/";



typedef string Namespace_Core
class Namespace_Core: string
{
	private static string Root = "$core:scripts/Core/";
	
	static Namespace_Generated 	Generated 	= Root + "generated/";
	static Namespace_Proto 		Proto 		= Root + "proto/";
	static Namespace_Workbench 	workbench 	= Root + "workbench/";
}

typedef string Namespace_Generated
class Namespace_Generated: string
{
	private static string Root = "$core:scripts/Core/generated";
	
	static string Audio 		= Root + "Audio/";
	static string Containers 	= Root + "Containers/";
	static string debugging 	= Root + "Debug/"; // This should be called debug not debugging, but it throws a compiler error if i call it that :/
	static string Entities 		= Root + "Entities/";
	static string Events 		= Root + "Events/";
	static string Input 		= Root + "Input/";
	static string math 			= Root + "Math/";
	static string physics 		= Root + "Physics/";
	static string replication 	= Root + "Replication/";
	static string Resources 	= Root + "Resources/";
	static string Road 			= Root + "Road/";
	static string system		= Root + "System/";
	static string Types 		= Root + "Types/";
	static string UI 			= Root + "UI/";
	static string Visual 		= Root + "Visual/";
	static string world 		= Root + "World/";
	
	void Namespace_Generated(string str)
	{
		Print("FUCK");
	}
}

typedef string Namespace_Proto
class Namespace_Proto: string
{
	
}

typedef string Namespace_Workbench
class Namespace_Workbench: string
{
	
}