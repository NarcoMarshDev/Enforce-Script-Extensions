// -----------------------------------------------------------------------------------------------------------
// Enforce Script Extensions - By NarcoMarshmallow
// 
// Message me @narcoleptic marshmallow #1188 on discord to give feedback or go to https://github.com/NarcoMarshDev
// -----------------------------------------------------------------------------------------------------------
/**
ESE_DynamicQueue Class

Template class for first-in, first-out array of objects. Unlike ESE_Queue, this class is dynamically sized and will expand
whenever a new object is enqueued, and old objects are never automatically dequeued.

For full documentation check the wiki @ https://github.com/NarcoMarshDev/Enforce-Script-Extensions/wiki/ESE_DynamicQueue-Class

Code example:
@code
	// See ESE_Queue
@endcode
*/

class ESE_DynamicQueue<Class T>
{
	ref array<T> Raw = {};
	T nullValue = null;
	
	// ----------------------------------------------------------------------------------------------------------- //
	void Enqueue(T value)
	{
		Raw.InsertAt(value, 0);
	}
	// ----------------------------------------------------------------------------------------------------------- //
	T Dequeue()
	{
		int lastIndex = Raw.Count() - 1;
		if (lastIndex < 0)
		{
			#ifdef ESE_VERBOSE
			Print("" + this + ": Attempted to dequeue index out of range ["+lastIndex+"]", LogLevel.ERROR);
			#endif
			return nullValue;
		}
		T value = Raw.Get(lastIndex);
		Raw.Remove(lastIndex);
		return value;
	}
	// ----------------------------------------------------------------------------------------------------------- //
	T Peek()
	{
		int lastIndex = Raw.Count() - 1;
		if (lastIndex < 0)
		{
			#ifdef ESE_VERBOSE
			Print("" + this + ": Attempted to peek index out of range ["+lastIndex+"]", LogLevel.ERROR);
			#endif
			return nullValue;
		}
		T value = Raw.Get(lastIndex);
		return value;
	}
	// ----------------------------------------------------------------------------------------------------------- //
	bool TryDequeue(out T output)
	{
		int lastIndex = Raw.Count() - 1;
		if (lastIndex < 0)
		{
			#ifdef ESE_VERBOSE
			Print("" + this + ": Attempted to dequeue index out of range ["+lastIndex+"]", LogLevel.ERROR);
			#endif
			output = nullValue;
			return false;
		}
		output = Raw.Get(lastIndex);
		Raw.Remove(lastIndex);
		return true;
	}
	// ----------------------------------------------------------------------------------------------------------- //
	bool TryPeek(out T output)
	{
		int lastIndex = Raw.Count() - 1;
		if (lastIndex < 0)
		{
			#ifdef ESE_VERBOSE
			Print("" + this + ": Attempted to peek index out of range ["+lastIndex+"]", LogLevel.ERROR);
			#endif
			output = nullValue;
			return false;
		}
		output = Raw.Get(lastIndex);
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
	void CopyToStaticQueue(notnull inout ESE_Queue<T> newQueue)
	{
		newQueue.Raw.Copy(this.Raw);
		newQueue.Resize(this.Raw.Count());
	}
	// ----------------------------------------------------------------------------------------------------------- //
	void CopyFromArray(notnull array<T> oldArray)
	{
		Raw.Copy(oldArray);
		TrimTo(oldArray.Count());
	}
	// ----------------------------------------------------------------------------------------------------------- //
	void PrintRaw()
	{
		Print(Raw);
	}
	// ----------------------------------------------------------------------------------------------------------- //
	void ESE_DynamicQueue()
	{
	}
	// ----------------------------------------------------------------------------------------------------------- //
	void ~ESE_DynamicQueue()
	{
		delete Raw;
	}
}