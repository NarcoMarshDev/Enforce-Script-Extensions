// -----------------------------------------------------------------------------------------------------------
// Enforce Script Extensions - By NarcoMarshmallow
// 
// Message me @narcoleptic marshmallow #1188 on discord to give feedback or go to https://github.com/NarcoMarshDev
//
// These are all experiemental custom data types, which are not guaranteed to work in their current state, mostly due to modding core
// classes being unsupported currently, as well as some not supporting inheritance. Very WIP, see ESE.c for more info
// -----------------------------------------------------------------------------------------------------------

#ifdef ESE_EXPERIMENTAL

class ESE_array<Class T> : array<T>
{
	// Converts contents of array to string, no matter what the type is
	void ToString(out string str)
	{		
		string temp;
		foreach (T element : this)
		{
			temp += element.ToString();
		}
		str = temp;
	}
	// -----------------------------------------------------------------------------------------------------------
	// Converts contents of array to string if array type is string, will return false if not array<string>
	bool ToStringTextOnly(out string str)
	{
		if (!T.IsInherited(string))
			return false;
		
		string temp;
		foreach (string element : this)
		{
			temp += element;
		}
		str = temp;
		return true;
	}
	// -----------------------------------------------------------------------------------------------------------
	// Returns data type of array
	typename GetType()
	{
		return T;
	}
	// -----------------------------------------------------------------------------------------------------------
	// Casts contents of array to template type of the new array and copies the contents to it
	bool CastToNewArray(inout ESE_array newArray)
	{
		int size = Count();
		if (!size || newArray.Count())
			return false;
		
		// for each element of this array, cast it's value to the new type and insert
		for (int i = 0; i < size; i++)
		{
			newArray.Insert(newArray.GetType().Cast( Get(i) ));
		}
		return true;
	}
}


#endif