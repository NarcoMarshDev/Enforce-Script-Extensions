// v2, this all needs checking and tweaking with classes changed to modded classes before being included back in ESE_Reflection.c
class ESE_ReflectionProperty: Managed
{
	typename m_tTypeName;
	string m_sPropName;
	
	typename GetType()  {return m_tTypeName;}
	string 	 GetName()  {return m_sPropName;}
	string	 Output()	{return m_tTypeName.ToString() + ": " + m_sPropName;}
	
	void ESE_ReflectionProperty(typename type, string name)
	{
		m_tTypeName = type;
		m_sPropName = name;
	}
}
class ESE_MemberInfo: Managed
{
	ESE_Type DeclaringType;
	ESE_Type ReflectingType;
	ESE_EMemberTypes MemberType;
	string Name;
	
	bool Equals(Class obj) {return this && obj;}
	
	
	void ESE_MemberInfo()
}

class ESE_Type: ESE_MemberInfo
{
	typename Type;
	typename BaseType;
	bool 	 IsByRef;
	bool 	 IsArray;
	bool 	 IsClass;
	bool 	 IsEnum;
	
	bool EqualsObj(Class obj) 	{return Type && obj;}
	bool EqualsType(typename T) {return Type && T;}
	array<ESE_MemberInfo> FindMembers(ESE_EMemberTypes memberType, ESE_EBindingFlags bindingFlags)
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
	static const ESE_EMemberTypes 	EMemberTypes;
	static const ESE_EBindingFlags 	EBindingFlags;
	
	static ESE_ReflectionProperty 					NewProperty(typename type, string name) {return new ESE_ReflectionProperty(type, name);}
	static array<autoptr ESE_ReflectionProperty> 	NewPropertyArray() 			  			{return new array<autoptr ESE_ReflectionProperty>();}
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
	static array<autoptr ESE_ReflectionProperty> GetAllProperties(Managed instance)
	{
		if (!instance)
			return null;
				
		typename classType = instance.Type();
		int varCount = classType.GetVariableCount();
		array<autoptr ESE_ReflectionProperty> output = new array<autoptr ESE_ReflectionProperty>();
		Print(output);
		for (int i = 0; i < varCount; i++)
		{
			typename type = classType.GetVariableType(i);
			string name = classType.GetVariableName(i);
			auto prop = NewProperty(type, name);
			output.Insert(prop);
			Print(output);
		}
		return output;
	}
	// -----------------------------------------------------------------------------------------------------------
}