#ifdef ESE_DEVMODE

int globalInt;

//[BaseContainerProps(configRoot: true)]
class TestClass
{
	static int swag = 5;
	
	static int a = 1;
	private static int b = 2;
	protected string bruh = "SWAGGIN";
	float flt = 3.021;
	ref array<int> intArray = {1,2,3,4,5};
	ref array<TestClass> testArray = {};
	
	private static string Bruh(int greg) //#FUNCTION
	{
		Print("private function" + greg);
		return "hello there";
	}
	
	static void Bruh2()
	{
		Print("public function");
	}
	
	void Bruh3()
	{
		Print("non-static function");
	}
	
	static int Bruh4(int in)
	{
		Print("Invoked Function: " + in);
		return 5;
	}
	void PrintPrivateValue(int val)
	{
		Print(val);
	}
}

[main()]
int main()
{
	TestClass obj = new TestClass();

	
	auto objptr = (BaseContainer)obj;
	Print(objptr);
	
	return 0;
}

int exitcode = main();
#endif
