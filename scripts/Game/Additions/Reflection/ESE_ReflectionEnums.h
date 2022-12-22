enum ESE_EMemberTypes
{
	None		= 0,
	Constructor = 1,
	Event 		= 2,
	Field 		= 4,
	Method 		= 8,
	Property 	= 16,
	All 		= 32
}

enum ESE_EBindingFlags
{
	Default 	   = 0,
	Ignore 		   = 1,
	Declared 	   = 2,
	Instance 	   = 4,
	Static 		   = 8,
	Public		   = 16,
	NonPublic	   = 32,
	CreateInstance = 64
}

enum EPrimitiveTypes
{
	bool,
	float,
	int,
	ResourceName,
	SharedItemRef,
	string,
	typename,
	vector,
	Class,
	void
}