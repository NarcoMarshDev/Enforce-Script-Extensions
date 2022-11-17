#ifdef ESE_DEVMODE

int globalInt;

class TestClass
{
	static int a;
}

[main()]
int main()
{
	Print("main");
	ESE_Queue<int> queue = new ESE_Queue<int>(5);
	for (int i = 0; i < 7; i++)
	{
		queue.Enqueue(i);
	}
	Print(queue);
	Print(queue[3]);
	
	return 0;
}

int exitcode = main();
#endif