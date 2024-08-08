#include "pch.h"
#include "CppUnitTest.h"
#include "../CourseWork_Smirnov/FindLoop.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FindLoopTest
{
	TEST_CLASS(test_funct_findLoopKeyword) 
	{
		TEST_METHOD(Name_of_function_simular_on_keyword_of_loop_1) 
		{
			char str[] = "	forEach(coro -> coro.cancel())";

			char* startStr = &str[0];
			char* endStr = &str[strlen(str) - 1];

			Word* expKeyword = NULL;
			Word* actualKeyword = findLoopKeywordInString(startStr, endStr);

			int keywordsAreEqual = expKeyword == actualKeyword;
			Assert::IsTrue(keywordsAreEqual);
		}

		TEST_METHOD(Name_of_function_simular_on_keyword_of_loop_2)
		{
			char str[] = "	for_()";

			char* startStr = &str[0];
			char* endStr = &str[strlen(str) - 1];

			Word* expKeyword = NULL;
			Word* actualKeyword = findLoopKeywordInString(startStr, endStr);

			int keywordsAreEqual = expKeyword == actualKeyword;
			Assert::IsTrue(keywordsAreEqual);
		}

		TEST_METHOD(Name_of_function_simular_on_keyword_of_loop_3)
		{
			char str[] = "	_for()";

			char* startStr = &str[0];
			char* endStr = &str[strlen(str) - 1];

			Word* expKeyword = NULL;
			Word* actualKeyword = findLoopKeywordInString(startStr, endStr);

			int keywordsAreEqual = expKeyword == actualKeyword;
			Assert::IsTrue(keywordsAreEqual);
		}

		TEST_METHOD(Name_of_variable_simular_on_keyword_of_loop)
		{
			char str[] = "bool whileConnect = hasConnect();";

			char* startStr = &str[0];
			char* endStr = &str[strlen(str) - 1];

			Word* expKeyword = NULL;
			Word* actualKeyword = findLoopKeywordInString(startStr, endStr);

			int keywordsAreEqual = expKeyword == actualKeyword;
			Assert::IsTrue(keywordsAreEqual);
		}

		TEST_METHOD(String_without_word) 
		{
			char str[] = "					";

			char* startStr = &str[0];
			char* endStr = &str[strlen(str) - 1];

			Word* expKeyword = NULL;
			Word* actualKeyword = findLoopKeywordInString(startStr, endStr);

			int keywordsAreEqual = expKeyword == actualKeyword;
			Assert::IsTrue(keywordsAreEqual);
		}

		TEST_METHOD(The_line_contains_the_while_loop_keyword) 
		{
			char str[] = "	while(1)";

			char* startStr = &str[0];
			char* endStr = &str[strlen(str) - 1];

			Word keyword = { &str[1], &str[5] };
			Word* expKeyword = &keyword;
			Word* actualKeyword = findLoopKeywordInString(startStr, endStr);


			int keywordsAreEqual = memcmp(expKeyword, actualKeyword, sizeof(Word)) == 0;
			Assert::IsTrue(keywordsAreEqual);
		}

		TEST_METHOD(The_line_contains_the_for_loop_keyword)
		{
			char str[] = "	for(int i = 0; i < 5; i++)";

			char* startStr = &str[0];
			char* endStr = &str[strlen(str) - 1];

			Word keyword = { &str[1], &str[3] };
			Word* expKeyword = &keyword;
			Word* actualKeyword = findLoopKeywordInString(startStr, endStr);


			int keywordsAreEqual = memcmp(expKeyword, actualKeyword, sizeof(Word)) == 0;
			Assert::IsTrue(keywordsAreEqual);
		}

		TEST_METHOD(The_line_contains_the_do_while_loop_keyword)
		{
			char str[] = "	do";

			char* startStr = &str[0];
			char* endStr = &str[strlen(str) - 1];

			Word keyword = { &str[1], &str[2] };
			Word* expKeyword = &keyword;
			Word* actualKeyword = findLoopKeywordInString(startStr, endStr);


			int keywordsAreEqual = memcmp(expKeyword, actualKeyword, sizeof(Word)) == 0;
			Assert::IsTrue(keywordsAreEqual);
		}
	};

	TEST_CLASS(test_func_findWhileLoop)
	{
		TEST_METHOD(Simple_detect_while_loop)
		{
			Text code = {
				{
				"int main()",
				"{",
				"		while (1)",
				"		{",
				"			func();",
				"		}",
				"}"
				}, 7
			};

			Range range = { {2, 2}, {6, 2} };

			LoopOccurrence expOccLoop = {
				TYPE_LOOP::WHILE,
				{ {2, 8}, {2, 10} },
				{ {3, 2},  {5, 2} },
			};

			LoopOccurrence actualOccLoop;
			actualOccLoop.type = TYPE_LOOP::WHILE;

			findOccurrenceOfWhileLoop(range, &code, &actualOccLoop);

			int occAreEqual = memcmp(&expOccLoop, &actualOccLoop, sizeof(LoopOccurrence)) == 0;
			Assert::IsTrue(occAreEqual);
		}

		TEST_METHOD(There_are_nested_parentheses_inside_the_header) 
		{
			Text code = {
				{
				"int main()",
				"{",
				"		while ((x > 0 || (x - 1) < rBorder) || (x == -1))",
				"		{",
				"			func();",
				"		}",
				"}"
				}, 7
			};

			Range range = { {2, 2}, {6, 2} };

			LoopOccurrence expOccLoop = {
				TYPE_LOOP::WHILE,
				{ {2, 8}, {2, 50} },
				{ {3, 2},  {5, 2} },
			};

			LoopOccurrence actualOccLoop;
			actualOccLoop.type = TYPE_LOOP::WHILE;

			findOccurrenceOfWhileLoop(range, &code, &actualOccLoop);

			int occAreEqual = memcmp(&expOccLoop, &actualOccLoop, sizeof(LoopOccurrence)) == 0;
			Assert::IsTrue(occAreEqual);
		}

		TEST_METHOD(There_are_comments_between_the_loop_head_and_body)
		{
			Text code = {
				{
				"int main()",
				"{",
				"		while (1)",
				"		// if (1) {}",
				"		// {}",
				"		",
				"		{",
				"			func();",
				"		// }",
				"		}",
				"}"
				}, 11
			};

			Range range = { {2, 2}, {10, 2} };

			LoopOccurrence expOccLoop = {
				TYPE_LOOP::WHILE,
				{ {2, 8}, {2, 10} },
				{ {6, 2},  {9, 2} },
			};

			LoopOccurrence actualOccLoop;
			actualOccLoop.type = TYPE_LOOP::WHILE;

			findOccurrenceOfWhileLoop(range, &code, &actualOccLoop);

			int occAreEqual = memcmp(&expOccLoop, &actualOccLoop, sizeof(LoopOccurrence)) == 0;
			Assert::IsTrue(occAreEqual);
		}

		TEST_METHOD(There_are_loops_and_branches_inside_the_loop_body)
		{
			Text code = {
				{
				"int main()",
				"{",
				"		while (f(x))",
				"		",
				"		{",
				"			if(func())",
				"			{",
				"				while(1)",
				"				{",
				"					;",
				"				}",
				"			}",
				"		// }",
				"		}",
				"}"
				}, 15
			};

			Range range = { {2, 2}, {14, 2} };

			LoopOccurrence expOccLoop = {
				TYPE_LOOP::WHILE,
				{ {2, 8}, {2, 13} },
				{ {4, 2},  {13, 2} },
			};

			LoopOccurrence actualOccLoop;
			actualOccLoop.type = TYPE_LOOP::WHILE;

			findOccurrenceOfWhileLoop(range, &code, &actualOccLoop);

			int occAreEqual = memcmp(&expOccLoop, &actualOccLoop, sizeof(LoopOccurrence)) == 0;
			Assert::IsTrue(occAreEqual);
		}
	};

	TEST_CLASS(test_func_findForLoop) 
	{
		TEST_METHOD(Simple_detect_for_loop) 
		{
			Text code = {
				{
				"int main()",
				"{",
				"		for		(;;)",
				"		{",
				"			func();",
				"		}",
				"}"
				}, 7
			};

			Range range = { {2, 2}, {6, 2} };

			LoopOccurrence expOccLoop = {
				TYPE_LOOP::FOR,
				{ {2, 7}, {2, 10} },
				{ {3, 2},  {5, 2} },
			};

			LoopOccurrence actualOccLoop;
			actualOccLoop.type = TYPE_LOOP::FOR;

			findOccurrenceOfForLoop(range, &code, &actualOccLoop);

			int occAreEqual = memcmp(&expOccLoop, &actualOccLoop, sizeof(LoopOccurrence)) == 0;
			Assert::IsTrue(occAreEqual);
		}

		TEST_METHOD(There_are_nested_parentheses_inside_the_header)
		{
			Text code = {
				{
				"int main()",
				"{",
				"		for (int x = 0;(x > 0 || (x - 1) < rBorder); x++)",
				"		{",
				"			func();",
				"		}",
				"}"
				}, 7
			};

			Range range = { {2, 2}, {6, 2} };

			LoopOccurrence expOccLoop = {
				TYPE_LOOP::FOR,
				{ {2, 6}, {2, 50} },
				{ {3, 2},  {5, 2} },
			};

			LoopOccurrence actualOccLoop;
			actualOccLoop.type = TYPE_LOOP::FOR;

			findOccurrenceOfForLoop(range, &code, &actualOccLoop);

			int occAreEqual = memcmp(&expOccLoop, &actualOccLoop, sizeof(LoopOccurrence)) == 0;
			Assert::IsTrue(occAreEqual);
		}

		TEST_METHOD(There_are_comments_between_the_loop_head_and_body)
		{
			Text code = {
				{
				"int main()",
				"{",
				"		for (int i = 0;(i > 1  i < 10); i++) // i++)",
				"		// if (1) {}",
				"		// {}",
				"		",
				"		 {",
				"			func();",
				"		// }",
				"		}",
				"}"
				}, 11
			};

			Range range = { {2, 2}, {10, 0} };

			LoopOccurrence expOccLoop = {
				TYPE_LOOP::FOR,
				{ {2, 6}, {2, 37} },
				{ {6, 3},  {9, 2} },
			};

			LoopOccurrence actualOccLoop;
			actualOccLoop.type = TYPE_LOOP::FOR;

			findOccurrenceOfForLoop(range, &code, &actualOccLoop);

			int occAreEqual = memcmp(&expOccLoop, &actualOccLoop, sizeof(LoopOccurrence)) == 0;
			Assert::IsTrue(occAreEqual);
		}

		TEST_METHOD(There_are_loops_and_branches_inside_the_loop_body)
		// detecting nested loop
		{
			Text code = {
				{
				"int main()",
				"{",
				"		while (f(x))",
				"		",
				"		{",
				"			for (;func();)",
				"			{",
				"				while(1)",
				"				{",
				"					;",
				"				}",
				"			}",
				"		// }",
				"		}",
				"}"
				}, 15
			};

			Range range = { {5, 3}, {14, 0} };

			LoopOccurrence expOccLoop = {
				TYPE_LOOP::FOR,
				{ {5, 7}, {5, 16} },
				{ {6, 3},  {11, 3} },
			};

			LoopOccurrence actualOccLoop;
			actualOccLoop.type = TYPE_LOOP::FOR;

			findOccurrenceOfForLoop(range, &code, &actualOccLoop);

			int occAreEqual = memcmp(&expOccLoop, &actualOccLoop, sizeof(LoopOccurrence)) == 0;
			Assert::IsTrue(occAreEqual);
		}
	};

	TEST_CLASS(test_func_findDoWhileLoop) 
	{
		TEST_METHOD(Simple_detect_do_while_loop)
		{
			Text code = {
				{
				"int main()",
				"{",
				"		do",
				"		{",
				"			func();",
				"		}",
				"		while(1)",	
				"}"
				}, 8
			};

			Range range = { {2, 2}, {7, 0} };

			LoopOccurrence expOccLoop = {
				TYPE_LOOP::DO_WHILE,
				{ {6, 7}, {6, 9} },
				{ {3, 2},  {5, 2} },
			};

			LoopOccurrence actualOccLoop;
			actualOccLoop.type = TYPE_LOOP::DO_WHILE;

			findOccurrenceOfDoWhileLoop(range, &code, &actualOccLoop);

			int occAreEqual = memcmp(&expOccLoop, &actualOccLoop, sizeof(LoopOccurrence)) == 0;
			Assert::IsTrue(occAreEqual);
		}

		TEST_METHOD(There_are_nested_parentheses_inside_the_header) 
		{
			Text code = {
				{
				"int main()",
				"{",
				"		do",
				"		{",
				"			func();",
				"		}",
				"		while((x > 0 || (x - 1) < rBorder) || (x == -1) && (func(x)) == -1)",
				"}"
				}, 8
			};

			Range range = { {2, 2}, {7, 0} };

			LoopOccurrence expOccLoop = {
				TYPE_LOOP::DO_WHILE,
				{ {6, 7}, {6, 68} },
				{ {3, 2},  {5, 2} },
			};

			LoopOccurrence actualOccLoop;
			actualOccLoop.type = TYPE_LOOP::DO_WHILE;

			findOccurrenceOfDoWhileLoop(range, &code, &actualOccLoop);

			int occAreEqual = memcmp(&expOccLoop, &actualOccLoop, sizeof(LoopOccurrence)) == 0;
			Assert::IsTrue(occAreEqual);
		}

		TEST_METHOD(There_are_comments_between_the_loop_head_and_body)
		{
			Text code = {
				{
				"int main()",
				"{",
				"		do // {}",
				"		//{",
				"		// More comments to the comment god ",
				"		",
				"		{",
				"			func();",
				"		}",
				"		",
				"",
				"		// while(1) ",
				"		while((x > 0 || (x - 1) < rBorder) || (x == -1) && (func(x)) == -1)",
				"}"
				}, 14
			};

			Range range = { {2, 2}, {13, 0} };

			LoopOccurrence expOccLoop = {
				TYPE_LOOP::DO_WHILE,
				{ {12, 7}, {12, 68} },
				{ {6, 2}, {8, 2} },
			};

			LoopOccurrence actualOccLoop;
			actualOccLoop.type = TYPE_LOOP::DO_WHILE;

			findOccurrenceOfDoWhileLoop(range, &code, &actualOccLoop);

			int occAreEqual = memcmp(&expOccLoop, &actualOccLoop, sizeof(LoopOccurrence)) == 0;
			Assert::IsTrue(occAreEqual);
		}

		TEST_METHOD(There_are_loops_and_branches_inside_the_loop_body)
		{
			Text code = {
					{
					"int main()",
					"{",
					"		{",
					"			do",
					"			{",
					"				while(1)",
					"				{",
					"					{",
					"						if (func()) {cnt++};",
					"					}",
					"				}",
					"			",
					"			 }",
					"			while((x > 0 || (x - 1) < rBorder) || (x == -1) && (func(x)) == -1)",
					"		}",
					"}"
					}, 16
			};

			Range range = { {3, 3}, {15, 0} };

			LoopOccurrence expOccLoop = {
				TYPE_LOOP::DO_WHILE,
				{ {13, 8}, {13, 69} },
				{ {4, 3}, {12, 4} },
			};

			LoopOccurrence actualOccLoop;
			actualOccLoop.type = TYPE_LOOP::DO_WHILE;

			findOccurrenceOfDoWhileLoop(range, &code, &actualOccLoop);

			int occAreEqual = memcmp(&expOccLoop, &actualOccLoop, sizeof(LoopOccurrence)) == 0;
			Assert::IsTrue(occAreEqual);
		}

		TEST_METHOD(do_while_loop_inline) 
		{
			Text code = {
				{
				"int main()",
				"{",
				"		do{func();}while(1)",
				"}"
				}, 4
			};

			Range range = { {2, 2}, {3, 0} };

			LoopOccurrence expOccLoop = {
				TYPE_LOOP::DO_WHILE,
				{ {2, 18}, {2, 20} },
				{ {2, 4},  {2, 12} },
			};

			LoopOccurrence actualOccLoop;
			actualOccLoop.type = TYPE_LOOP::DO_WHILE;

			findOccurrenceOfDoWhileLoop(range, &code, &actualOccLoop);

			int occAreEqual = memcmp(&expOccLoop, &actualOccLoop, sizeof(LoopOccurrence)) == 0;
			Assert::IsTrue(occAreEqual);
		}
	};

	TEST_CLASS(test_func_findLoopsOccurrenceInCode) 
	{
		TEST_METHOD(Detecting_the_occurrence_of_one_while_loop)
		{
			Text code = {
				{
				"int main()",
				"{",
				"		while (1)",
				"		{",
				"			func();",
				"		}",
				"}"
				}, 7
			};

			Range range = { {2, 2}, {6, 2} };

			LoopOccurrence expOccLoop1 = {
				TYPE_LOOP::WHILE,
				{ {2, 8}, {2, 10} },
				{ {3, 2},  {5, 2} },
			};

			const int expCountOfOccurrences = 1;
			LoopOccurrence expOccurrences[expCountOfOccurrences] = {
				expOccLoop1
			};

			LoopOccurrence actualOccurrences[MAX_COUNT_LOOP];;
			int actualCountOfOccurrences = findLoopsOccurrenceInCode(range, &code, actualOccurrences);
			
			int sizeAreEqual = expCountOfOccurrences == actualCountOfOccurrences;
			int occAreEqual = memcmp(expOccurrences, actualOccurrences, sizeof(LoopOccurrence)* expCountOfOccurrences) == 0;
			Assert::IsTrue(occAreEqual);
		}

		TEST_METHOD(No_loops_in_code)
		{
			Text code = {
				{
				"int main()",
				"{",
				"		",
				"		{",
				"		}",
				"		",
				"}"
				}, 7
			};

			Range range = { {2, 2}, {6, 2} };

			const int expCountOfOccurrences = 0;
			LoopOccurrence expOccurrences[1] = {};

			LoopOccurrence actualOccurrences[MAX_COUNT_LOOP];;
			int actualCountOfOccurrences = findLoopsOccurrenceInCode(range, &code, actualOccurrences);

			int sizeAreEqual = expCountOfOccurrences == actualCountOfOccurrences;
			int occAreEqual = memcmp(expOccurrences, actualOccurrences, sizeof(LoopOccurrence) * expCountOfOccurrences) == 0;
			Assert::IsTrue(occAreEqual);
		}

		TEST_METHOD(There_are_several_non_nested_different_loops)
		{
			Text code = {
				{
				"int main()",
				"{",
				"		while (1)",
				"		{",
				"			func();",
				"		}",
				"		for(;;)",
				"		{",
				"		}",
				"		do",
				"		{",
				"		",
				"		}",
				"		while(func())",
				"}"
				}, 15
			};

			Range range = { {2, 2}, {14, 0} };

			LoopOccurrence expOccLoop1 = {
				TYPE_LOOP::WHILE,
				{ {2, 8}, {2, 10} },
				{ {3, 2},  {5, 2} },
			};

			LoopOccurrence expOccLoop2 = {
				TYPE_LOOP::FOR,
				{ {6, 5}, {6, 8} },
				{ {7, 2}, {8,2} }
			};

			LoopOccurrence expOccLoop3 = {
				TYPE_LOOP::DO_WHILE,
				{ {13, 7}, {13, 14} },
				{ {10, 2}, {12,2} }
			};

			const int expCountOfOccurrences = 3;
			LoopOccurrence expOccurrences[expCountOfOccurrences] = {
				expOccLoop1,
				expOccLoop2,
				expOccLoop3
			};

			LoopOccurrence actualOccurrences[MAX_COUNT_LOOP];;
			int actualCountOfOccurrences = findLoopsOccurrenceInCode(range, &code, actualOccurrences);

			int sizeAreEqual = expCountOfOccurrences == actualCountOfOccurrences;
			int occAreEqual = memcmp(expOccurrences, actualOccurrences, sizeof(LoopOccurrence) * expCountOfOccurrences) == 0;
			Assert::IsTrue(occAreEqual);
		}

		TEST_METHOD(Do_while_loop_located_before_while) 
		{
			Text code = {
				{
				"int main()",
				"{",
				"		do",
				"		{",
				"			func();",
				"		}",
				"		while(1)",
				"		while(x>0)",
				"		{",
				"		",
				"		}",
				"		",
				"		",
				"",
				"}"
				}, 15
			};

			Range range = { {2, 2}, {14, 0} };

			LoopOccurrence expOccLoop1 = {
				TYPE_LOOP::DO_WHILE,
				{ {6, 7}, {6, 9} },
				{ {3, 2},  {5, 2} },
			};

			LoopOccurrence expOccLoop2 = {
				TYPE_LOOP::WHILE,
				{ {7, 7}, {7, 11} },
				{ {8, 2}, {10,2} }
			};

			const int expCountOfOccurrences = 2;
			LoopOccurrence expOccurrences[expCountOfOccurrences] = {
				expOccLoop1,
				expOccLoop2
			};

			LoopOccurrence actualOccurrences[MAX_COUNT_LOOP];;
			int actualCountOfOccurrences = findLoopsOccurrenceInCode(range, &code, actualOccurrences);

			int sizeAreEqual = expCountOfOccurrences == actualCountOfOccurrences;
			int occAreEqual = memcmp(expOccurrences, actualOccurrences, sizeof(LoopOccurrence) * expCountOfOccurrences) == 0;
			Assert::IsTrue(occAreEqual);
		}

		TEST_METHOD(There_are_nested_loops) 
		{
			Text code = {
					{
					"int main()",
					"{",
					"		{",
					"			do",
					"			{",
					"				do",
					"				{",
					"				}",
					"				while(func())",
					"				while(1)",
					"				{",
					"					{",
					"						if (func()) {cnt++};",
					"					}",
					"				}",
					"			",
					"			 }",
					"			while((x > 0 || (x - 1) < rBorder) || (x == -1) && (func(x)) == -1)",
					"		}",
					"}"
					}, 20
			};

			Range range = { {0, 0}, {20, 0} };

			LoopOccurrence expOccLoop1 = {
				TYPE_LOOP::DO_WHILE,
				{ {17, 8}, {17, 69} },
				{ {4, 3}, {16, 4} },
			};

			LoopOccurrence expOccLoop2 =
			{
				TYPE_LOOP::DO_WHILE,
				{ {8, 9}, {8, 16} },
				{ {6, 4}, {7, 4} }
			};

			LoopOccurrence expOccLoop3 =
			{
				TYPE_LOOP::WHILE,
				{ {9, 9}, {9, 11} },
				{ {10, 4}, {14, 4} }
			};

			const int expCountOfOccurrences = 3;
			LoopOccurrence expOccurrences[expCountOfOccurrences] = {
				expOccLoop1,
				expOccLoop2,
				expOccLoop3
			};

			LoopOccurrence actualOccurrences[MAX_COUNT_LOOP];;
			int actualCountOfOccurrences = findLoopsOccurrenceInCode(range, &code, actualOccurrences);

			int sizeAreEqual = expCountOfOccurrences == actualCountOfOccurrences;
			int occAreEqual = memcmp(expOccurrences, actualOccurrences, sizeof(LoopOccurrence) * expCountOfOccurrences) == 0;
			Assert::IsTrue(occAreEqual);
		}
	};
}