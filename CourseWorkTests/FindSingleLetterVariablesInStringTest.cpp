#include "pch.h"
#include "CppUnitTest.h"
#include "../CourseWork_Smirnov/FindVariables.h"
#include "../CourseWork_Smirnov/StrToWord.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FindSingleLetterVariablesTest
{
	TEST_CLASS(test_func_findSingleLetterVariablesInString)
	{
		TEST_METHOD(find_one_single_letter_var_in_string)
		{
			char str[] = "int a;";

			int expCountVar = 1;
			Word expVars[] = {
				{&str[4], &str[4]}
			};

			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}

		TEST_METHOD(find_one_single_letter_var_with_init_in_string)
		{
			char str[] = "int a=1;";

			int expCountVar = 1;
			Word expVars[] = {
				{&str[4], &str[4]}
			};

			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}

		TEST_METHOD(find_multiple_single_letter_var_in_string)
		{
			char str[] = "int a,b,c";

			int expCountVar = 3;
			Word expVars[] = { 
				{&str[4], &str[4]},
				{&str[6], &str[6]},
				{&str[8], &str[8]}
			};
			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}

		TEST_METHOD(find_one_sigle_letter_var_if_exist_multi_letter_vars)
		{
			char str[] = "int dog,b,cat";

			int expCountVar = 1;
			Word expVars[] = {
				{&str[8], &str[8]}
			};
			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}

		TEST_METHOD(find_multiple_sigle_letter_var_if_exist_multiple_letter_vars)
		{
			char str[] = "int dog,b,cat,c";

			int expCountVar = 2;
			Word expVars[] = {
				{&str[8], &str[8]},
				{&str[14], &str[14]}
			};

			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}

		TEST_METHOD(find_sigle_letter_var_in_if_operator)
		{
			char str[] = "if(a==-1)";

			int expCountVar = 1;
			Word expVars[] = {
				{&str[3], &str[3]}
			};

			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}

		TEST_METHOD(searching_for_single_letter_vars_in_the_if_operator_in_the_presence_of_a_complex_condition)
		{
			char str[] = "if(a==q&&q>leftLimit)";

			int expCountVar = 3;
			Word expVars[] = {
				{&str[3], &str[3]},
				{&str[6], &str[6]},
				{&str[9], &str[9]}
			};

			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}

		TEST_METHOD(find_single_letter_var_in_header_of_for_loop)
		{
			char str[] = "for(int q = 0; q < 10; q++)";

			int expCountVar = 3;
			Word expVars[] = {
				{&str[8], &str[8]},
				{&str[15], &str[15]},
				{&str[23], &str[23]}
			};

			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}

		TEST_METHOD(There_are_spaces_and_tabs_between_the_loop_name_and_its_description) 
		{
			char str[] = "for		   (int q = 0; q < 10; q++)";

			int expCountVar = 3;
			Word expVars[] = {
				{&str[13], &str[13]},
				{&str[20], &str[20]},
				{&str[28], &str[28]}
			};

			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}

		TEST_METHOD(find_single_letter_var_in_header_of_while_loop)
		{
			char str[] = "while(q > 0 && rightLimit != q)";

			int expCountVar = 2;
			Word expVars[] = {
				{&str[6], &str[6]},
				{&str[29], &str[29]},
			};

			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}

		TEST_METHOD(find_single_letter_var_in_switch)
		{
			char str[] = "		switch(q)";

			int expCountVar = 1;
			Word expVars[] = {
				{&str[9], &str[9]}
			};

			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}

		TEST_METHOD(search_for_a_single_letter_variable_inside_parameters_of_function)
		{
			char str[] = "	someFunc(a, (q+a));";

			int expCountVar = 3;
			Word expVars[] = {
				{&str[10], &str[10]},
				{&str[14], &str[14]},
				{&str[16], &str[16]}
			};

			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}

		TEST_METHOD(The_variable_is_similar_to_a_single_letter_var_1)
		{
			char str[] = "double _a;";

			int expCountVar = 0;
			Word expVars[MAX_COUNT_VAR_IN_STRING] = {};

			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}

		TEST_METHOD(The_variable_is_similar_to_a_single_letter_var_2)
		{
			char str[] = "double a_;";

			int expCountVar = 0;
			Word expVars[MAX_COUNT_VAR_IN_STRING] = {};

			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}

		TEST_METHOD(The_variable_is_similar_to_a_single_letter_var_3)
		{
			char str[] = "double a0;";

			int expCountVar = 0;
			Word expVars[MAX_COUNT_VAR_IN_STRING] = {};

			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}

		TEST_METHOD(The_variable_is_similar_to_a_single_letter_var_4)
		{
			char str[] = "f();";

			int expCountVar = 0;
			Word expVars[MAX_COUNT_VAR_IN_STRING] = {};

			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}
		
		TEST_METHOD(The_variable_is_similar_to_a_single_letter_var_5)
		{
			char str[] = "f();";

			int expCountVar = 0;
			Word expVars[MAX_COUNT_VAR_IN_STRING] = {};

			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}

		TEST_METHOD(The_function_is_similar_to_a_single_letter_var_6)
		{
			char str[] = "((f))(());";

			int expCountVar = 0;
			Word expVars[MAX_COUNT_VAR_IN_STRING] = {};

			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}

		TEST_METHOD(There_are_no_single_letter_variables)
		{
			char str[] = "char not_single_letter_var, mid_x_y;";

			int expCountVar = 0;
			Word expVars[MAX_COUNT_VAR_IN_STRING] = {};

			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}

		TEST_METHOD(Finding_a_variable_within_a_given_boundary)
		{
			char str[] = "while(q > 0 && rightLimit != q); // int x = 0";

			char* startStr = str + 5;// pointer to the first parenthesis of the loop header `(`
			char* endStr = str + 32; // pointer to `//`

			int expCountVar = 2;
			Word expVars[MAX_COUNT_VAR_IN_STRING] = {
				{&str[6],&str[6]},
				{&str[29],&str[29]}
			};

			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				startStr, endStr,
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}

		TEST_METHOD(Single_letter_variable_on_the_left_border_on_the_left_border_of_the_search)
		{
			char str[] = "f(i)";

			int expCountVar = 1;
			Word expVars[MAX_COUNT_VAR_IN_STRING] = {
				{&str[2],&str[2]}
			};

			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}

		TEST_METHOD(empty_string)
		{
			char str[] = "			";

			int expCountVar = 0;
			Word expVars[MAX_COUNT_VAR_IN_STRING] = {};

			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}

		TEST_METHOD(lenght_string_is_zero)
		{
			char str[] = "";

			int expCountVar = 0;
			Word expVars[MAX_COUNT_VAR_IN_STRING] = {};

			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}

		TEST_METHOD(Single_letter_variable_at_the_end_of_the_line_and_spaces_between_type_and_name)
		{
			char str[] = "float           q";
			
			int expCountVar = 1;
			Word expVars[] = {
				{&str[16],&str[16]}
			};

			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}

		TEST_METHOD(At_the_end_of_the_variable_value_there_is_a_data_type_suffix_1)
		{
			char str[] = "float q = 4.3f";

			int expCountVar = 1;
			Word expVars[] = {
				{&str[6],&str[6]}
			};

			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}

		TEST_METHOD(At_the_end_of_the_variable_value_there_is_a_data_type_suffix_2)
		{
			char str[] = "long a = 4LL";

			int expCountVar = 1;
			Word expVars[] = {
				{&str[5],&str[5]}
			};

			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}

		TEST_METHOD(Non_decimal_numbers) 
		{
			char str[] = "int some = 1e-3 + 4E5 + 0x3BC2FA;";

			int expCountVar = 0;
			Word expVars[MAX_COUNT_VAR];

			Word actualVars[MAX_COUNT_VAR_IN_STRING];
			int actualCountVar = findSingleLetterVariablesInString(
				str, (str + strlen(str)),
				actualVars
			);

			int countOfBytesCompared = sizeof(Word) * expCountVar;
			int varsIsEqual = memcmp(expVars, actualVars, countOfBytesCompared) == 0;
			Assert::IsTrue(
				expCountVar == actualCountVar &&
				varsIsEqual
			);
		}
	};
}