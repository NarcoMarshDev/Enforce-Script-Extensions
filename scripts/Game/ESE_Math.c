// -----------------------------------------------------------------------------------------------------------
// Enforce Script Extensions - By NarcoMarshmallow
// 
// Message me @narcoleptic marshmallow #1188 on discord to give feedback or go to https://github.com/NarcoMarshDev
//
// Math class containing various additions to the core math classes
// -----------------------------------------------------------------------------------------------------------

class ESE_Math
{
	static float CeilToNearestMultiple(float number, float multiple)
	{
    	if (multiple != 0 && number != 0)
		{
			float sign;
			if (number > 0) {sign = 1;}
			else			{sign = -1;}
        	number *= sign;
        	number /= multiple;
        	int fixedPoint = Math.Ceil(number);
        	number = fixedPoint * multiple;
        	number *= sign;
    	}
    	return number;
	}
	
	
	/**
	Fixes given value to modulo of 360 and then within -180 and 180, used mostly for rotation values
	@code
		int num = 245;
		int fixedNum = ESE_Math.FixInt180(num);
		Print(fixedNum);
		
		>> -115
	@endcode
	*/
	static int FixInt180(int val)
	{
		int rem = val % 360;
		if (rem > 180){
			return rem - 360;
		}
		return rem;
	}
	// See FixInt180(), same but for floats
	static float FixFloat180(float val)
	{
		float rem = SCR_Global.fmod(val, 360);
		if (rem > 180){
			return rem - 360;
		}
		return rem;
	}
	// See FixInt180(), same but for vectors
	static vector FixVector180(vector vec)
	{
		for (int i = 0; i < vec.Length() - 1; i++)
		{
			vec[i] = FixFloat180(vec[i]);
		}
		return vec;
	}
	//-----------------------------------------------------------------------------------------------------------
	// Fast versions for when input is known to be between -360 & 360
	static float FastFixFloat180(float val)
	{
		if 		(val > 180)  {val -= 360;}
		else if (val < -180) {val += 360;}
		return val;
	}
	
	static int FastFixInt180(int val)
	{
		if 		(val > 180)  {val -= 360;}
		else if (val < -180) {val += 360;}
		return val;
	}
	
	static vector FastFixVector180(vector vec)
	{
		for (int a = 0; a < 3; a++)
		{
			float v = vec[a];
			while (v > 180)
				v -= 360;
			while (v < -180)
				v += 360;
			vec[a] = v;
		}
		return vec;
	}
	// -----------------------------------------------------------------------------------------------------------
	
	
	
	
	
	
	
	

	// ================================ Obsolete ================================
	
	#ifdef ESE_OBSOLETE
	static float _OLD_FixFloat180(float val)
	{
		if 		(val > 180)  {val -= 360;}
		else if (val < -180) {val += 360;}
		return val;
	}
	
	static int _OLD_FixInt180(int val)
	{
		if 		(val > 180)  {val -= 360;}
		else if (val < -180) {val += 360;}
		return val;
	}
	
	static vector _OLD_FixVector180(vector vec)
	{
		for (int a = 0; a < 3; a++)
		{
			float v = vec[a];
			while (v > 180)
				v -= 360;
			while (v < -180)
				v += 360;
			vec[a] = v;
		}
		return vec;
	}
	#endif
}