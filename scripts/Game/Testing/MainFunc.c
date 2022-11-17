#ifdef ESE_DEVMODE

int globalInt;

class TestClass
{
	static int a;
}

[ESE_Preprocessor().Register()]
int main()
{
	Print("main");
	Print(globalInt);
	
	
	
	return 0;
}

int exitcode = main();
#endif