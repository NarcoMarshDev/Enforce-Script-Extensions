/**
 \brief Tuple Class Template with seven parameters.
 */
class Tuple7<Class T1, Class T2, Class T3, Class T4, Class T5, Class T6, Class T7> extends Tuple
{
	T1 param1;
	T2 param2;
	T3 param3;
	T4 param4;
	T5 param5;
	T6 param6;
	T7 param7;

	void Tuple8(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7)
	{
		param1 = p1;
		param2 = p2;
		param3 = p3;
		param4 = p4;
		param5 = p5;
		param6 = p6;
		param7 = p7;
	}
	
	override bool Serialize(Serializer ctx)
	{
		return ctx.Write(param1) && ctx.Write(param2) && ctx.Write(param3) && ctx.Write(param4) && ctx.Write(param5) && ctx.Write(param6) && ctx.Write(param7);
	}
	
	override bool Deserializer(Serializer ctx)
	{
		return ctx.Read(param1) && ctx.Read(param2) && ctx.Read(param3) && ctx.Read(param4) && ctx.Read(param5) && ctx.Read(param6) && ctx.Read(param7);
	}
};

/**
 \brief Tuple Class Template with eight parameters.
 */
class Tuple8<Class T1, Class T2, Class T3, Class T4, Class T5, Class T6, Class T7, Class T8> extends Tuple
{
	T1 param1;
	T2 param2;
	T3 param3;
	T4 param4;
	T5 param5;
	T6 param6;
	T7 param7;
	T8 param8;

	void Tuple8(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8)
	{
		param1 = p1;
		param2 = p2;
		param3 = p3;
		param4 = p4;
		param5 = p5;
		param6 = p6;
		param7 = p7;
		param8 = p8;
	}
	
	override bool Serialize(Serializer ctx)
	{
		return ctx.Write(param1) && ctx.Write(param2) && ctx.Write(param3) && ctx.Write(param4) && ctx.Write(param5) && ctx.Write(param6) && ctx.Write(param7) && ctx.Write(param8);
	}
	
	override bool Deserializer(Serializer ctx)
	{
		return ctx.Read(param1) && ctx.Read(param2) && ctx.Read(param3) && ctx.Read(param4) && ctx.Read(param5) && ctx.Read(param6) && ctx.Read(param7) && ctx.Read(param8);
	}
};

/**
 \brief Tuple Class Template with nine parameters.
 */
class Tuple9<Class T1, Class T2, Class T3, Class T4, Class T5, Class T6, Class T7, Class T8, Class T9> extends Tuple
{
	T1 param1;
	T2 param2;
	T3 param3;
	T4 param4;
	T5 param5;
	T6 param6;
	T7 param7;
	T8 param8;
	T9 param9;

	void Tuple9(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9)
	{
		param1 = p1;
		param2 = p2;
		param3 = p3;
		param4 = p4;
		param5 = p5;
		param6 = p6;
		param7 = p7;
		param8 = p8;
		param9 = p9;
	}
	
	override bool Serialize(Serializer ctx)
	{
		return ctx.Write(param1) && ctx.Write(param2) && ctx.Write(param3) && ctx.Write(param4) && ctx.Write(param5) && ctx.Write(param6) && ctx.Write(param7) && ctx.Write(param8) && ctx.Write(param9);
	}
	
	override bool Deserializer(Serializer ctx)
	{
		return ctx.Read(param1) && ctx.Read(param2) && ctx.Read(param3) && ctx.Read(param4) && ctx.Read(param5) && ctx.Read(param6) && ctx.Read(param7) && ctx.Read(param8) && ctx.Read(param9);
	}
};