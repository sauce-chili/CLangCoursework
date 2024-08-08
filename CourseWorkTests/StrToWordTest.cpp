#include "pch.h"
#include "CppUnitTest.h"
#include "string.h"
#include "../CourseWork_Smirnov/Common.h"
#include "../CourseWork_Smirnov/StrToWord.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StrToWordTest
{
	TEST_CLASS(test_func_strToWords)
	{
		TEST_METHOD(Empty_string)
		{
			char str[] = "";

			char* startPrt = str;
			char* endPtr = &str[strlen(str)];

			int expCountOfWord = 0;
			Word expWords[MAX_COUNT_VAR_IN_STRING];

			Word actualWords[MAX_COUNT_VAR_IN_STRING];
			int actualOfCountWords = strToWords(startPrt, endPtr, actualWords);

			int wordsArrayEquals = memcmp(actualWords, expWords, sizeof(Word) * expCountOfWord) == 0;
			Assert::IsTrue(
				actualOfCountWords == expCountOfWord &&
				wordsArrayEquals
			);
		}

		TEST_METHOD(Correct_detection_of_a_word_at_the_end_of_a_line)
		{
			char str[] = "					a";

			char* startPrt = str;
			char* endPtr = &str[strlen(str)];

			int expCountOfWord = 1;
			Word expWords[MAX_COUNT_VAR_IN_STRING] = {
				{&str[strlen(str) - 1], &str[strlen(str) - 1]},
			};

			Word actualWords[MAX_COUNT_VAR_IN_STRING];
			int actualOfCountWords = strToWords(startPrt, endPtr, actualWords);

			int wordsArrayEquals = memcmp(actualWords, expWords, sizeof(Word) * expCountOfWord) == 0;
			Assert::IsTrue(
				actualOfCountWords == expCountOfWord &&
				wordsArrayEquals
			);
		}

		TEST_METHOD(Correct_definition_of_a_word_located_at_the_end_of_the_search_range) 
		{
			char str[] = "		a|	";

			char* startPrt = str;
			char* endPtr = &str[2]; // index "a"

			int expCountOfWord = 1;
			Word expWords[MAX_COUNT_VAR_IN_STRING] = {
				{&str[2], &str[2]},
			};

			Word actualWords[MAX_COUNT_VAR_IN_STRING];
			int actualOfCountWords = strToWords(startPrt, endPtr, actualWords);

			int wordsArrayEquals = memcmp(actualWords, expWords, sizeof(Word) * expCountOfWord) == 0;
			Assert::IsTrue(
				actualOfCountWords == expCountOfWord &&
				wordsArrayEquals
			);
		}

		TEST_METHOD(Correct_detection_of_a_word_at_the_start_of_a_line)
		{
			char str[] = "a					";

			char* startPrt = str;
			char* endPtr = &str[strlen(str)];

			int expCountOfWord = 1;
			Word expWords[MAX_COUNT_VAR_IN_STRING] = {
				{&str[0], &str[0]},
			};

			Word actualWords[MAX_COUNT_VAR_IN_STRING];
			int actualOfCountWords = strToWords(startPrt, endPtr, actualWords);

			int wordsArrayEquals = memcmp(actualWords, expWords, sizeof(Word) * expCountOfWord) == 0;
			Assert::IsTrue(
				actualOfCountWords == expCountOfWord &&
				wordsArrayEquals
			);
		}

		TEST_METHOD(One_single_letter_word)
		{
			char str[] = "a";

			char* startPrt = str;
			char* endPtr = &str[strlen(str)];

			int expCountOfWord = 1;
			Word expWords[MAX_COUNT_VAR_IN_STRING] = {
				{&str[0], &str[0]}
			};

			Word actualWords[MAX_COUNT_VAR_IN_STRING];
			int actualOfCountWords = strToWords(startPrt, endPtr, actualWords);

			int wordsArrayEquals = memcmp(actualWords, expWords, sizeof(Word) * expCountOfWord) == 0;
			Assert::IsTrue(
				actualOfCountWords == expCountOfWord &&
				wordsArrayEquals
			);
		}

		TEST_METHOD(Two_word)
		{
			char str[] = "int a";

			char* startPrt = str;
			char* endPtr = &str[strlen(str)];

			int expCountOfWord = 2;
			Word expWords[MAX_COUNT_VAR_IN_STRING] = {
				{&str[0], &str[2]},
				{&str[4], &str[4]}
			};

			Word actualWords[MAX_COUNT_VAR_IN_STRING];
			int actualOfCountWords = strToWords(startPrt, endPtr, actualWords);

			int wordsArrayEquals = memcmp(actualWords, expWords, sizeof(Word) * expCountOfWord) == 0;
			Assert::IsTrue(
				actualOfCountWords == expCountOfWord &&
				wordsArrayEquals
			);
		}

		TEST_METHOD(Several_words)
		{
			char str[] = "unsigned long long not_Bad,a,_b";

			char* startPrt = str;
			char* endPtr = &str[strlen(str)];

			int expCountOfWord = 6;
			Word expWords[MAX_COUNT_VAR_IN_STRING] = {
				{&str[0],  &str[7]},
				{&str[9], &str[12]},
				{&str[14], &str[17]},
				{&str[19], &str[25]},
				{&str[27], &str[27]},
				{&str[29], &str[30]}
			};

			Word actualWords[MAX_COUNT_VAR_IN_STRING];
			int actualOfCountWords = strToWords(startPrt, endPtr, actualWords);

			int wordsArrayEquals = memcmp(actualWords, expWords, sizeof(Word) * expCountOfWord) == 0;
			Assert::IsTrue(
				actualOfCountWords == expCountOfWord &&
				wordsArrayEquals
			);
		}

		TEST_METHOD(The_string_is_the_for_loop_header)
		{
			char str[] = "	for(int i = 0; i < 5; i++)";

			char* startPrt = str;
			char* endPtr = &str[strlen(str)];

			int expCountOfWord = 5;
			Word expWords[MAX_COUNT_VAR_IN_STRING] = {
				{&str[1],  &str[3]},
				{&str[5],  &str[7]},
				{&str[9],  &str[9]},
				{&str[16], &str[16]},
				{&str[23], &str[23]}
			};

			Word actualWords[MAX_COUNT_VAR_IN_STRING];
			int actualOfCountWords = strToWords(startPrt, endPtr, actualWords);

			int wordsArrayEquals = memcmp(actualWords, expWords, sizeof(Word) * expCountOfWord) == 0;
			Assert::IsTrue(
				actualOfCountWords == expCountOfWord &&
				wordsArrayEquals
			);
		}

		TEST_METHOD(Ñonverting_only_a_certain_part_of_a_string_to_words) 
		{
			char str[] = "	for(int i = 0; i < 5; i++)";

			char* startPrt = &str[14];
			char* endPtr = &str[strlen(str)];

			int expCountOfWord = 2;
			Word expWords[MAX_COUNT_VAR_IN_STRING] = {
				{&str[16], &str[16]},
				{&str[23], &str[23]}
			};

			Word actualWords[MAX_COUNT_VAR_IN_STRING];
			int actualOfCountWords = strToWords(startPrt, endPtr, actualWords);

			int wordsArrayEquals = memcmp(actualWords, expWords, sizeof(Word) * expCountOfWord) == 0;
			Assert::IsTrue(
				actualOfCountWords == expCountOfWord &&
				wordsArrayEquals
			);
		}

		TEST_METHOD(There_are_numbers_that_look_like_words_1)
		{
			char str[] = "int a = 1e-3 + 4E5 + 0x3BC2FA;";

			char* startPrt = str;
			char* endPtr = &str[strlen(str)];

			int expCountOfWord = 2;
			Word expWords[MAX_COUNT_VAR_IN_STRING] = {
				{&str[0], &str[2]},
				{&str[4], &str[4]}
			};

			Word actualWords[MAX_COUNT_VAR_IN_STRING];
			int actualOfCountWords = strToWords(startPrt, endPtr, actualWords);

			int wordsArrayEquals = memcmp(actualWords, expWords, sizeof(Word) * expCountOfWord) == 0;
			Assert::IsTrue(
				actualOfCountWords == expCountOfWord &&
				wordsArrayEquals
			);
		}

		TEST_METHOD(There_are_numbers_that_look_like_words_2)
		{
			char str[] = "long a = 4LL;";

			char* startPrt = str;
			char* endPtr = &str[strlen(str)];

			int expCountOfWord = 2;
			Word expWords[MAX_COUNT_VAR_IN_STRING] = {
				{&str[0], &str[3]},
				{&str[5], &str[5]}
			};

			Word actualWords[MAX_COUNT_VAR_IN_STRING];
			int actualOfCountWords = strToWords(startPrt, endPtr, actualWords);

			int wordsArrayEquals = memcmp(actualWords, expWords, sizeof(Word) * expCountOfWord) == 0;
			Assert::IsTrue(
				actualOfCountWords == expCountOfWord &&
				wordsArrayEquals
			);
		}

		TEST_METHOD(There_are_numbers_that_look_like_words_3)
		{
			char str[] = "float a = 2.5f;";

			char* startPrt = str;
			char* endPtr = &str[strlen(str)];

			int expCountOfWord = 2;
			Word expWords[MAX_COUNT_VAR_IN_STRING] = {
				{&str[0], &str[4]},
				{&str[6], &str[6]}
			};

			Word actualWords[MAX_COUNT_VAR_IN_STRING];
			int actualOfCountWords = strToWords(startPrt, endPtr, actualWords);

			int wordsArrayEquals = memcmp(actualWords, expWords, sizeof(Word) * expCountOfWord) == 0;
			Assert::IsTrue(
				actualOfCountWords == expCountOfWord &&
				wordsArrayEquals
			);
		}

		TEST_METHOD(Words_and_brackets)
		{
			char str[] = "(((F)))((x));";

			char* startPrt = str;
			char* endPtr = &str[strlen(str)];

			int expCountOfWord = 2;
			Word expWords[MAX_COUNT_VAR_IN_STRING] = {
				{&str[3], &str[3]},
				{&str[9], &str[9]}
			};

			Word actualWords[MAX_COUNT_VAR_IN_STRING];
			int actualOfCountWords = strToWords(startPrt, endPtr, actualWords);

			int wordsArrayEquals = memcmp(actualWords, expWords, sizeof(Word) * expCountOfWord) == 0;
			Assert::IsTrue(
				actualOfCountWords == expCountOfWord &&
				wordsArrayEquals
			);
		}
	};

	TEST_CLASS(test_func_getWordLength) 
	{
		TEST_METHOD(Empty_word) 
		{
			Word word;

			int expLength = 0;
			int actualLength = getWordLength(&word);

			Assert::AreEqual(expLength, actualLength);
		}

		TEST_METHOD(Length_of_single_letter_word_in_end)
		{
			char str[] = "		a";

			Word word = {&str[3], &str[3]};

			int expLength = 1;
			int actualLength = getWordLength(&word);

			Assert::AreEqual(expLength, actualLength);
		}

		TEST_METHOD(Length_of_single_letter_word_in_start)
		{
			char str[] = "a ";

			Word word = { &str[0], &str[0] };

			int expLength = 1;
			int actualLength = getWordLength(&word);

			Assert::AreEqual(expLength, actualLength);
		}

		TEST_METHOD(Ñorrect_length_of_determination_of_multi_letter_word) 
		{
			char str[] = "	unsigned ";

			Word word = { &str[1], &str[8] };

			int expLength = 8;
			int actualLength = getWordLength(&word);

			Assert::AreEqual(expLength, actualLength);
		}
	};

	TEST_CLASS(test_func_wordToStr)
	{

		TEST_METHOD(Empty_word)
		{

			Word word;

			char expectedStrWord[MAX_CHAR_IN_STRING];
			int expectedLen = 0;

			char actualStrWord[MAX_CHAR_IN_STRING];
			int actualLen = wordToStr(&word, actualStrWord);

			int strWordAreEquals = strcmp(actualStrWord, expectedStrWord) == 0;
			Assert::IsTrue(expectedLen == actualLen &&
				strWordAreEquals
			);
		}

		TEST_METHOD(Multi_letter_word_in_start_of_string) 
		{
			char str[] = "unsigned  ";

			Word word = { &str[0], &str[7] };

			char expectedStrWord[] = "unsigned";
			int expectedLen = 8;

			char actualStrWord[MAX_CHAR_IN_STRING];
			int actualLen = wordToStr(&word, actualStrWord);

			int strWordAreEquals = strcmp(actualStrWord, expectedStrWord) == 0;
			Assert::IsTrue(expectedLen == actualLen &&
				strWordAreEquals
			);
		}
		TEST_METHOD(Multi_letter_word_in_end_of_string)
		{
			char str[] = "	unsigned ";

			Word word = { &str[1], &str[8] };

			char expectedStrWord[] = "unsigned";
			int expectedLen = 8;

			char actualStrWord[MAX_CHAR_IN_STRING];
			int actualLen = wordToStr(&word, actualStrWord);

			int strWordAreEquals = strcmp(actualStrWord, expectedStrWord) == 0;
			Assert::IsTrue(expectedLen == actualLen &&
				strWordAreEquals
			);
		}
		TEST_METHOD(Single_letter_word_in_start_of_string) 
		{
			char str[] = "F  ";

			Word word = { &str[0], &str[0] };

			char expectedStrWord[] = "F";
			int expectedLen = 1;

			char actualStrWord[MAX_CHAR_IN_STRING];
			int actualLen = wordToStr(&word, actualStrWord);

			int strWordAreEquals = strcmp(actualStrWord, expectedStrWord) == 0;
			Assert::IsTrue(expectedLen == actualLen &&
				strWordAreEquals
			);
		}
		TEST_METHOD(Single_letter_word_in_end_of_string) 
		{
			char str[] = "		F";

			int len = strlen(str);

			Word word = { &str[len-1], &str[len-1] };

			char expectedStrWord[] = "F";
			int expectedLen = 1;

			char actualStrWord[MAX_CHAR_IN_STRING];
			int actualLen = wordToStr(&word, actualStrWord);

			int strWordAreEquals = strcmp(actualStrWord, expectedStrWord) == 0;
			Assert::IsTrue(expectedLen == actualLen &&
				strWordAreEquals
			);
		}

		TEST_METHOD(Single_letter_word) 
		{
			char str[] = "(((F)))((x));";

			Word word = { &str[3], &str[3] };
			
			char expectedStrWord[] = "F";
			int expectedLen = 1;

			char actualStrWord[MAX_CHAR_IN_STRING];
			int actualLen = wordToStr(&word, actualStrWord);

			int strWordAreEquals = strcmp(actualStrWord, expectedStrWord) == 0;
			Assert::IsTrue( expectedLen == actualLen &&
							strWordAreEquals
			);
		}

		TEST_METHOD(Multi_letter_word_middle_a_string)
		{
			char str[] = "	unsigned  ";

			Word word = { &str[1], &str[8] };

			char expectedStrWord[] = "unsigned";
			int expectedLen = 8;

			char actualStrWord[MAX_CHAR_IN_STRING];
			int actualLen = wordToStr(&word, actualStrWord);

			int strWordAreEquals = strcmp(actualStrWord, expectedStrWord) == 0;
			Assert::IsTrue(expectedLen == actualLen &&
				strWordAreEquals
			);
		}
	};
}