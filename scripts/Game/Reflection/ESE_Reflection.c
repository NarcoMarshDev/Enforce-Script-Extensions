//#include "$EnforceScriptExtensions:scripts/Game/Reflection/ESE_Reflection_v1.h"
//#include "$EnforceScriptExtensions:scripts/Game/Reflection/ESE_Reflection_v2.h"

class ESE_Type: Managed
{
	typename Type;
	typename BaseType;
	bool 	 IsByRef;
	bool 	 IsArray;
	bool 	 IsClass;
	bool 	 IsEnum;
	
	ESE_Reflection_EMemberTypes MemberType;
	string Name;
	
	bool EqualsObj(Class obj) 	{return Type && obj;}
	bool EqualsType(typename T) {return Type && T;}
	array<ESE_Type> FindMembers(ESE_Reflection_EMemberTypes memberType, ESE_Reflection_EBindingFlags bindingFlags)
	{
		
	}
	
	void ESE_Type(typename type = typename.Empty)
	{
		if (!type)
			return;
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
	static const ESE_Reflection_EMemberTypes 	EMemberTypes;
	static const ESE_Reflection_EBindingFlags 	EBindingFlags;
	
	// -----------------------------------------------------------------------------------------------------------
	
	
	// -----------------------------------------------------------------------------------------------------------
	static ESE_Type TypeOf(int in)
	{
		ESE_Type T = new ESE_Type();
		T.Type = int; T.BaseType = int;
		T.IsByRef = false; T.IsArray = false; T.IsClass = false; T.IsEnum = false;
		T.Name = in.ToString();
		return T;
	}
	static ESE_Type TypeOf(float in)
	{
		ESE_Type T = new ESE_Type();
		T.Type = float; T.BaseType = float;
		T.IsByRef = false; T.IsArray = false; T.IsClass = false; T.IsEnum = false;
		T.Name = in.ToString();
		return T;
	}
	static ESE_Type TypeOf(bool in)
	{
		ESE_Type T = new ESE_Type();
		T.Type = bool; T.BaseType = bool;
		T.IsByRef = false; T.IsArray = false; T.IsClass = false; T.IsEnum = false;
		T.Name = in.ToString();
		return T;
	}
	static ESE_Type TypeOf(string in)
	{
		ESE_Type T = new ESE_Type();
		T.Type = string; T.BaseType = string;
		T.IsByRef = false; T.IsArray = false; T.IsClass = false; T.IsEnum = false;
		T.Name = in;
		return T;
	}
	static ESE_Type TypeOf(vector in)
	{
		ESE_Type T = new ESE_Type();
		T.Type = vector; T.BaseType = vector;
		T.IsByRef = false; T.IsArray = false; T.IsClass = false; T.IsEnum = false;
		T.Name = in.ToString();
		return T;
	}
	static ESE_Type TypeOf(Class in)
	{
		ESE_Type T = new ESE_Type();
		T.Type = Class; T.BaseType = Class;
		T.IsByRef = true; T.IsArray = false; T.IsClass = true; T.IsEnum = false;
		T.Name = in.ToString();
		return T;
	}
	static ESE_Type TypeOf(typename in)
	{
		ESE_Type T = new ESE_Type();
		T.Type = typename; T.BaseType = typename;
		T.IsByRef = false; T.IsArray = false; T.IsClass = false; T.IsEnum = false;
		T.Name = in.ToString();
		return T;
	}
	// -----------------------------------------------------------------------------------------------------------
	
	// -----------------------------------------------------------------------------------------------------------
}