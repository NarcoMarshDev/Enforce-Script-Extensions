class ESE_Type
{
	protected bool 				bool_owner;
	protected float 			float_owner;
	protected int 				int_owner;
	protected ResourceName 		resourceName_owner;
	protected SharedItemRef 	sharedItemRef_owner;
	protected string 			string_owner;
	protected typename 			typename_owner;
	protected vector 			vector_owner;
	protected Class 			class_owner;
	
	protected EPrimitiveTypes	primitiveType;
	protected typename 			ownerType;
	protected bool 				isReference;
	
	ScriptModule scriptModule;
	
	typename 		GetTypename() 		{return ownerType;}
	
	
	
	void GetOwner(out void val)				{}
	void GetOwner(out bool val) 			{val = bool_owner;}
	void GetOwner(out float val) 			{val = float_owner;}
	void GetOwner(out int val) 				{val = int_owner;}
	void GetOwner(out ResourceName val) 	{val = resourceName_owner;}
	void GetOwner(out SharedItemRef val) 	{val = sharedItemRef_owner;}
	void GetOwner(out string val) 			{val = string_owner;}
	void GetOwner(out typename val) 		{val = typename_owner;}
	void GetOwner(out vector val) 			{val = vector_owner;}
	void GetOwner(out Class val) 			{val = class_owner;}
	
	bool Invoke(string method, out bool returnValue) 			{return scriptModule.Call(class_owner, method, false, returnValue);}
	bool Invoke(string method, out float returnValue) 			{return scriptModule.Call(class_owner, method, false, returnValue);}
	bool Invoke(string method, out int returnValue) 			{return scriptModule.Call(class_owner, method, false, returnValue);}
	bool Invoke(string method, out ResourceName returnValue) 	{return scriptModule.Call(class_owner, method, false, returnValue);}
	bool Invoke(string method, out SharedItemRef returnValue) 	{return scriptModule.Call(class_owner, method, false, returnValue);}
	bool Invoke(string method, out string returnValue) 			{return scriptModule.Call(class_owner, method, false, returnValue);}
	bool Invoke(string method, out typename returnValue) 		{return scriptModule.Call(class_owner, method, false, returnValue);}
	bool Invoke(string method, out vector returnValue) 			{return scriptModule.Call(class_owner, method, false, returnValue);}
	bool Invoke(string method, out Class returnValue) 			{return scriptModule.Call(class_owner, method, false, returnValue);}
	
	void ESE_Type(EPrimitiveTypes type, bool boolVal=false, float floatVal=float.MAX, int intVal=int.MAX, ResourceName resNameVal="", SharedItemRef sharedItemRefVal=null, StaticArray staticArrayVal=null, string stringVal="", typename typenameVal=typename.Empty, vector vectorVal=Vector(float.MAX, float.MAX, float.MAX), Class classVal=null, Managed managedVal=null)
	{
		switch (type)
		{
			case EPrimitiveTypes.bool: 			{bool_owner = boolVal; 						ownerType = bool; 				break;}
			case EPrimitiveTypes.float: 		{float_owner = floatVal; 					ownerType = float;				break;}
			case EPrimitiveTypes.int: 			{int_owner = intVal; 						ownerType = int; 				break;}
			case EPrimitiveTypes.ResourceName: 	{resourceName_owner = resNameVal; 			ownerType = ResourceName; 		break;}
			case EPrimitiveTypes.SharedItemRef: {sharedItemRef_owner = sharedItemRefVal; 	ownerType = SharedItemRef; 		break;}
			case EPrimitiveTypes.string: 		{string_owner = stringVal; 					ownerType = string; 			break;}
			case EPrimitiveTypes.typename: 		{typename_owner = typenameVal; 				ownerType = typename; 			break;}
			case EPrimitiveTypes.vector: 		{vector_owner = vectorVal; 					ownerType = vector; 			break;}
			case EPrimitiveTypes.Class: 		{class_owner = classVal; 					ownerType = classVal.Type();	break;}
			default:
			{
				Print("ESE_Type::SetOwner() - Invalid type!", LogLevel.ERROR);
				return;
			}
		}
		scriptModule = ScriptModule.LoadScript(null, string.Empty, true);
	}
}

ESE_Type typeof(bool inst) 			{return new ESE_Type(EPrimitiveTypes.bool, 				boolVal: 			inst);}
ESE_Type typeof(float inst) 		{return new ESE_Type(EPrimitiveTypes.float, 			floatVal: 			inst);}
ESE_Type typeof(int inst) 			{return new ESE_Type(EPrimitiveTypes.int, 				intVal: 			inst);}
ESE_Type typeof(ResourceName inst) 	{return new ESE_Type(EPrimitiveTypes.ResourceName, 		resNameVal: 		inst);}
ESE_Type typeof(SharedItemRef inst) {return new ESE_Type(EPrimitiveTypes.SharedItemRef, 	sharedItemRefVal: 	inst);}
ESE_Type typeof(string inst) 		{return new ESE_Type(EPrimitiveTypes.string, 			stringVal: 			inst);}
ESE_Type typeof(typename inst) 		{return new ESE_Type(EPrimitiveTypes.typename, 			typenameVal: 		inst);}
ESE_Type typeof(vector inst) 		{return new ESE_Type(EPrimitiveTypes.vector, 			vectorVal: 			inst);}
ESE_Type typeof(Class inst) 		{return new ESE_Type(EPrimitiveTypes.Class, 			classVal: 			inst);}

/**
// try adding a recursive function so you carry the result from casting and getting the value into the next step, at the end of the recusion make the call.
// #ESE_TODO - Make this work, right now you have to call ESE_Type.scriptModule.Call() if you want to invoke a method with params and have it work.
	bool InvokeWithParams(string method, out string returnValue, ESE_BaseParam param1=null, ESE_BaseParam param2=null, ESE_BaseParam param3=null, ESE_BaseParam param4=null, ESE_BaseParam param5=null, ESE_BaseParam param6=null, ESE_BaseParam param7=null, ESE_BaseParam param8=null, ESE_BaseParam param9=null, )
	//bool InvokeMethod(string method, out string returnValue, Tuple params)
	{
		if (!class_owner)
		{
			Print("ESE_Type::InvokeMethod() - Can't invoke method on type not derived from 'Class'", LogLevel.ERROR);
			return false;
		}
		
		array<bool> bool_array = {};
		array<float> float_array = {};
		array<int> int_array = {};
		array<ResourceName> resName_array = {};
		array<SharedItemRef> sharedItemRef_array = {};
		array<StaticArray> staticArray_array = {};
		array<string> string_array = {};
		array<typename> typename_array = {};
		array<vector> vector_array = {};
		array<Class> class_array = {};
		array<Managed> managed_array = {};
			
		Print(param1);
		
		ESE_BaseParam allParams[] = {param1, param2, param3, param4, param5, param6, param7, param8, param9};
		foreach (ESE_BaseParam param: allParams)
		{
			if (ESE_BoolParam.Cast(param)) 			{bool_array.Insert(ESE_BoolParam.Cast(param).value); 					continue;}
			if (ESE_FloatParam.Cast(param)) 		{float_array.Insert(ESE_FloatParam.Cast(param).value); 					continue;}
			if (ESE_IntParam.Cast(param)) 			{int_array.Insert(ESE_IntParam.Cast(param).value); 						continue;}
			if (ESE_ResourceNameParam.Cast(param)) 	{resName_array.Insert(ESE_ResourceNameParam.Cast(param).value); 		continue;}
			if (ESE_SharedItemRefParam.Cast(param)) {sharedItemRef_array.Insert(ESE_SharedItemRefParam.Cast(param).value); 	continue;}
			if (ESE_StaticArrayParam.Cast(param)) 	{staticArray_array.Insert(ESE_StaticArrayParam.Cast(param).value); 		continue;}
			if (ESE_StringParam.Cast(param)) 		{string_array.Insert(ESE_StringParam.Cast(param).value); 				continue;}
			if (ESE_TypenameParam.Cast(param)) 		{typename_array.Insert(ESE_TypenameParam.Cast(param).value); 			continue;}
			if (ESE_VectorParam.Cast(param)) 		{vector_array.Insert(ESE_VectorParam.Cast(param).value); 				continue;}
			if (ESE_ClassParam.Cast(param)) 		{class_array.Insert(ESE_ClassParam.Cast(param).value); 					continue;}
			if (ESE_ManagedParam.Cast(param)) 		{managed_array.Insert(ESE_ManagedParam.Cast(param).value); 				continue;}
		}
		ScriptModule.LoadScript(null, "", true).Call(class_owner, method, false, returnValue, 5);
		return true;
	}
**/