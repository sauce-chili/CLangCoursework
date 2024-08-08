#include "pch.h"
#include "CppUnitTest.h"
#include "string.h"
#include "../CourseWork_Smirnov/Common.h"
#include "../CourseWork_Smirnov/VariableNamingInspector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VariableNamingInspector
{
	TEST_CLASS(func_findBadVariableName)
	{
		/*
		int findBadVariablesNames(const char codeText[][MAX_CHAR_IN_STRING], int numberStrings, struct ReportRecord  badVariableReport[MAX_COUNT_STRING]);
		*/
	public:
		TEST_METHOD(oneBadVariable)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"int a;",
				"}"
			};
			int numberOfStrings = 4;


			const int expNumberOfBadVariable = 1;
			ReportRecord expBadVariableReport[expNumberOfBadVariable] = {
				{2, "a"}
			};


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(oneNotBadVariable)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int notBad;",
				"}"
			};
			int numberOfStrings = 4;


			const int expNumberOfBadVariable = 0;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING];


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(multipleBadVariable)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"int a;",
				"int b;",
				"}"
			};
			int numberOfStrings = 5;


			const int expNumberOfBadVariable = 2;
			ReportRecord expBadVariableReport[expNumberOfBadVariable] = {
				{2, "a"},
				{3, "b"}
			};


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(oneBadAndOneWellVariableInSnaleCase)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"int a;",
				"int not_bad;",
				"}"
			};
			int numberOfStrings = 5;


			const int expNumberOfBadVariable = 1;
			ReportRecord expBadVariableReport[expNumberOfBadVariable] = {
				{2, "a"}
			};


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(multipleBadAndAnyWellVariable)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"int notBad",
				"int a;",
				"int notBad2;",
				"int good;",
				"int b;",
				"int c;",
				"}"
			};
			int numberOfStrings = 9;


			const int expNumberOfBadVariable = 3;
			ReportRecord expBadVariableReport[expNumberOfBadVariable] = {
				{3, "a"},
				{6, "b"},
				{7, "c"}
			};


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(variablesInArithmeticExpressions)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"int a;",
				"int b;",
				"int good;",
				"good=a+b-good/a%good*b-2;",
				"}",
			};
			int numberOfStrings = 7;


			const int expNumberOfBadVariable = 4;
			ReportRecord expBadVariableReport[expNumberOfBadVariable] = {
				{2, "a"},
				{3, "b"},
				{5, "a"},
				{5, "b"}
			};


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(variablesAndLogicExpressions)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"int a;",
				"int b;",
				"int good;",
				"a>0&&b<10==good&&a!=b;",
				"}"
			};
			int numberOfStrings = 7;


			const int expNumberOfBadVariable = 4;
			ReportRecord expBadVariableReport[expNumberOfBadVariable] = {
				{2, "a"},
				{3, "b"},
				{5, "a"},
				{5, "b"}
			};

			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(declarationMultipleVariableOnOneLine)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"int a,good,b;",
				"}"
			};
			int numberOfStrings = 4;


			const int expNumberOfBadVariable = 2;
			ReportRecord expBadVariableReport[expNumberOfBadVariable] = {
					{2, "a"},
					{2, "b"}
			};


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(declrationAndInitializingVariable)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"int a=0;",
				"int notBad=1;",
				"}"
			};
			int numberOfStrings = 5;


			const int expNumberOfBadVariable = 1;
			ReportRecord expBadVariableReport[expNumberOfBadVariable] = {
				{2, "a"}
			};


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}


		TEST_METHOD(declarationAndInitializingMultipleVariableOnLine)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"int a=0,good=1,b=1;",
				"}"
			};
			int numberOfStrings = 4;

			const int expNumberOfBadVariable = 2;
			ReportRecord expBadVariableReport[expNumberOfBadVariable] = {
				{2, "a"},
				{2, "b"}
			};


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(declarationAndInitializingUsingComputedValue)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"int a=1;",
				"int notBad=a*9;",
				"}"
			};
			int numberOfStrings = 5;


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			const int expNumberOfBadVariable = 2;
			ReportRecord expBadVariableReport[expNumberOfBadVariable] = {
					{2, "a"},
					{3, "a"}
			};

			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(declarationWithInitializationByAssignmentAnotherVariable)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"int a=1;",
				"int notBad=a;",
				"}"
			};
			int numberOfStrings = 5;


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			const int expNumberOfBadVariable = 2;
			ReportRecord expBadVariableReport[expNumberOfBadVariable] = {
				{2, "a"},
				{3, "a"}
			};

			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(effecOfSpaceOnVariableDetection)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"int a = 0;",
				"  int notBad=1;",
				"}"
			};
			int numberOfStrings = 5;


			const int expNumberOfBadVariable = 1;
			ReportRecord expBadVariableReport[expNumberOfBadVariable] = {
				{2, "a"}
			};


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(effecOfTabsOnVariableDetection)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"int		a;",
				"int notBad;",
				"}"
			};
			int numberOfStrings = 5;


			const int expNumberOfBadVariable = 1;
			ReportRecord expBadVariableReport[expNumberOfBadVariable] = {
				{2, "a"}
			};


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(effecOfEmptyStringsOnVariableDetection)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"",
				"				",
				"	int a;",
				"				",
				"	int notBad;",
				"}"
			};
			int numberOfStrings = 5;


			const int expNumberOfBadVariable = 1;
			ReportRecord expBadVariableReport[expNumberOfBadVariable] = {
				{4, "a"}
			};


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(effecOfСommentOnVariableDetection)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int		a;",
				"	// some comment",
				"	int notBad;",
				"}"
			};
			int numberOfStrings = 6;


			const int expNumberOfBadVariable = 1;
			ReportRecord expBadVariableReport[expNumberOfBadVariable] = {
				{2, "a"}
			};


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(bad_variable_commented_out)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	// int	a;",
				"	int notBad;",
				"}"
			};
			int numberOfStrings = 5;


			const int expNumberOfBadVariable = 0;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING];


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(badVariableInIfStatement)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int a;",
				"	int notBad=0;",
				"	if(notBad==0)",
				"	{",
				"		a=0;",
				"	}",
				"}"
			};
			int numberOfStrings = 9;


			const int expNumberOfBadVariable = 2;
			ReportRecord expBadVariableReport[expNumberOfBadVariable] = {
				{2, "a"},
				{6, "a"}
			};


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(badVariableInIfStatementWithElseBrench)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int a=0;",
				"	int notBad=0;",
				"	if(a==0)",
				"	{",
				"		notBad=0;",
				"	}",
				"	else",
				"	{",
				"		a=1",
				"	}",
				"}"
			};
			int numberOfStrings = 13;


			const int expNumberOfBadVariable = 3;
			ReportRecord expBadVariableReport[expNumberOfBadVariable] = {
				{2, "a"},
				{4, "a"},
				{10, "a"}
			};


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(badVariableInElseIfBrench)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int a=0;",
				"	int notBad=0;",
				"	if(a==0)",
				"	{",
				"		notBad=0;",
				"	}",
				"	else if(a!=0)",
				"	{",
				"		a=1;",
				"	}",
				"}"
			};
			int numberOfStrings = 13;


			const int expNumberOfBadVariable = 4;
			ReportRecord expBadVariableReport[expNumberOfBadVariable] = {
				{2, "a"},
				{4, "a"},
				{8, "a"},
				{10, "a"}
			};


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(badVariableInSwitchHeader)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int a=0;",
				"	int notBad=0;",
				"	switch(a)",
				"	{",
				"		case 0:",
				"		break;",
				"	}",
				"}"
			};
			int numberOfStrings = 10;


			const int expNumberOfBadVariable = 2;
			ReportRecord expBadVariableReport[expNumberOfBadVariable] = {
				{2, "a"},
				{4, "a"},
			};


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(badVariableInSwitchCaseBrench)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int a=0;",
				"	int notBad=0;",
				"	switch(notBad)",
				"	{",
				"		case 0:",
				"			a=1;",
				"			break;",
				"	}",
				"}"
			};
			int numberOfStrings = 11;


			const int expNumberOfBadVariable = 2;
			ReportRecord expBadVariableReport[expNumberOfBadVariable] = {
				{2, "a"},
				{7, "a"}
			};


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(badVariableInDefaultBrenchOfSwitch)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int a=0;",
				"	int notBad=0;",
				"	switch(notBad)",
				"	{",
				"		case 0: ",
				"		break;",
				"		default:",
				"			a=1;",
				"	}",
				"}"
			};
			int numberOfStrings = 12;

			const int expNumberOfBadVariable = 2;
			ReportRecord expBadVariableReport[expNumberOfBadVariable] = {
				{2, "a"},
				{9, "a"}
			};


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}


		TEST_METHOD(badVariablesInScopeOperator)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int a;",
				"	{",
				"		a=2;",
				"	}",
				"}"
			};
			int numberOfStrings = 7;


			const int expNumberOfBadVariable = 2;
			ReportRecord expBadVariableReport[expNumberOfBadVariable] = {
				{2, "a"},
				{4, "a"}
			};


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(badVariableIntoHeaderOfWhileLoop)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int a;",
				"	while(a > 5)",
				"	{",
				"	}",
				"}"
			};
			int numberOfStrings = 8;

			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);

			const int expNumberOfBadVariable = 2;
			ReportRecord expBadVariableReport[expNumberOfBadVariable] = {
				{2, "a"},
				{3, "a"}
			};

			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(badVariavleInForLoopHeader)
		{
			// третья часть цикла for - считаем телом цикла, 2 перавый усл
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int a;",
				"	for(a = 0; a < 5;)",
				"	{",
				"		1;",
				"	}",
				"}"
			};
			int numberOfStrings = 8;

			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);

			const int expNumberOfBadVariable = 2;
			ReportRecord expBadVariableReport[expNumberOfBadVariable] = {
				{2, "a"},
				{3, "a"},
			};

			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(badVariableInBodyOfForLoop)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int a,notBad;",
				"	for(notBad = 0; notBad < 5; notBad++)",
				"	{",
				"		a + 1;",
				"	}",
				"}"
			};
			int numberOfStrings = 8;

			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);

			const int expNumberOfBadVariable = 2;
			ReportRecord expBadVariableReport[expNumberOfBadVariable] = {
				{2, "a"},
				{5, "a"}
			};

			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(variableIsAWhileLoopVariable)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int a;",
				"	while(a < 5)",
				"	{",
				"		a + 1;",
				"	}",
				"}"
			};
			int numberOfStrings = 8;

			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);

			const int expNumberOfBadVariable = 0;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING]; // = { {2, "a"} };

			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(comment_between_header_and_body_of_loop)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int a;",
				"	while(a < 5)",
				"	// some comment",
				"	{",
				"		a + 1;",
				"	}",
				"}"
			};
			int numberOfStrings = 9;

			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);

			const int expNumberOfBadVariable = 0;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING]; //= { {2, "a"} };

			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(badVariableOnlyInHeaderOfDoWhileLoop)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int a;",
				"	do",
				"	{",
				"		;",
				"	}",
				"	while(a < 5);",
				"}"
			};
			int numberOfStrings = 9;

			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);

			const int expNumberOfBadVariable = 2;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING] = {
				{2,"a"},
				{7,"a"}
			};

			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(badVariableInBodyOfDoWhileLoop)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int a;",
				"	do",
				"	{",
				"		a+1;",
				"	}",
				"	while(1);",
				"}"
			};
			int numberOfStrings = 9;

			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);

			const int expNumberOfBadVariable = 2;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING] = {
				{2,"a"},
				{5,"a"}
			};

			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(variableIsADoWhileLoopVariable)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int a;",
				"	do",
				"	{",
				"		a + 1;",
				"	}",
				"	while(a < 5);",
				"}"
			};
			int numberOfStrings = 9;

			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);

			const int expNumberOfBadVariable = 0;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING];

			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(comment_between_header_and_body_of_do_while_loop)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int b,a;",
				"	do",
				"	// some comment 1",
				"	{",
				"		a + 1;",
				"	}",
				"	// some comment 2",
				"	while(a < 5);",
				"}"
			};
			int numberOfStrings = 11;

			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);

			const int expNumberOfBadVariable = 1;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING] = { 2,"b" };

			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(variableIsAForLoopVariable)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int b;",
				"	for(int a = 0; a < 5; a++)",
				"	{",
				"		a + 1;",
				"	}",
				"}"
			};
			int numberOfStrings = 8;

			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);

			const int expNumberOfBadVariable = 1;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING] = {2, "b"};

			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(variableIsAForLoopVariable_2)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int b;",
				"	for(int a = 0; a < 5; a++)",
				"	{",
				"		1 + 1;",
				"	}",
				"}"
			};
			int numberOfStrings = 8;

			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);

			const int expNumberOfBadVariable = 1;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING] = { 2, "b" };

			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(The_variable_is_used_only_in_the_initialization_block)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int q,notBad;",
				"	for(q = 0, notBad = 0; notBad < 5; notBad++)",
				"	{",
				"		q + 1;",
				"	}",
				"}"
			};
			int numberOfStrings = 8;

			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);

			const int expNumberOfBadVariable = 3;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING] =
			{
				{2, "q"},
				{3, "q"},
				{5, "q"}
			};

			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(The_variable_is_used_only_in_the_condition_block)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int q,notBad;",
				"	for(notBad = 0; q < 5; notBad++)",
				"	{",
				"		q+1;",
				"	}",
				"}"
			};

			int numberOfStrings = 8;

			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);

			const int expNumberOfBadVariable = 3;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING] =
			{
				{2, "q"},
				{3, "q"},
				{5, "q"}
			};

			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(The_variable_is_used_only_in_the_increment_block)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int q,notBad;",
				"	for(notBad = 0; notBad < 5; q++)",
				"	{",
				"		",
				"	}",
				"}"
			};
			int numberOfStrings = 8;

			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);

			const int expNumberOfBadVariable = 2;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING] = {
				{2, "q"},
				{3, "q"}
			};

			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(loopVariableIsUsedOutsideTheLoop)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	",
				"	for(int a = 0; a < 5;)",
				"	{",
				"		a + 1;",
				"	}",
				"	a+1;",
				"}"
			};
			int numberOfStrings = 9;

			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);

			const int expNumberOfBadVariable = 0;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING];

			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(loopVariableIsUsedInsideNestedLoop_1)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	",
				"	for(int a = 0; a < 5;)",
				"	{",
				"		int b;",
				"		while(b < 2)",
				"		{",
				"			a++",
				"		}",
				"	}",
				"}"
			};
			int numberOfStrings = 11;

			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);

			const int expNumberOfBadVariable = 2;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING] =
			{
				{5, "b"},
				{6, "b"}
			};

			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(loopVariableIsUsedInsideNestedLoop_2) 
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

			const int expNumberOfBadVariable = 3;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING] =
			{
				{6, "b"},
				{9, "b"},
				{14,"b"}
			};

			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(code, actualBadVariableReport);

			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(Variables_are_used_in_adjacent_do_while_while_loops) 
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	",
				"	for(int a = 0; a < 5;)",
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
				"	}",
				"}"
			};
			int numberOfStrings = 18;

			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);

			const int expNumberOfBadVariable = 1;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING] =
			{
				{8, "x"}
			};

			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(Outer_loop_variable_used_inside_nested_loop)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int a,i;",
				"	for (i=0;i<5;i++)",
				"	{",
				"		int x = -2;",
				"		while(x<0)",
				"		{",
				"			x + i;",
				"		}",
				"	}",
				"}"
			};
			int numberOfStrings = 12;

			const int expNumberOfBadVariable = 1;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING] = 
			{
				{2, "a"}
			};

			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);

			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}


		TEST_METHOD(loopVariableIsUsedInsideNestedIf)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int a;",
				"	for(a = 0; a < 5; i++)",
				"	{",
				"		if(a < 2)",
				"		{",
				"			a--;",
				"		}",
				"	}",
				"}"
			};
			int numberOfStrings = 11;

			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);

			const int expNumberOfBadVariable = 1;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING] = {3, "i"};

			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(loopVariableIsUsedInsideNestedScopeOperator)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int a;",
				"	for(i = 0; i < 5; i++)",
				"	{",
				"		",
				"		{",
				"			a+1;",
				"		}",
				"	}",
				"}"
			};
			int numberOfStrings = 11;

			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);

			const int expNumberOfBadVariable = 2;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING] = {
				{2,"a"},
				{7,"a"}
			};

			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(FunctionInvokeLooksLikeBadVariable)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	f();",
				"}"
			};
			int numberOfStrings = 4;


			const int expNumberOfBadVariable = 0;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING];


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(BeginOfVariableNameLooksLikeBeginOfLoop_1)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	bool whileSelect;",
				"}"
			};
			int numberOfStrings = 4;


			const int expNumberOfBadVariable = 0;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING];


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(BeginOfVariableNameLooksLikeBeginOfLoop_2)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int i;",
				"	_for(i, i < 0, i++);",
				"}"
			};
			int numberOfStrings = 4;


			const int expNumberOfBadVariable = 2;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING] = {
				{2, "i"},
				{3, "i"}
			};


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(variableNameSubstringOfAnotherVariable)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	bool h;",
				"	int	hh",
				"}"
			};
			int numberOfStrings = 5;


			const int expNumberOfBadVariable = 1;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING] = {
				{2, "h"}
			};


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(variableNameSubstringOfSomeOperator)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	bool h;",
				"	while(1)",
				"	{",
				"		;",
				"	}",
				"}"
			};
			int numberOfStrings = 8;


			const int expNumberOfBadVariable = 1;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING] = {
				{2, "h"}
			};


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(badVariableInsideFunctionArguments)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int h;",
				"	hex(h)",
				"}"
			};
			int numberOfStrings = 5;


			const int expNumberOfBadVariable = 2;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING] = {
				{2, "h"},
				{3, "h"}
			};


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);

			Assert::IsTrue(cmpReports(
				expBadVariableReport, expNumberOfBadVariable,
				actualBadVariableReport, actualNumberOfBadVariable)
			);
		}

		TEST_METHOD(severalBadVariablesInsideFunctionArguments)
		{
			char codeText[MAX_COUNT_STRING][MAX_CHAR_IN_STRING] = {
				"int main()",
				"{",
				"	int a,h;",
				"	func(h,a)",
				"}"
			};
			int numberOfStrings = 5;


			const int expNumberOfBadVariable = 4;
			ReportRecord expBadVariableReport[MAX_COUNT_STRING] = {
				{2, "a"},
				{2, "h"},
				{3, "h"},
				{3, "a"}
			};


			ReportRecord actualBadVariableReport[MAX_COUNT_STRING];
			int actualNumberOfBadVariable = findBadVariablesNames(codeText, numberOfStrings, actualBadVariableReport);


			Assert::IsTrue(cmpReports(
					expBadVariableReport, expNumberOfBadVariable,
					actualBadVariableReport, actualNumberOfBadVariable)
			);
		}
	};
}