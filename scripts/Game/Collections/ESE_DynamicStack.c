// -----------------------------------------------------------------------------------------------------------
// Enforce Script Extensions - By NarcoMarshmallow
// 
// Message me @narcoleptic marshmallow #1188 on discord to give feedback or go to https://github.com/NarcoMarshDev
// -----------------------------------------------------------------------------------------------------------
/**
ESE_DynamicStack Class

Template class for first-in, last-out array of objects. The dynamic stack has no max size, and will continue to grow
as more objects are pushed onto it, and shrink when popped off. Use TrimTo() to reduce the size and lose the most
recent entries.

For full documentation check the wiki @ https://github.com/NarcoMarshDev/Enforce-Script-Extensions/wiki/ESE_DynamicStack-Class

Code example:
@code
	// See ESE_Stack
@endcode
*/

class ESE_DynamicStack<Class T>: Managed
{
	ref array<T> Raw = {};
	T nullValue = null;
	
	// ----------------------------------------------------------------------------------------------------------- //
	void Push(T value)
	{
		Raw.Insert(value);
	}
	// ----------------------------------------------------------------------------------------------------------- //
	T Pop()
	{
		int topIndex = Raw.Count() - 1;
		if (topIndex < 0)
		{
			#ifdef ESE_VERBOSE
			Print("" + this + ": Attempted to peek index out of range ["+topIndex+"]", LogLevel.ERROR);
			#endif
			return nullValue;
		}
		T value = Raw.Get(topIndex);
		Raw.Remove(topIndex);
		return value;
	}
	// ----------------------------------------------------------------------------------------------------------- //
	T Peek()
	{
		int topIndex = Raw.Count() - 1;
		if (topIndex < 0)
		{
			#ifdef ESE_VERBOSE
			Print("" + this + ": Attempted to peek index out of range ["+topIndex+"]", LogLevel.ERROR);
			#endif
			return nullValue;
		}
		T value = Raw.Get(topIndex);
		return value;
	}
	// ----------------------------------------------------------------------------------------------------------- //
	bool TryPop(out T output)
	{
		int topIndex = Raw.Count() - 1;
		if (topIndex < 0)
		{
			#ifdef ESE_VERBOSE
			Print("" + this + ": Attempted to peek index out of range ["+topIndex+"]", LogLevel.ERROR);
			#endif
			output = nullValue;
			return false;
		}
		output = Raw.Get(topIndex);
		Raw.Remove(topIndex);
		return true;
	}
	// ----------------------------------------------------------------------------------------------------------- //
	bool TryPeek(out T output)
	{
		int topIndex = Raw.Count() - 1;
		if (topIndex < 0)
		{
			#ifdef ESE_VERBOSE
			Print("" + this + ": Attempted to peek index out of range ["+topIndex+"]", LogLevel.ERROR);
			#endif
			output = nullValue;
			return false;
		}
		output = Raw.Get(topIndex);
		return true;
	}
	// ----------------------------------------------------------------------------------------------------------- //
	bool Contains(T value)
	{
		return Raw.Contains(value);
	}
	// ----------------------------------------------------------------------------------------------------------- //
	void Clear()
	{
		Raw.Clear();
	}
	// ----------------------------------------------------------------------------------------------------------- //
	int Count()
	{
		return Raw.Count();
	}
	// ----------------------------------------------------------------------------------------------------------- //
	void TrimTo(int size)
	{
		int sizeDifference = Raw.Count() - size;
		if (sizeDifference < 0) {
			return;
		}
		Raw.Resize(size);
		Raw.Compact();
	}
	// ----------------------------------------------------------------------------------------------------------- //
	void Compact()
	{
		Raw.Compact();
	}
	// ----------------------------------------------------------------------------------------------------------- //
	typename GetDataType()
	{
		return T;
	}
	// ----------------------------------------------------------------------------------------------------------- //
	void CopyToArray(notnull inout array<T> newArray)
	{
		newArray.Copy(Raw);
	}
	// ----------------------------------------------------------------------------------------------------------- //
	void CopyToStaticStack(notnull inout ESE_Stack<T> newStack)
	{
		newStack.Raw.Copy(this.Raw);
		newStack.Resize(this.Raw.Count());
	}
	// ----------------------------------------------------------------------------------------------------------- //
	void CopyFromArray(notnull array<T> oldArray)
	{
		Raw.Copy(oldArray);
		Resize(oldArray.Count());
	}
	// ----------------------------------------------------------------------------------------------------------- //
	void PrintRaw()
	{
		Print(Raw);
	}
	// ----------------------------------------------------------------------------------------------------------- //
	void ESE_DynamicStack()
	{
	}
	// ----------------------------------------------------------------------------------------------------------- //
	void ~ESE_DynamicStack()
	{
		delete Raw;
	}
}