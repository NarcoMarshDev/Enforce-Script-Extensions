// -----------------------------------------------------------------------------------------------------------
// Enforce Script Extensions - By NarcoMarshmallow
// 
// Message me @narcoleptic marshmallow #1188 on discord to give feedback or go to https://github.com/NarcoMarshDev
// -----------------------------------------------------------------------------------------------------------
/**
ESE_Stack Class

Template class for first-in, last-out array of objects. Attempting to push an object to the stack when it's count has
reached it's maxsize will make Push() return false and no object will be added.

For full documentation check the wiki @ https://github.com/NarcoMarshDev/Enforce-Script-Extensions/wiki/ESE_Stack-Class

Code example:
@code
	// creates new stack with a size of 5
	auto m_stack = new ESE_Stack<int>(5);
	
	for (int i = 0; i < 5; i++)
	{
		m_stack.Push(i); // push i onto stack
	}
	Print(m_stack.Raw); 		>> {0,1,2,3,4}
	
	// pop most recent entry off the stack and return it
	int val = m_stack.Pop();
	Print(val);					>> 4
	Print(m_stack.Raw);			>> {0,1,2,3}
@endcode
*/

class ESE_Stack<Class T>: Managed
{
	ref array<T> Raw = {};
	int MaxSize;
	T nullValue = null;
	
	// ----------------------------------------------------------------------------------------------------------- //
	bool Push(T value)
	{
		if (Raw.Count() >= MaxSize)
		{
			return false;
		}
		Raw.Insert(value);
		return true;
	}
	// ----------------------------------------------------------------------------------------------------------- //
	T Pop()
	{
		int topIndex = Raw.Count() - 1;
		if (topIndex < 0)
		{
			#ifdef ESE_VERBOSE
			Print("" + this + ": Attempted to pop index out of range ["+topIndex+"]", LogLevel.ERROR);
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
			Print("" + this + ": Attempted to pop index out of range ["+topIndex+"]", LogLevel.ERROR);
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
	int GetMaxSize()
	{
		return MaxSize;
	}
	// ----------------------------------------------------------------------------------------------------------- //
	void Resize(int size)
	{
		int sizeDifference = MaxSize - size;
		if (sizeDifference > 0)
		{
			Raw.Resize(size);
		}
		MaxSize = size;
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
	void CopyToDynamicStack(notnull inout ESE_DynamicStack<T> newStack)
	{
		newStack.Raw.Copy(this.Raw);
		newStack.Compact();
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
	void ESE_Stack(int size)
	{
		MaxSize = size;
	}
	// ----------------------------------------------------------------------------------------------------------- //
	void ~ESE_Stack()
	{
		delete Raw;
	}
}