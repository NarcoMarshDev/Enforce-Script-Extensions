// -----------------------------------------------------------------------------------------------------------
// Enforce Script Extensions - By NarcoMarshmallow
// 
// Message me @narcoleptic marshmallow #1188 on discord to give feedback or go to https://github.com/NarcoMarshDev
// -----------------------------------------------------------------------------------------------------------
/**
ESE_Queue Class

Template class for first-in, first-out array of objects. Adding more objects than the max size will automatically
Dequeue the oldest object in the queue.

For full documentation check the wiki @ https://github.com/NarcoMarshDev/Enforce-Script-Extensions/wiki/ESE_Queue-Class

Code example:
@code
	// creates new queue with a size of 5
	auto m_queue = new ESE_Queue<int>(5);
	for (int i = 0; i < 5; i++)
	{
		m_queue.Enqueue(i); // add i to queue
	}
	
	// values are stored in reverse in queue, position 0 is newest, position 5 is oldest
	Print(m_queue.Raw); 		>> {4,3,2,1,0}
	
	// remove oldest entry from the queue and return it
	int val = m_queue.Dequeue();
	Print(val);					>> 0
	Print(m_queue.Raw);			>> {4,3,2,1}
@endcode
*/

class ESE_Queue<Class T>
{
	ref array<T> Raw = {};
	int MaxSize;
	T nullValue = null;
	
	// ----------------------------------------------------------------------------------------------------------- //
	void Enqueue(T value)
	{
		Raw.InsertAt(value, 0);
		if (Raw.Count() > MaxSize)
		{
			Raw.Remove(MaxSize);
		}
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
	void CopyToDynamicQueue(notnull inout ESE_DynamicQueue<T> newQueue)
	{
		newQueue.Raw.Copy(this.Raw);
		newQueue.Compact();
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
	void ESE_Queue(int size)
	{
		MaxSize = size;
	}
	// ----------------------------------------------------------------------------------------------------------- //
	void ~ESE_Queue()
	{
		delete Raw;
	}
}