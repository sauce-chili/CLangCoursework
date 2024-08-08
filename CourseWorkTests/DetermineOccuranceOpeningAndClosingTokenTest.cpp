#include "pch.h"
#include "CppUnitTest.h"
#include "../CourseWork_Smirnov/Common.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommonTests
{
	TEST_CLASS(test_func_determineOccuranceOfOpeningAndClosingSubstring) 
	{
		TEST_METHOD(Searching_the_start_and_end_of_the_loop_header_in_string) 
		{
			Text code = {
				{
				"int main()",
				"{",
				"	for(int q = 0; q < 5; q++);",
				"}"
				}, 4
			};

			const char openingSubstr[] = "(";
			const char closingSubstr[] = ")";
			Range searchRange = { {2, 3}, {2, strlen(code.text[2]) - 1}};

			Occurrence expOpeningOcc = { 2, 4 };
			Occurrence expClosingOcc = { 2, 26 };
			int expStatus = 0;

			Occurrence actualOpeningOcc;
			Occurrence actualClosingOcc;

			int actualStatus = determineOccuranceOfOpeningAndClosingToken(
				openingSubstr,
				closingSubstr,
				searchRange,
				&code,
				&actualOpeningOcc,
				&actualClosingOcc
			);

			int statusCorrect = expStatus == actualStatus;
			int occurrenceEqual =
				memcmp(&expOpeningOcc, &actualOpeningOcc, sizeof(Occurrence)) == 0 &&
				memcmp(&expClosingOcc, &actualClosingOcc, sizeof(Occurrence)) == 0;

			Assert::IsTrue(
				statusCorrect && occurrenceEqual
			);
		}

		TEST_METHOD(The_opening_and_closing_token_consists_of_several_characters)
		{
			Text code = {
				{
				"int main()",
				"{",
				"	for((int ((q = 0)); ((q < 5)); q++));",
				"}"
				}, 4
			};

			const char openingSubstr[] = "((";
			const char closingSubstr[] = "))";
			Range searchRange = { {2, 3}, {2, strlen(code.text[2]) - 1} };

			Occurrence expOpeningOcc = { 2, 4 };
			Occurrence expClosingOcc = { 2, 35 };
			int expStatus = 0;

			Occurrence actualOpeningOcc;
			Occurrence actualClosingOcc;

			int actualStatus = determineOccuranceOfOpeningAndClosingToken(
				openingSubstr,
				closingSubstr,
				searchRange,
				&code,
				&actualOpeningOcc,
				&actualClosingOcc
			);

			int statusCorrect = expStatus == actualStatus;
			int occurrenceEqual =
				memcmp(&expOpeningOcc, &actualOpeningOcc, sizeof(Occurrence)) == 0 &&
				memcmp(&expClosingOcc, &actualClosingOcc, sizeof(Occurrence)) == 0;

			Assert::IsTrue(
				statusCorrect && occurrenceEqual
			);
		}

		TEST_METHOD(Multiple_nested_opening_and_closing_token_within_a_given_string_range) 
		{
			Text code = {
				{
				"int main()",
				"{",
				"	for(int q = ((x%2 + 1)/2); q < 5; q++);",
				"}"
				}, 4
			};

			const char openingSubstr[] = "(";
			const char closingSubstr[] = ")";
			Range searchRange = { {2, 3}, {2, 39} };

			Occurrence expOpeningOcc = { 2, 4 };
			Occurrence expClosingOcc = { 2, 38 };
			int expStatus = 0;

			Occurrence actualOpeningOcc;
			Occurrence actualClosingOcc;

			int actualStatus = determineOccuranceOfOpeningAndClosingToken(
				openingSubstr,
				closingSubstr,
				searchRange,
				&code,
				&actualOpeningOcc,
				&actualClosingOcc
			);

			int statusCorrect = expStatus == actualStatus;
			int occurrenceEqual =
				memcmp(&expOpeningOcc, &actualOpeningOcc, sizeof(Occurrence)) == 0 &&
				memcmp(&expClosingOcc, &actualClosingOcc, sizeof(Occurrence)) == 0;

			Assert::IsTrue(
				statusCorrect && occurrenceEqual
			);
		}

		TEST_METHOD(Occurrences_of_the_opening_and_closing_token_is_located_on_several_strings) 
		{
			Text code = {
				{
				"int main()",
				"{",
				"	for(int q = ((x%2 + 1)/2); q < 5; q++)",
				"		{",
				"		func();",
				"	}",
				"}"
				}, 7
			};

			const char openingSubstr[] = "{";
			const char closingSubstr[] = "}";
			Range searchRange = { {2, 3}, {6, strlen(code.text[2])} };

			Occurrence expOpeningOcc = { 3, 2 };
			Occurrence expClosingOcc = { 5, 1 };
			int expStatus = 0;

			Occurrence actualOpeningOcc;
			Occurrence actualClosingOcc;

			int actualStatus = determineOccuranceOfOpeningAndClosingToken(
				openingSubstr,
				closingSubstr,
				searchRange,
				&code,
				&actualOpeningOcc,
				&actualClosingOcc
			);

			int statusCorrect = expStatus == actualStatus;
			int occurrenceEqual =
				memcmp(&expOpeningOcc, &actualOpeningOcc, sizeof(Occurrence)) == 0 &&
				memcmp(&expClosingOcc, &actualClosingOcc, sizeof(Occurrence)) == 0;

			Assert::IsTrue(
				statusCorrect && occurrenceEqual
			);
		}

		TEST_METHOD(There_are_several_nested_opening_and_closing_tokens_in_the_range) 
		{
			Text code = {
				{
				"int main()",
				"{",
				"	for(int q = ((x%2 + 1)/2); q < 5; q++)",
				"		{",
				"		{",
				"		}",
				"		while (1)",
				"		{",
				"			func();",
				"		}",
				"	}",
				"}"
				}, 12
			};

			const char openingSubstr[] = "{";
			const char closingSubstr[] = "}";
			Range searchRange = { {2, 3}, {10, strlen(code.text[10])} };

			Occurrence expOpeningOcc = { 3, 2 };
			Occurrence expClosingOcc = { 10, 1 };
			int expStatus = 0;

			Occurrence actualOpeningOcc;
			Occurrence actualClosingOcc;

			int actualStatus = determineOccuranceOfOpeningAndClosingToken(
				openingSubstr,
				closingSubstr,
				searchRange,
				&code,
				&actualOpeningOcc,
				&actualClosingOcc
			);

			int statusCorrect = expStatus == actualStatus;
			int occurrenceEqual =
				memcmp(&expOpeningOcc, &actualOpeningOcc, sizeof(Occurrence)) == 0 &&
				memcmp(&expClosingOcc, &actualClosingOcc, sizeof(Occurrence)) == 0;

			Assert::IsTrue(
				statusCorrect && occurrenceEqual
			);
		}

		TEST_METHOD(The_search_range_contains_comments_with_opening_and_closing_tokens_1)
		{
			Text code = {
				{
				"int main()",
				"{",
				"	for(int q = ((x%2 + 1)/2); q < 5; q++); // ()",
				"}"
				}, 4
			};

			const char openingSubstr[] = "(";
			const char closingSubstr[] = ")";
			Range searchRange = { {2, 3}, {2, strlen(code.text[2])} };

			Occurrence expOpeningOcc = { 2, 4 };
			Occurrence expClosingOcc = { 2, 38 };
			int expStatus = 0;

			Occurrence actualOpeningOcc;
			Occurrence actualClosingOcc;

			int actualStatus = determineOccuranceOfOpeningAndClosingToken(
				openingSubstr,
				closingSubstr,
				searchRange,
				&code,
				&actualOpeningOcc,
				&actualClosingOcc
			);

			int statusCorrect = expStatus == actualStatus;
			int occurrenceEqual =
				memcmp(&expOpeningOcc, &actualOpeningOcc, sizeof(Occurrence)) == 0 &&
				memcmp(&expClosingOcc, &actualClosingOcc, sizeof(Occurrence)) == 0;

			Assert::IsTrue(
				statusCorrect && occurrenceEqual
			);
		}
		
		TEST_METHOD(The_search_range_contains_comments_with_opening_and_closing_tokens_2)
		{
			Text code = {
				{
				"int main()",
				"{",
				"	for(int q = ((x%2 + 1)/2); q < 5; q++)",
				"		{",
				"		{",
				"		}",
				"		//while (1)",
				"		//{",
				"		//	func();",
				"		//}",
				"	}",
				"}"
				}, 12
			};

			const char openingSubstr[] = "{";
			const char closingSubstr[] = "}";
			Range searchRange = { {2, 3}, {11, strlen(code.text[11])} };

			Occurrence expOpeningOcc = { 3, 2 };
			Occurrence expClosingOcc = { 10, 1 };
			int expStatus = 0;

			Occurrence actualOpeningOcc;
			Occurrence actualClosingOcc;

			int actualStatus = determineOccuranceOfOpeningAndClosingToken(
				openingSubstr,
				closingSubstr,
				searchRange,
				&code,
				&actualOpeningOcc,
				&actualClosingOcc
			);

			int statusCorrect = expStatus == actualStatus;
			int occurrenceEqual =
				memcmp(&expOpeningOcc, &actualOpeningOcc, sizeof(Occurrence)) == 0 &&
				memcmp(&expClosingOcc, &actualClosingOcc, sizeof(Occurrence)) == 0;

			Assert::IsTrue(
				statusCorrect && occurrenceEqual
			);
		}

		TEST_METHOD(Incorrect_sequence_of_opening_and_closing_tokens)
		// all closing token located before opening
		{
			Text code = {
				{
				"int main()",
				"{",
				"	}",
				"		}",
				"		}",
				"		{",
				"		//while (1)",
				"		//{",
				"		//	func();",
				"		//}",
				"	{",
				"{"
				}, 12
			};
			
			const char openingSubstr[] = "{";
			const char closingSubstr[] = "}";
			Range searchRange = { {2, 3}, {11, strlen(code.text[11])} };

			Occurrence expOpeningOcc = { -1, -1 };
			Occurrence expClosingOcc = { -1, -1 };
			int expStatus = -1;

			Occurrence actualOpeningOcc;
			Occurrence actualClosingOcc;
			int actualStatus = determineOccuranceOfOpeningAndClosingToken(
				openingSubstr,
				closingSubstr,
				searchRange,
				&code,
				&actualOpeningOcc,
				&actualClosingOcc
			);

			if (expStatus == ERROR_RESULT && actualStatus == ERROR_RESULT) 
			{
				Assert::IsTrue(true);
				return;
			}

			int statusCorrect = expStatus == actualStatus;
			int occurrenceEqual =
				memcmp(&expOpeningOcc, &actualOpeningOcc, sizeof(Occurrence)) == 0 &&
				memcmp(&expClosingOcc, &actualClosingOcc, sizeof(Occurrence)) == 0;

			Assert::IsTrue(
				statusCorrect && occurrenceEqual
			);
		}

		TEST_METHOD(Opening_and_closing_tokens_are_equal)
		{
			Text code = {
				{
				"int main()",
				"{",
				"	for(int q = ((x%2 + 1)/2); q < 5; q++)",
				"		!",
				"		!",
				"		!",
				"		//while (1)",
				"		//{",
				"		//	func();",
				"		//}",
				"	!",
				"!"
				}, 12
			};

			const char openingSubstr[] = "!";
			const char closingSubstr[] = "!";
			Range searchRange = { {2, 3}, {11, strlen(code.text[11])} };

			Occurrence expOpeningOcc = { -1, -1 };
			Occurrence expClosingOcc = { -1, -1 };
			int expStatus = ERROR_RESULT;

			Occurrence actualOpeningOcc;
			Occurrence actualClosingOcc;

			int actualStatus = determineOccuranceOfOpeningAndClosingToken(
				openingSubstr,
				closingSubstr,
				searchRange,
				&code,
				&actualOpeningOcc,
				&actualClosingOcc
			);

			if (expStatus == ERROR_RESULT && actualStatus == ERROR_RESULT)
			{
				Assert::IsTrue(true);
				return;
			}

			int statusCorrect = expStatus == actualStatus;
			int occurrenceEqual =
				memcmp(&expOpeningOcc, &actualOpeningOcc, sizeof(Occurrence)) == 0 &&
				memcmp(&expClosingOcc, &actualClosingOcc, sizeof(Occurrence)) == 0;

			Assert::IsTrue(
				statusCorrect && occurrenceEqual
			);
		}
	};
}