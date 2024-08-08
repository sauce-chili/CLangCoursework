#include "pch.h"
#include "CppUnitTest.h"
#include "../CourseWork_Smirnov/FindVariables.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FindSingleLetterVariablesTest
{
	TEST_CLASS(test_func_findSingleLetterVariableInCode) 
	{
		TEST_METHOD(Finding_one_single_letter_variable_in_code) 
		{
			Text code = {
				{
				"int main()",
				"{",
				"int a;",
				"int not_bad;",
				"}"
				}, 5 
			};
			Occurrence startSearch = { 0, 0 };
			Occurrence endSearch = { code.countOfString - 1, 0 };


			int expCountOfOccVar = 1;
			VariableOccurrence expVarOccurrence[] = {
				{"a",{2, 4}},
			};

			VariableOccurrence actualVarOccurence[MAX_COUNT_VAR];
			int actualCountOfVars = findSingleLetterVariablesInCode(
				startSearch, endSearch,
				code, actualVarOccurence
			);

			int varsAreEqual = memcmp(expVarOccurrence, actualVarOccurence, sizeof(VariableOccurrence) * expCountOfOccVar) == 0;
			Assert::IsTrue(
				expCountOfOccVar == actualCountOfVars &&
				varsAreEqual
			);
		}

		TEST_METHOD(Several_single_letter_variables_in_the_code) 
		{
			Text code = {
				{
				"int main()",
				"{",
				"int notBad",
				"int a;",
				"int notBad2;",
				"int good;",
				"int b;",
				"int c;",
				"}"
				}, 9
			};
			Occurrence startSearch = { 0, 0 };
			Occurrence endSearch = { code.countOfString - 1, 0 };


			int expCountOfOccVar = 3;
			VariableOccurrence expVarOccurrence[] = {
				{"a",{3, 4}},
				{"b",{6, 4}},
				{"c",{7, 4}}
			};

			VariableOccurrence actualVarOccurence[MAX_COUNT_VAR];
			int actualCountOfVars = findSingleLetterVariablesInCode(
				startSearch, endSearch,
				code, actualVarOccurence
			);

			int varsAreEqual = memcmp(expVarOccurrence, actualVarOccurence, sizeof(VariableOccurrence) * expCountOfOccVar) == 0;
			Assert::IsTrue(
				expCountOfOccVar == actualCountOfVars &&
				varsAreEqual
			);
		}

		TEST_METHOD(Several_single_letter_variables_in_the_code_inizilazing_in_one_string) 
		{
			Text code = {
				{
				"int main()",
				"{",
				"int a=0,good=1,b=1;",
				"}"
				}, 4
			};
			Occurrence startSearch = { 0, 0 };
			Occurrence endSearch = { code.countOfString - 1, 0 };


			int expCountOfOccVar = 2;
			VariableOccurrence expVarOccurrence[] = {
				{"a",{2, 4}},
				{"b",{2, 15}},
			};

			VariableOccurrence actualVarOccurence[MAX_COUNT_VAR];
			int actualCountOfVars = findSingleLetterVariablesInCode(
				startSearch, endSearch,
				code, actualVarOccurence
			);

			int varsAreEqual = memcmp(expVarOccurrence, actualVarOccurence, sizeof(VariableOccurrence) * expCountOfOccVar) == 0;
			Assert::IsTrue(
				expCountOfOccVar == actualCountOfVars &&
				varsAreEqual
			);
		}

		TEST_METHOD(Single_letter_variables_in_arithmetic_expression)
		{
			Text code = {
				{
				"int main()",
				"{",
				"int a;",
				"int b;",
				"int good;",
				"good=a+b-good/a%good*b-2;",
				"}",
				}, 7 
			};
			Occurrence startSearch = { 0, 0 };
			Occurrence endSearch = { code.countOfString - 1, 0 };


			int expCountOfOccVar = 6;
			VariableOccurrence expVarOccurrence[] = {
				{"a",{2, 4}},
				{"b",{3, 4}},
				{"a",{5, 5}},
				{"b",{5, 7}},
				{"a",{5, 14}},
				{"b",{5, 21}}
			};

			VariableOccurrence actualVarOccurence[MAX_COUNT_VAR];
			int actualCountOfVars = findSingleLetterVariablesInCode(
				startSearch, endSearch,
				code, actualVarOccurence
			);

			int varsAreEqual = memcmp(expVarOccurrence, actualVarOccurence, sizeof(VariableOccurrence) * expCountOfOccVar) == 0;
			Assert::IsTrue(
				expCountOfOccVar == actualCountOfVars &&
				varsAreEqual
			);
		}

		TEST_METHOD(Search_for_single_letter_variables_within_certain_scope_1) 
		{
			Text code = {
					{
					"int main()",
					"{",
					"	double x;",
					"	float _x  = 2.5f;",
					"   {",
					"		int q;",
					"		float tmp;",
					"   }",
					"}"
					}, 9
			};
			Occurrence startSearch = { 4, 2 };
			Occurrence endSearch = { 7, 2 };


			int expCountOfVar = 1;
			VariableOccurrence expVarOccurrence[] = {
				{"q",{5, 6}},
			};

			VariableOccurrence actualVarOccurence[MAX_COUNT_VAR];
			int actualCountOfVars = findSingleLetterVariablesInCode(
				startSearch, endSearch,
				code, actualVarOccurence
			);

			int varsAreEqual = memcmp(expVarOccurrence, actualVarOccurence, sizeof(VariableOccurrence) * expCountOfVar) == 0;
			Assert::IsTrue(
				expCountOfVar == actualCountOfVars &&
				varsAreEqual
			);
		}

		TEST_METHOD(Search_for_single_letter_variables_within_certain_scope_2)
		{
			Text code = {
					{
					"int main()",
					"{",
					"	double x;",
					"	float _x  = 2.5f;",
					"   for(int q; q<5; q++);",
					"}"
					}, 6
			};
			Occurrence startSearch = { 4, 6 };
			Occurrence endSearch = { 4, 22 };


			int expCountOfVar = 3;
			VariableOccurrence expVarOccurrence[] = {
				{"q",{4, 11}},
				{"q",{4, 14}},
				{"q",{4, 19}},
			};

			VariableOccurrence actualVarOccurence[MAX_COUNT_VAR];
			int actualCountOfVars = findSingleLetterVariablesInCode(
				startSearch, endSearch,
				code, actualVarOccurence
			);

			int varsAreEqual = memcmp(expVarOccurrence, actualVarOccurence, sizeof(VariableOccurrence) * expCountOfVar) == 0;
			Assert::IsTrue(
				expCountOfVar == actualCountOfVars &&
				varsAreEqual
			);
		}

		TEST_METHOD(Single_letter_variables_in_the_loop_header_and_body) 
		{
			Text code = {
					{
					"int main()",
					"{",
					"	 ",
					"	for(int a = 0; a < 5; a++)",
					"	{",
					"		a + 1;",
					"	}",
					"}"
					}, 8
			};
			Occurrence startSearch = { 0, 0 };
			Occurrence endSearch = { code.countOfString - 1, 0 };


			int expCountOfVar = 4;
			VariableOccurrence expVarOccurrence[] = {
				{"a",{3, 9}},
				{"a",{3, 16}},
				{"a",{3, 23}},
				{"a",{5, 2}},
			};

			VariableOccurrence actualVarOccurence[MAX_COUNT_VAR];
			int actualCountOfVars = findSingleLetterVariablesInCode(
				startSearch, endSearch,
				code, actualVarOccurence
			);

			int varsAreEqual = memcmp(expVarOccurrence, actualVarOccurence, sizeof(VariableOccurrence) * expCountOfVar) == 0;
			Assert::IsTrue(
				expCountOfVar == actualCountOfVars &&
				varsAreEqual
			);
		}

		TEST_METHOD(Detecting_variables_in_nested_constructs)
		{
			Text code = {
					{
					"int main()",
					"{",
					"	int a,q;",
					"	for (q=0;q<5;q++)",
					"	{",
					"		int x = -2;",
					"		while(x<0)",
					"		{",
					"			swith(x)",
					"			{",
					"				case 0:",
					"					x--;",
					"				case 2:",
					"					break;",
					"				default:",
					"					a = 0",
					"			}",
					"		}",
					"	}",
					"}"
					}, 20
			};
			Occurrence startSearch = { 0, 0 };
			Occurrence endSearch = { code.countOfString - 1, 0 };


			int expCountOfVar = 10;
			VariableOccurrence expVarOccurrence[] = {
				{"a",{2, 5}},
				{"q",{2, 7}},
				{"q",{3, 6}},
				{"q",{3, 10}},
				{"q",{3, 14}},
				{"x",{5, 6}},
				{"x",{6, 8}},
				{"x",{8, 9}},
				{"x",{11, 5}},
				{"a",{15, 5}},
			};

			VariableOccurrence actualVarOccurence[MAX_COUNT_VAR];
			int actualCountOfVars = findSingleLetterVariablesInCode(
				startSearch, endSearch,
				code, actualVarOccurence
			);

			int varsAreEqual = memcmp(expVarOccurrence, actualVarOccurence, sizeof(VariableOccurrence) * expCountOfVar) == 0;
			Assert::IsTrue(
				expCountOfVar == actualCountOfVars &&
				varsAreEqual
			);
		}

		TEST_METHOD(Single_letter_variable_in_an_expression_inside_a_comment)
		{
			Text code = {
					{
					"int main()",
					"{",
					"	double x; // int	a;",
					"	long _x  = 5LL;",
					"}"
					}, 5
			};
			Occurrence startSearch = { 0, 0 };
			Occurrence endSearch = { code.countOfString - 1, 0 };

			int expCountOfOccVar = 1;
			VariableOccurrence expVarOccurrence[] = {
				{"x",{2, 8}},
			};

			VariableOccurrence actualVarOccurence[MAX_COUNT_VAR];
			int actualCountOfVars = findSingleLetterVariablesInCode(
				startSearch, endSearch,
				code, actualVarOccurence
			);

			int varsAreEqual = memcmp(expVarOccurrence, actualVarOccurence, sizeof(VariableOccurrence) * expCountOfOccVar) == 0;
			Assert::IsTrue(
				expCountOfOccVar == actualCountOfVars &&
				varsAreEqual
			);
		}

		TEST_METHOD(Comments_between_different_parts_of_the_loop) 
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
			Occurrence startSearch = { 0, 0 };
			Occurrence endSearch = { code.countOfString - 1, 0 };

			int expCountOfOccVar = 3;
			VariableOccurrence expVarOccurrence[] = {
				{"a",{2, 5}},
				{"a",{6, 2}},
				{"a",{9, 7}},
			};

			VariableOccurrence actualVarOccurence[MAX_COUNT_VAR];
			int actualCountOfVars = findSingleLetterVariablesInCode(
				startSearch, endSearch,
				code, actualVarOccurence
			);

			int varsAreEqual = memcmp(expVarOccurrence, actualVarOccurence, sizeof(VariableOccurrence) * expCountOfOccVar) == 0;
			Assert::IsTrue(
				expCountOfOccVar == actualCountOfVars &&
				varsAreEqual
			);
		}
	};
}