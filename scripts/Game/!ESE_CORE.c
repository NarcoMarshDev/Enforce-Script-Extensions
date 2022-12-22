#define ESE_INSTALLED // Always keep this enabled to ensure mod compatiblity with additional aliases
#define ESE_VERSION_MAJOR_0

bool ESE_IS_INITIALIZED = ESE.Init();

// #ESE_ADD_DOCUMENTATION
[__ESE_InitPtrMap()]
void __ESE_InitPtrMap() {ESE_PointerReferenceMap = new map<pointer, Class>();}
ref map<pointer, Class> ESE_PointerReferenceMap;

pointer ptr(Class in)
{
	return (int)in;
}

pointer stringf_ptr(Class in)
{
	string str = in.ToString();
	str = str.Substring(str.Length()-17, 16);
	
	string loBitsStr, hiBitsStr;
	hiBitsStr = str.Substring(0, 8);
	loBitsStr = str.Substring(8, 8);
	int loBits, hiBits;
	
	int j = 0;
	for (int i = 7; i >= 0; i--)
	{
		if (!loBitsStr.IsDigitAt(i)) {loBits += (loBitsStr.ToAscii(i) - 55) * (Math.Pow(16, j));} else {loBits += (loBitsStr.ToAscii(i) - 48) * (Math.Pow(16, j));}
		if (!hiBitsStr.IsDigitAt(i)) {hiBits += (hiBitsStr.ToAscii(i) - 55) * (Math.Pow(16, j));} else {hiBits += (hiBitsStr.ToAscii(i) - 48) * (Math.Pow(16, j));}
		j++;
	}
	
	pointer ptr = EntityID.FromInt(hiBits, loBits);
	ESE_PointerReferenceMap.Set(ptr, in);	
	return ptr;
}

Class deref_ptr(pointer ptr)
{
	return ESE_PointerReferenceMap.Get(ptr);
}