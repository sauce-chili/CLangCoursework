#include "pch.h"
#include "CppUnitTest.h"
#include "string.h"
#include "../CourseWork_Smirnov/Common.h"
#include "../CourseWork_Smirnov/FindVariables.h"
#include "../CourseWork_Smirnov/VariableNamingInspector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VariableNamingInspector
{
	TEST_CLASS(test_func_findLoopVariables) 
	{
		TEST_METHOD(Vars_of_do_while_loop) 
		{
			Text code = {
				{
				"int main()",
				"{",
				"	int a;",
				"	do",
				"	// float x = a++;",
				"	{",
				"		a + 1;",
				"	}",
				"	// some comment",
				"	while(a < 5);",
				"}"
				}, 11
			};
			Range range = { {0,0},{code.countOfString, code.text[code.countOfString - 1][0]} };

			VariableOccurrence allVars[MAX_COUNT_VAR];
			int countVarsInAllCode = findSingleLetterVariablesInCode(range, code, allVars);

			int expCoutLoopVars = 2;
			VariableOccurrence expLoopVars[MAX_COUNT_VAR] = {
				{"a",{6, 2}},
				{"a",{9, 7}}
			};

			VariableOccurrence actualLoopVars[MAX_COUNT_VAR];
			int actualCountLoopVars = findLoopVariables(allVars, countVarsInAllCode, &code, actualLoopVars);

			sortVariableOccurrencesArrayByOccurrence(actualLoopVars, actualCountLoopVars);

			int sizeAreEquals = expCoutLoopVars == actualCountLoopVars;
			int loopVarsAreEquals = memcmp(expLoopVars, actualLoopVars, sizeof(VariableOccurrence)*expCoutLoopVars) == 0;

			Assert::IsTrue(sizeAreEquals && loopVarsAreEquals);
		}

		TEST_METHOD(Vars_of_while_loop) 
		{
			Text code = {
				{
				"int main()",
				"{",
				"	int a;",
				"	while(a < 5);",
				"	// float x = a++;",
				"	{",
				"		a + 1;",
				"	}",
				"	// some comment",
				"	",
				"}"
				}, 11
			};
			Range range = { {0,0},{code.countOfString, code.text[code.countOfString - 1][0]} };

			VariableOccurrence allVars[MAX_COUNT_VAR];
			int countVarsInAllCode = findSingleLetterVariablesInCode(range, code, allVars);

			int expCoutLoopVars = 2;
			VariableOccurrence expLoopVars[MAX_COUNT_VAR] = {
				{"a",{3, 7}},
				{"a",{6, 2}}
			};

			VariableOccurrence actualLoopVars[MAX_COUNT_VAR];
			int actualCountLoopVars = findLoopVariables(allVars, countVarsInAllCode, &code, actualLoopVars);

			sortVariableOccurrencesArrayByOccurrence(actualLoopVars, actualCountLoopVars);

			int sizeAreEquals = expCoutLoopVars == actualCountLoopVars;
			int loopVarsAreEquals = memcmp(expLoopVars, actualLoopVars, sizeof(VariableOccurrence) * expCoutLoopVars) == 0;

			Assert::IsTrue(sizeAreEquals && loopVarsAreEquals);
		}

		TEST_METHOD(Vars_of_for_loop_1) 
		{
			Text code = {
					{
					"int main()",
					"{",
					"	 int b;",
					"	for(int a = 0; a < 5;)",
					"	{",
					"		a + 1;",
					"	}",
					"}"
					}, 8
			};
			Range range = { {0,0},{code.countOfString, code.text[code.countOfString - 1][0]} };

			VariableOccurrence allVars[MAX_COUNT_VAR];
			int countVarsInAllCode = findSingleLetterVariablesInCode(range, code, allVars);

			int expCoutLoopVars = 3;
			VariableOccurrence expLoopVars[MAX_COUNT_VAR] = {
				{"a",{3, 9}},
				{"a",{3, 16}},
				{"a",{5, 2}},
			};

			VariableOccurrence actualLoopVars[MAX_COUNT_VAR];
			int actualCountLoopVars = findLoopVariables(allVars, countVarsInAllCode, &code, actualLoopVars);

			sortVariableOccurrencesArrayByOccurrence(actualLoopVars, actualCountLoopVars);

			int sizeAreEquals = expCoutLoopVars == actualCountLoopVars;
			int loopVarsAreEquals = memcmp(expLoopVars, actualLoopVars, sizeof(VariableOccurrence) * expCoutLoopVars) == 0;

			Assert::IsTrue(sizeAreEquals && loopVarsAreEquals);
		}

		TEST_METHOD(Vars_of_for_loop_2) 
		{
			Text code = {
					{
					"int main()",
					"{",
					"	 int b;",
					"	for(int a = 0; a < 5; a++)",
					"	{",
					"	}",
					"}"
					}, 7
			};
			Range range = { {0,0},{code.countOfString, code.text[code.countOfString - 1][0]} };

			VariableOccurrence allVars[MAX_COUNT_VAR];
			int countVarsInAllCode = findSingleLetterVariablesInCode(range, code, allVars);

			int expCoutLoopVars = 3;
			VariableOccurrence expLoopVars[MAX_COUNT_VAR] = {
				{"a",{3, 9}},
				{"a",{3, 16}},
				{"a",{3,23}}
			};

			VariableOccurrence actualLoopVars[MAX_COUNT_VAR];
			int actualCountLoopVars = findLoopVariables(allVars, countVarsInAllCode, &code, actualLoopVars);

			sortVariableOccurrencesArrayByOccurrence(actualLoopVars, actualCountLoopVars);

			int sizeAreEquals = expCoutLoopVars == actualCountLoopVars;
			int loopVarsAreEquals = memcmp(expLoopVars, actualLoopVars, sizeof(VariableOccurrence) * expCoutLoopVars) == 0;

			Assert::IsTrue(sizeAreEquals && loopVarsAreEquals);
		}

		TEST_METHOD(Without_vars_of_loop) 
		{
			Text code = {
				{
				"int main()",
				"{",
				"	int a;",
				"	while(a < 5);",
				"	// float x = a++;",
				"	{",
				"		x + 1;",
				"	}",
				"	// some comment",
				"	",
				"}"
				}, 11
			};
			Range range = { {0,0},{code.countOfString, code.text[code.countOfString - 1][0]} };

			VariableOccurrence allVars[MAX_COUNT_VAR];
			int countVarsInAllCode = findSingleLetterVariablesInCode(range, code, allVars);

			int expCoutLoopVars = 0;
			VariableOccurrence expLoopVars[MAX_COUNT_VAR]; /*= {
				{"a",{3, 7}},
				{"a",{6, 2}}
			};*/

			VariableOccurrence actualLoopVars[MAX_COUNT_VAR];
			int actualCountLoopVars = findLoopVariables(allVars, countVarsInAllCode, &code, actualLoopVars);

			sortVariableOccurrencesArrayByOccurrence(actualLoopVars, actualCountLoopVars);

			int sizeAreEquals = expCoutLoopVars == actualCountLoopVars;
			int loopVarsAreEquals = memcmp(expLoopVars, actualLoopVars, sizeof(VariableOccurrence) * expCoutLoopVars) == 0;

			Assert::IsTrue(sizeAreEquals && loopVarsAreEquals);
		}

		TEST_METHOD(Without_vars_of_loop_2)
		{
			Text code = {
					{
					"int main()",
					"{",
					"	int q",
					"	for(int a = 0; q < 5;a++)",
					"	{",
					"		a + 1;",
					"	}",
					"}"
					}, 8
			};
			Range range = { {0,0},{code.countOfString, code.text[code.countOfString - 1][0]} };

			VariableOccurrence allVars[MAX_COUNT_VAR];
			int countVarsInAllCode = findSingleLetterVariablesInCode(range, code, allVars);

			int expCoutLoopVars = 0;
			VariableOccurrence expLoopVars[MAX_COUNT_VAR]; /*= {
				{"a",{3, 7}},
				{"a",{6, 2}}
			};*/

			VariableOccurrence actualLoopVars[MAX_COUNT_VAR];
			int actualCountLoopVars = findLoopVariables(allVars, countVarsInAllCode, &code, actualLoopVars);

			sortVariableOccurrencesArrayByOccurrence(actualLoopVars, actualCountLoopVars);

			int sizeAreEquals = expCoutLoopVars == actualCountLoopVars;
			int loopVarsAreEquals = memcmp(expLoopVars, actualLoopVars, sizeof(VariableOccurrence) * expCoutLoopVars) == 0;

			Assert::IsTrue(sizeAreEquals && loopVarsAreEquals);
		}

		TEST_METHOD(Vars_of_loop_in_nestd_loop) 
		{
			Text code = {
				{
				"int main()",
				"{",
				"	int q = 0;",
				"	for(int q=0; q < 10;q++)",
				"	{",
				"	}",
				"	int b = 0;",
				"	while(a < 100)",
				"	{",
				"		b++",
				"		do",
				"		{",
				"			a = a + 1",
				"		}",
				"		while(b > 0)",
				"	}",
				"}",
				}, 17
			};

			Range range = { {0,0},{code.countOfString, code.text[code.countOfString - 1][0]} };

			VariableOccurrence allVars[MAX_COUNT_VAR];
			int countVarsInAllCode = findSingleLetterVariablesInCode(range, code, allVars);

			int expCoutLoopVars = 6;
			VariableOccurrence expLoopVars[MAX_COUNT_VAR] = {
				{"q",{3, 9}},
				{"q",{3, 14}},
				{"q",{3, 21}},
				{"a",{7, 7}},
				{"a",{12, 3}},
				{"a",{12, 7}}
			};

			VariableOccurrence actualLoopVars[MAX_COUNT_VAR];
			int actualCountLoopVars = findLoopVariables(allVars, countVarsInAllCode, &code, actualLoopVars);

			sortVariableOccurrencesArrayByOccurrence(actualLoopVars, actualCountLoopVars);

			int sizeAreEquals = expCoutLoopVars == actualCountLoopVars;
			int loopVarsAreEquals = memcmp(expLoopVars, actualLoopVars, sizeof(VariableOccurrence) * expCoutLoopVars) == 0;

			Assert::IsTrue(sizeAreEquals && loopVarsAreEquals);
		}

		TEST_METHOD(While_and_Do_while_loop_located_near) 
		{
			Text code = {
				{
				"	int main()",
				"	{",
				"		int b;",
				"		do",
				"		{",
				"			int x",
				"		}",
				"		while((b < 2))",
				"		while(b > a)",
				"		{",
				"\n",
				"			b++;",
				"		}",
				"	}"
				}, 15 
			};
			
			Range range = { {0,0},{code.countOfString, code.text[code.countOfString - 1][0]} };

			VariableOccurrence allVars[MAX_COUNT_VAR];
			int countVarsInAllCode = findSingleLetterVariablesInCode(range, code, allVars);

			int expCoutLoopVars = 2;
			VariableOccurrence expLoopVars[MAX_COUNT_VAR] = {
				{"b",{8, 8}},
				{"b",{11, 3}}
			};

			VariableOccurrence actualLoopVars[MAX_COUNT_VAR];
			int actualCountLoopVars = findLoopVariables(allVars, countVarsInAllCode, &code, actualLoopVars);

			int sizeAreEquals = expCoutLoopVars == actualCountLoopVars;
			int loopVarsAreEquals = memcmp(expLoopVars, actualLoopVars, sizeof(VariableOccurrence) * expCoutLoopVars) == 0;

			Assert::IsTrue(sizeAreEquals && loopVarsAreEquals);
		}

		TEST_METHOD(No_loops_in_code_but_exist_simular_constration) 
		{
			Text code = {
				{
				"int main()",
				"{",
				"	int i;",
				"	_for(i, i < 0, i++);",
				"}"
				},4
			};

			Range range = { {0,0},{code.countOfString, code.text[code.countOfString - 1][0]} };

			VariableOccurrence allVars[MAX_COUNT_VAR];
			int countVarsInAllCode = findSingleLetterVariablesInCode(range, code, allVars);

			int expCoutLoopVars = 0;
			VariableOccurrence expLoopVars[MAX_COUNT_VAR];

			VariableOccurrence actualLoopVars[MAX_COUNT_VAR];
			int actualCountLoopVars = findLoopVariables(allVars, countVarsInAllCode, &code, actualLoopVars);
			
			sortVariableOccurrencesArrayByOccurrence(actualLoopVars, actualCountLoopVars);

			int sizeAreEquals = expCoutLoopVars == actualCountLoopVars;
			int loopVarsAreEquals = memcmp(expLoopVars, actualLoopVars, sizeof(VariableOccurrence) * expCoutLoopVars) == 0;

			Assert::IsTrue(sizeAreEquals && loopVarsAreEquals);
		}
	};
}