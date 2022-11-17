enum ESE_Reflection_EMemberTypes
{
	Constructor = 1,
	Event 		= 2,
	Field 		= 4,
	Method 		= 8,
	Property 	= 16,
	TypeInfo 	= 32,
	Custom 		= 64,
	NestedType 	= 128,
	All 		= 256
}

enum ESE_Reflection_EBindingFlags
{
	Default 	   = 0,
	Ignore 		   = 1,
	Declared 	   = 2,
	Instance 	   = 4,
	Static 		   = 8,
	Public		   = 16,
	NonPublic	   = 32,
	CreateInstance = 64,
	
}