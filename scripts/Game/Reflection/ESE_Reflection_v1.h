// v1 reflection testing
class _OLD_ESE_Type<Class T>: Managed
{
	typename GetType() {return T;}
}

class _OLD_ESE_ReflectionProp
{
	typename type;
	string name;
	
	int iValue;
	float fValue;
	bool bValue;
	string sValue;
	vector vValue;
	Managed mValue;
	Class cValue;
	typename tValue;
	
	autoptr Managed returnValue;
	
	void Set_iValue(int val) 		{iValue = val; returnValue = new _OLD_ESE_Type<int>();}
	void Set_fValue(float val) 		{fValue = val; returnValue = new _OLD_ESE_Type<float>();}
	void Set_bValue(bool val) 		{bValue = val; returnValue = new _OLD_ESE_Type<bool>();}
	void Set_sValue(string val) 	{sValue = val; returnValue = new _OLD_ESE_Type<string>();}
	void Set_vValue(vector val) 	{vValue = val; returnValue = new _OLD_ESE_Type<vector>();}
	void Set_mValue(Managed val)	{mValue = val; returnValue = new _OLD_ESE_Type<Managed>();}
	void Set_cValue(Class val) 		{cValue = val; returnValue = new _OLD_ESE_Type<Class>();}
	void Set_tValue(typename val)	{tValue = val; returnValue = new _OLD_ESE_Type<typename>();}
	
	typename GetType()  {return type;}
	string	 GetName()  {return name;}
	Managed	 GetValue() {return _OLD_ESE_Type.Cast( returnValue );}
	
	void _OLD_ESE_ReflectionProp(typename inType)
	{
		type = inType;
	}
}

modded class ESE_Reflection
{
	static array<_OLD_ESE_ReflectionProp> _OLD_GetAllProperties(Managed instance)
	{
		if (!instance)
			return null;
		
		typename type = instance.Type();
		array<_OLD_ESE_ReflectionProp> output = new array<_OLD_ESE_ReflectionProp>();
		for (int i = 0; i < type.GetVariableCount(); i++)
		{
			typename varType = type.GetVariableType(i);
			_OLD_ESE_ReflectionProp entry = new _OLD_ESE_ReflectionProp(varType);
			entry.name = type.GetVariableName(i);
			
			// oh here we go
			if (varType.IsInherited(int))
			{
				int val;
				type.GetVariableValue(instance, i, val);
				entry.Set_iValue(val);
			}
			else if (varType.IsInherited(float))
			{
				float val;
				type.GetVariableValue(instance, i, val);
				entry.Set_fValue(val);
			}
			else if (varType.IsInherited(bool))
			{
				bool val;
				type.GetVariableValue(instance, i, val);
				entry.Set_bValue(val);
			}
			else if (varType.IsInherited(string))
			{
				string val;
				type.GetVariableValue(instance, i, val);
				entry.Set_sValue(val);
			}
			else if (varType.IsInherited(vector))
			{
				vector val;
				type.GetVariableValue(instance, i, val);
				entry.Set_vValue(val);
			}
			else if (varType.IsInherited(Managed))
			{
				Managed val;
				type.GetVariableValue(instance, i, val);
				entry.Set_mValue(val);
			}
			else if (varType.IsInherited(Class))
			{
				Class val;
				type.GetVariableValue(instance, i, val);
				entry.Set_cValue(val);
			}
			else if (varType.IsInherited(typename))
			{
				typename val;
				type.GetVariableValue(instance, i, val);
				entry.Set_tValue(val);
			}
			else
			{
				Print("ESE.Reflection.GetAllProperties(): Unknown variable type!", LogLevel.ERROR);
			}
			output.Insert(entry);
		}
		return output;
	}
}