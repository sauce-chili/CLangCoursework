#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "testing.h"
#include "VariableNamingInspector.h"

int main()
{
	int countOfLines = 0;
	//input_printf("Input count of strings in your program:\n");
	scanf_s("%d", &countOfLines);
	getchar();

	if (1 >= countOfLines || countOfLines > MAX_COUNT_STRING) 
	{
		
		error_printf("Wrong count of strings!\n");
		return 0;
	}


	Text code;
	code.countOfString = countOfLines;

	//input_printf("Input text of program:\n");
	for (int i = 0; i < countOfLines; i++) 
	{
		gets_s(code.text[i]);
	}
	
	Report badVariableReport;
	int countOfBadVariables = findBadVariablesNames(code, badVariableReport);

	if (countOfBadVariables == 0) 
	{
		printf("all is correct\n");
		return 0;
	}

	for (int i = 0; i < countOfBadVariables; i++) 
	{
		printf("%d, ", badVariableReport[i].indexStr);
		printf("%s\n", badVariableReport[i].value);
	}

	return 0;
}


/*
13
int main()
{
	for(int i = 0; i < 5; i++)
	{
		do
		{
			1E5 + 0x4245;
		}
		while(1)
	}

	return 0;
}
*/

/*
10
int main()
{
		for(int i = 0; i < 10;)
		{
				//int a = i + 1;
		}
		f(i);
		//int b = 0;
		return 0;
}
*/

/*
20
int main()
{
	int a,b;
	for(int a = 0; a < 10; a++)
	{
		do
		{ // some commnet
			if(1)
			{
				b++;
			}
		}
		while(a < 5)
		while(b > 0)
		// int b = 0
		{
			{a + a};
		}
	}
}
*/