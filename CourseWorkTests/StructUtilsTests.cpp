#include "pch.h"
#include "CppUnitTest.h"
#include "../CourseWork_Smirnov/Common.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommonTests
{
	TEST_CLASS(test_func_collectVariableOccurrenceFromRange) 
	{
		TEST_METHOD(Collet_element_from_empty_array) 
		{
			int size = 0;
			VariableOccurrence varOccurrences[MAX_COUNT_VAR];

			Range range = { {0, 2}, {0,10} };

			const int expSize = 0;
			VariableOccurrence expCollectdOccurrences[MAX_COUNT_VAR];

			VariableOccurrence actualCollectedOccurrences[MAX_COUNT_VAR];
			int actualSize = collectVariableOccurrenceFromRange(&range, varOccurrences, size, actualCollectedOccurrences);

			int sizeAreEqual = actualSize == expSize;
			int occurrencesAreEqual = memcmp(expCollectdOccurrences, actualCollectedOccurrences, sizeof(VariableOccurrence) * expSize) == 0;

			Assert::IsTrue(sizeAreEqual && occurrencesAreEqual);
		}

		TEST_METHOD(Collect_elements_from_some_line)
		{
			int size = 7;
			VariableOccurrence varOccurrences[MAX_COUNT_VAR] = {
				{"i", {2,3}}, {"i", {2,5}}, {"x", {2,7}},
				{"a", {3,1}}, {"b", {3, 4}}, {"x", {4,0}},
				{"l", {9,0} }
			};

			Range range = { {2,4}, {3,4} };

			const int expSize = 4;
			VariableOccurrence expCollectdOccurrences[expSize] = {
				{"i", {2,5}}, {"x", {2,7}}, {"a", {3,1}}, {"b", {3, 4}}
			};

			VariableOccurrence actualCollectedOccurrences[MAX_COUNT_VAR];
			int actualSize = collectVariableOccurrenceFromRange(&range, varOccurrences, size, actualCollectedOccurrences);

			int sizeAreEqual = actualSize == expSize;
			int occurrencesAreEqual = memcmp(expCollectdOccurrences, actualCollectedOccurrences, sizeof(VariableOccurrence) * expSize) == 0;

			Assert::IsTrue(sizeAreEqual && occurrencesAreEqual);
		}

		TEST_METHOD(No_elements_in_range)
		{
			int size = 7;
			VariableOccurrence varOccurrences[MAX_COUNT_VAR] = {
				{"i", {2,3}}, {"i", {2,5}}, {"x", {2,7}},
				{"a", {3,1}}, {"b", {3, 4}}, {"x", {4,0}},
				{"l", {9,0} }
			};

			Range range = { {3,5}, {3,9} };

			const int expSize = 0;
			VariableOccurrence expCollectdOccurrences[MAX_COUNT_VAR];// = {
			//	{"i", {2,5}}, {"x", {2,7}}, {"a", {3,1}}, {"b", {3, 4}}
			//};

			VariableOccurrence actualCollectedOccurrences[MAX_COUNT_VAR];
			int actualSize = collectVariableOccurrenceFromRange(&range, varOccurrences, size, actualCollectedOccurrences);

			int sizeAreEqual = actualSize == expSize;
			int occurrencesAreEqual = memcmp(expCollectdOccurrences, actualCollectedOccurrences, sizeof(VariableOccurrence) * expSize) == 0;

			Assert::IsTrue(sizeAreEqual && occurrencesAreEqual);
		}

		TEST_METHOD(Invalid_range)
		{
			int size = 7;
			VariableOccurrence varOccurrences[MAX_COUNT_VAR] = {
				{"i", {2,3}}, {"i", {2,5}}, {"x", {2,7}},
				{"a", {3,1}}, {"b", {3, 4}}, {"x", {4,0}},
				{"l", {9,0} }
			};

			Range range;// = { {3,5}, {3,9} };

			const int expSize = 0;
			VariableOccurrence expCollectdOccurrences[MAX_COUNT_VAR];// = {
			//	{"i", {2,5}}, {"x", {2,7}}, {"a", {3,1}}, {"b", {3, 4}}
			//};

			VariableOccurrence actualCollectedOccurrences[MAX_COUNT_VAR];
			int actualSize = collectVariableOccurrenceFromRange(&range, varOccurrences, size, actualCollectedOccurrences);

			int sizeAreEqual = actualSize == expSize;
			int occurrencesAreEqual = memcmp(expCollectdOccurrences, actualCollectedOccurrences, sizeof(VariableOccurrence) * expSize) == 0;

			Assert::IsTrue(sizeAreEqual && occurrencesAreEqual);
		}
	};

	TEST_CLASS(test_func_inRange) 
	{
		TEST_METHOD(Occurrence_not_in_range) 
		{
			Range range = { {1,0},{1,9} };

			Occurrence occ = { 2,3 };

			int expResult = 0;
			int actualResult = inRange(&range, &occ);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(Occurrence_in_range) 
		{
			Range range = { {1,0},{1,9} };

			Occurrence occ = { 1,5 };

			int expResult = 1;
			int actualResult = inRange(&range, &occ);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(Occurrence_in_a_range_but_the_ends_of_the_range_are_on_different_lines) 
		{
			Range range = { {1,0},{5,9} };

			Occurrence occ = { 4,5 };

			int expResult = 1;
			int actualResult = inRange(&range, &occ);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(Occurrence_in_is_at_the_beginning_of_the_range) 
		{
			Range range = { {1,0},{5,9} };

			Occurrence occ = { 1,0 };

			int expResult = 1;
			int actualResult = inRange(&range, &occ);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(Occurrence_in_is_at_the_end_of_the_range)
		{
			Range range = { {1,0},{5,9} };

			Occurrence occ = { 5,9 };

			int expResult = 1;
			int actualResult = inRange(&range, &occ);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(Occurrence_is_not_in_the_range_but_is_close_to_the_boundary_1) 
		{
			Range range = { {1,0},{5,9} };

			Occurrence occ = { 6,0 };

			int expResult = 0;
			int actualResult = inRange(&range, &occ);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(Occurrence_is_not_in_the_range_but_is_close_to_the_boundary_2)
		{
			Range range = { {0,9},{5,9} };

			Occurrence occ = { 0,8 };

			int expResult = 0;
			int actualResult = inRange(&range, &occ);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(Occurrence_is_not_in_the_range_but_is_close_to_the_boundary_3) 
		{
			Range range = { {1,0},{5,9} };

			Occurrence occ = { 5, 10 };

			int expResult = 0;
			int actualResult = inRange(&range, &occ);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(Uninitialized_occurrence) 
		{
			Range range = { {1,0},{5,9} };

			Occurrence occ;

			int expResult = 0;
			int actualResult = inRange(&range, &occ);

			Assert::AreEqual(expResult, actualResult);
		}

	};

	TEST_CLASS(test_func_isInitializedLoopOccurrence) 
	{
		TEST_METHOD(LoopOccurrence_has_been_initialized)
		{
			LoopOccurrence loopOcc = { WHILE, { {1,0}, {1,2} },{{2,0}, {3,0}} };

			int expResult = 1;
			int actualResult = isInitializedLoopOccurrence(&loopOcc);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(LoopOccurrence_has_not_been_initialized)
		{
			LoopOccurrence loopOcc;

			int expResult = 0;
			int actualResult = isInitializedLoopOccurrence(&loopOcc);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(The_LoopOccurrence_was_not_fully_initialized_1)
		{
			LoopOccurrence loopOcc = { UNKNOW, { {1,0}, {1,2} },{{2,0}, {3,0}} };

			int expResult = 0;
			int actualResult = isInitializedLoopOccurrence(&loopOcc);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(The_LoopOccurrence_was_not_fully_initialized_2)
		{
			LoopOccurrence loopOcc = { FOR, { {1,0}, {1,2} }, UNINITED_RANGE };

			int expResult = 0;
			int actualResult = isInitializedLoopOccurrence(&loopOcc);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(The_LoopOccurrence_was_not_fully_initialized_3)
		{
			LoopOccurrence loopOcc = { DO_WHILE, UNINITED_RANGE,  { {2,0}, {3,0} } };

			int expResult = 0;
			int actualResult = isInitializedLoopOccurrence(&loopOcc);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(The_LoopOccurrence_was_not_fully_initialized_4)
		{
			LoopOccurrence loopOcc = { DO_WHILE, { {-1,-1}, {1,2} },  { {2,0}, {3,0} } };

			int expResult = 0;
			int actualResult = isInitializedLoopOccurrence(&loopOcc);

			Assert::AreEqual(expResult, actualResult);
		}
	};

	TEST_CLASS(test_func_isInitializedRange) 
	{
		TEST_METHOD(Range_has_been_initialized)
		{
			Range range = { {3,9}, {3,2} };

			int expResult = 1;
			int actualResult = isInitializedRange(&range);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(Range_has_not_been_initialized)
		{
			Range range;

			int expResult = 0;
			int actualResult = isInitializedRange(&range);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(The_range_was_not_fully_initialized_1)
		{
			Range range = { {-1, 5}, {3,5} };

			int expResult = 0;
			int actualResult = isInitializedRange(&range);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(The_range_was_not_fully_initialized_2)
		{
			Range range = { {1, 5}, {-1,-1} };

			int expResult = 0;
			int actualResult = isInitializedRange(&range);

			Assert::AreEqual(expResult, actualResult);
		}
	};

	TEST_CLASS(test_func_isInitializedOccurrence) 
	{
		TEST_METHOD(Occurrences_has_been_initialized) 
		{
			Occurrence occ = { 3,9 };
			
			int expResult = 1;
			int actualResult = isInitializedOccurrence(&occ);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(Occurrences_has_not_been_initialized) 
		{
			Occurrence occ;

			int expResult = 0;
			int actualResult = isInitializedOccurrence(&occ);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(The_occurrences_was_not_fully_initialized_1) 
		{
			Occurrence occ = {-1, 9};

			int expResult = 0;
			int actualResult = isInitializedOccurrence(&occ);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(The_occurrences_was_not_fully_initialized_2)
		{
			Occurrence occ = { 1, -1 };

			int expResult = 0;
			int actualResult = isInitializedOccurrence(&occ);

			Assert::AreEqual(expResult, actualResult);
		}
	};

	TEST_CLASS(test_func_isOperatorOrFunction) 
	{
		TEST_METHOD(Word_is_not_operator_of_functio_1) 
		{
			char str[] = "int a";

			Word word = { &str[0], &str[2] };
			char endOfStr = str[strlen(str)];

			int expResult = 0;
			int actualResult = isOperatorOrFunction(&word, &endOfStr);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(Word_is_not_operator_of_function_2)
		{
			char str[] = "int a";

			Word word = { &str[4], &str[4] };
			char endOfStr = str[strlen(str)];

			int expResult = 0;
			int actualResult = isOperatorOrFunction(&word, &endOfStr);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(Word_is_function)
		{
			char str[] = "int a = f(x)";


			Word word = { &str[8], &str[8] };
			char endOfStr = str[strlen(str)];

			int expResult = 1;
			int actualResult = isOperatorOrFunction(&word, &endOfStr);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(Word_is_operator_1)
		{
			char str[] = "if(f(x))";

			Word word = { &str[0], &str[1] };
			char endOfStr = str[strlen(str)];

			int expResult = 1;
			int actualResult = isOperatorOrFunction(&word, &endOfStr);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(Word_is_operator_2)
		{
			char str[] = "while(f(x))";

			Word word = { &str[0], &str[4] };
			char endOfStr = str[strlen(str)];

			int expResult = 1;
			int actualResult = isOperatorOrFunction(&word, &endOfStr);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(The_word_is_surrounded_by_parentheses_and_is_a_function)
		{
			char str[] = "(f)((x))";

			Word word = { &str[1], &str[1] };
			char endOfStr = str[strlen(str)];

			int expResult = 1;
			int actualResult = isOperatorOrFunction(&word, &endOfStr);

			Assert::AreEqual(expResult, actualResult);
		}
	};

	TEST_CLASS(test_func_cmpOccurrence) 
	{
		TEST_METHOD(Occurrences_are_quals) 
		{
			Occurrence occ1 = { 5, 5 };
			Occurrence occ2 = { 5, 5 };

			int expResultOfCompare = 0;
			int actulaResultOfCompare = cmpOccurrence(&occ1, &occ2);

			Assert::AreEqual(expResultOfCompare, actulaResultOfCompare);
		}

		TEST_METHOD(The_first_occurrence_is_further_down_the_line_than_the_second) 
		{
			Occurrence occ1 = { 5, 6 };
			Occurrence occ2 = { 5, 5 };

			int expResultOfCompare = 1;
			int actulaResultOfCompare = cmpOccurrence(&occ1, &occ2);

			Assert::AreEqual(expResultOfCompare, actulaResultOfCompare);
		}

		TEST_METHOD(The_second_occurrence_is_further_down_the_line_than_the_first) 
		{
			Occurrence occ1 = { 5, 5 };
			Occurrence occ2 = { 5, 6 };

			int expResultOfCompare = -1;
			int actulaResultOfCompare = cmpOccurrence(&occ1, &occ2);

			Assert::AreEqual(expResultOfCompare, actulaResultOfCompare);
		}

		TEST_METHOD(Occurrences_are_located_on_different_lines_1) 
		{
			Occurrence occ1 = { 5, 5 };
			Occurrence occ2 = { 7, 5 };

			int expResultOfCompare = -1;
			int actulaResultOfCompare = cmpOccurrence(&occ1, &occ2);

			Assert::AreEqual(expResultOfCompare, actulaResultOfCompare);
		}

		TEST_METHOD(Occurrences_are_located_on_different_lines_2)
		{
			Occurrence occ1 = { 5, 5 };
			Occurrence occ2 = { 7, 5 };

			int expResultOfCompare = 1;
			int actulaResultOfCompare = cmpOccurrence(&occ2, &occ1);

			Assert::AreEqual(expResultOfCompare, actulaResultOfCompare);
		}
	};

	TEST_CLASS(test_func_determineBordersOfSearchInLineOfCode)
	{
		TEST_METHOD(A_simple_line_of_code_starting_and_ending_at_the_beginning_and_end_of_the_line)
		{
			Text code = {
			{
			"for(int i = 0; i < 5; i++)",
			"{",
			"		i + 1;",
			"		// a++",
			"	}	"
			}, 5
			};

			// First occurrence posiotion second `;` in for-heade, second occurrence posiotion closing curly brace
			Range range = { {0, 20}, {4, 1} };
			int idxCurrentStr = 2;

			char* expStartPtr = NULL;
			expStartPtr = &code.text[idxCurrentStr][0];
			char* expEndPtr;
			expEndPtr = &code.text[idxCurrentStr][strlen(code.text[idxCurrentStr])];

			char* actualStartPtr = NULL;
			char* actualEndPtr = NULL;

			determineBordersOfSearchInLineOfCode(idxCurrentStr, range, &code, &actualStartPtr, &actualEndPtr);

			Assert::IsTrue(actualStartPtr == expStartPtr && actualEndPtr == expEndPtr);
		}

		TEST_METHOD(The_initial_boundary_coincides_with_the_range)
		{
			Text code = {
			{
			"for(int i = 0; i < 5; i++)",
			"{",
			"		i + 1;",
			"		// a++",
			"	}	",
			}, 5
			};

			// First occurrence posiotion second `;` in for-heade, second occurrence posiotion closing curly brace
			Range range = { {0, 20}, {4, 1} };
			int idxCurrentStr = 0;

			char* expStartPtr = NULL;
			expStartPtr = &code.text[idxCurrentStr][20];
			char* expEndPtr;
			expEndPtr = &code.text[idxCurrentStr][strlen(code.text[0])];

			char* actualStartPtr = NULL;
			char* actualEndPtr = NULL;

			determineBordersOfSearchInLineOfCode(idxCurrentStr, range, &code, &actualStartPtr, &actualEndPtr);

			Assert::IsTrue(actualStartPtr == expStartPtr && actualEndPtr == expEndPtr);
		}

		TEST_METHOD(The_end_boundary_coincides_with_the_end_of_the_range)
		{
			Text code = {
			{
			"for(int i = 0; i < 5; i++)",
			"{",
			"		i + 1;",
			"		// a++",
			"	}	"
			}, 5
			};

			// First occurrence posiotion second `;` in for-heade, second occurrence posiotion closing curly brace
			Range range = { {0, 20}, {4, 1} };
			int idxCurrentStr = 4;

			char* expStartPtr = NULL;
			expStartPtr = &code.text[idxCurrentStr][0];
			char* expEndPtr;
			expEndPtr = &code.text[idxCurrentStr][1];

			char* actualStartPtr = NULL;
			char* actualEndPtr = NULL;

			determineBordersOfSearchInLineOfCode(idxCurrentStr, range, &code, &actualStartPtr, &actualEndPtr);

			Assert::IsTrue(actualStartPtr == expStartPtr && actualEndPtr == expEndPtr);
		}

		TEST_METHOD(The_end_boundary_must_coincide_with_the_start_of_the_comment)
		{
			Text code = {
			{
			"for(int i = 0; i < 5; i++)",
			"{",
			"		i + 1;",
			"		// a++",
			"	}	"
			}, 5
			};

			// First occurrence posiotion second `;` in for-heade, second occurrence posiotion closing curly brace
			Range range = { {0, 20}, {4, 1} };
			int idxCurrentStr = 3;

			char* expStartPtr = NULL;
			expStartPtr = &code.text[idxCurrentStr][0];
			char* expEndPtr;
			expEndPtr = &code.text[idxCurrentStr][2];

			char* actualStartPtr = NULL;
			char* actualEndPtr = NULL;

			determineBordersOfSearchInLineOfCode(idxCurrentStr, range, &code, &actualStartPtr, &actualEndPtr);

			Assert::IsTrue(actualStartPtr == expStartPtr && actualEndPtr == expEndPtr);
		}

		TEST_METHOD(The_end_of_the_range_is_behind_the_comment)
		{
			Text code = {
			{
			"for(int i = 0; i < 5; i++)",
			"{",
			"		i + 1;",
			"		// a++",
			"	}	",
			}, 5
			};

			// First occurrence posiotion second `;` in for-heade, second occurrence posiotion closing curly brace
			Range range = { {0, 20}, {3, 5} };
			int idxCurrentStr = 3;

			char* expStartPtr = NULL;
			expStartPtr = &code.text[idxCurrentStr][0];
			char* expEndPtr;
			expEndPtr = &code.text[idxCurrentStr][2];

			char* actualStartPtr = NULL;
			char* actualEndPtr = NULL;

			determineBordersOfSearchInLineOfCode(idxCurrentStr, range, &code, &actualStartPtr, &actualEndPtr);

			Assert::IsTrue(actualStartPtr == expStartPtr && actualEndPtr == expEndPtr);
		}
	};

	TEST_CLASS(test_func_sortVariableOccurrencesArrayByOccurrence)
	{
		TEST_METHOD(Sort_empty_array)
		{
			const int size = 0;
			VariableOccurrence arr[MAX_COUNT_VAR];

			VariableOccurrence expSorted[MAX_COUNT_VAR];

			sortVariableOccurrencesArrayByOccurrence(arr, size);

			int sortedAreEqual = memcmp(expSorted, arr, sizeof(VariableOccurrence) * size) == 0;
			Assert::IsTrue(sortedAreEqual);
		}

		TEST_METHOD(Sorting_an_array_consisting_of_one_element)
		{
			const int size = 1;
			VariableOccurrence arr[MAX_COUNT_VAR] = {
				{"a", {1,0}}
			};

			VariableOccurrence expSorted[MAX_COUNT_VAR]{
				{"a", {1,0}}
			};

			sortVariableOccurrencesArrayByOccurrence(arr, size);

			int sortedAreEqual = memcmp(expSorted, arr, sizeof(VariableOccurrence) * size) == 0;
			Assert::IsTrue(sortedAreEqual);
		}
		
		TEST_METHOD(Sorting_an_array_consisting_of_some_element)
		{
			const int size = 5;
			VariableOccurrence arr[MAX_COUNT_VAR] = {
				{"a", {5,1}},
				{"b", {5,0}},
				{"a", {6,0}},
				{"c", {0,1}},
				{"b", {5,2}}
			};

			VariableOccurrence expSorted[MAX_COUNT_VAR]{
				{"c", {0,1}},
				{"b", {5,0}},
				{"a", {5,1}},
				{"b", {5,2}},
				{"a", {6,0}}
			};

			sortVariableOccurrencesArrayByOccurrence(arr, size);

			int sortedAreEqual = memcmp(expSorted, arr, sizeof(VariableOccurrence) * size) == 0;
			Assert::IsTrue(sortedAreEqual);
		}

		TEST_METHOD(Sorting_an_array_where_all_occurrences_are_equal) 
		{
			const int size = 5;
			VariableOccurrence arr[MAX_COUNT_VAR] = {
				{"a", {5,0}},
				{"b", {5,0}},
				{"a", {5,0}},
				{"c", {5,0}},
				{"b", {5,0}}
			};

			VariableOccurrence expSorted[MAX_COUNT_VAR]{
				{"a", {5,0}},
				{"b", {5,0}},
				{"a", {5,0}},
				{"c", {5,0}},
				{"b", {5,0}}
			};

			sortVariableOccurrencesArrayByOccurrence(arr, size);

			int sortedAreEqual = memcmp(expSorted, arr, sizeof(VariableOccurrence) * size) == 0;
			Assert::IsTrue(sortedAreEqual);
		}
	};

	TEST_CLASS(test_func_intersectVariableOccurrenceByName)
	{
		TEST_METHOD(Intersect_of_two_empty_arrays)
		{
			VariableOccurrence srcVarOcc1[MAX_COUNT_VAR];
			int sizeSrc1 = 0;
			VariableOccurrence srcVarOcc2[MAX_COUNT_VAR];
			int sizeSrc2 = 0;

			VariableOccurrence expIntersect[MAX_COUNT_VAR];
			int expSize = 0;

			VariableOccurrence actualIntersect[MAX_COUNT_VAR];
			int actualSize = intersectVariableOccurrenceByName(srcVarOcc1, sizeSrc1, srcVarOcc2, sizeSrc2, actualIntersect);
			sortVariableOccurrencesArrayByOccurrence(actualIntersect, actualSize);

			int sizesAreEquals = expSize == actualSize;
			int intersectionAreEquals = memcmp(actualIntersect, expIntersect, sizeof(VariableOccurrence) * expSize) == 0;

			Assert::IsTrue(sizesAreEquals && intersectionAreEquals);
		}

		TEST_METHOD(Intersect_one_empty_and_one_filled_arrays_1)
		{
			VariableOccurrence srcVarOcc1[MAX_COUNT_VAR];
			int sizeSrc1 = 0;
			VariableOccurrence srcVarOcc2[MAX_COUNT_VAR] = {
				{"a", {4,5}},
				{"b", {5,4}}
			};
			int sizeSrc2 = 2;

			VariableOccurrence expIntersect[MAX_COUNT_VAR];
			int expSize = 0;

			VariableOccurrence actualIntersect[MAX_COUNT_VAR];
			int actualSize = intersectVariableOccurrenceByName(srcVarOcc1, sizeSrc1, srcVarOcc2, sizeSrc2, actualIntersect);
			sortVariableOccurrencesArrayByOccurrence(actualIntersect, actualSize);

			int sizesAreEquals = expSize == actualSize;
			int intersectionAreEquals = memcmp(actualIntersect, expIntersect, sizeof(VariableOccurrence) * expSize) == 0;

			Assert::IsTrue(sizesAreEquals && intersectionAreEquals);
		}

		TEST_METHOD(Intersect_one_empty_and_one_filled_arrays_2)
		{
			VariableOccurrence srcVarOcc1[MAX_COUNT_VAR] = {
				{"a", {4,5}},
				{"b", {5,4}}
			};
			int sizeSrc1 = 2;

			VariableOccurrence srcVarOcc2[MAX_COUNT_VAR];
			int sizeSrc2 = 0;

			VariableOccurrence expIntersect[MAX_COUNT_VAR];
			int expSize = 0;

			VariableOccurrence actualIntersect[MAX_COUNT_VAR];
			int actualSize = intersectVariableOccurrenceByName(srcVarOcc1, sizeSrc1, srcVarOcc2, sizeSrc2, actualIntersect);
			sortVariableOccurrencesArrayByOccurrence(actualIntersect, actualSize);

			int sizesAreEquals = expSize == actualSize;
			int intersectionAreEquals = memcmp(actualIntersect, expIntersect, sizeof(VariableOccurrence) * expSize) == 0;

			Assert::IsTrue(sizesAreEquals && intersectionAreEquals);
		}

		TEST_METHOD(Intersect_of_two_arrays_with_only_one_common_name)
		{
			VariableOccurrence srcVarOcc1[MAX_COUNT_VAR] = {
				{"a", {4,5}},
				{"b", {4,9}}
			};
			int sizeSrc1 = 2;
			VariableOccurrence srcVarOcc2[MAX_COUNT_VAR] = {
				{"a", {3,1}},
				{"a", {3,4}}
			};
			int sizeSrc2 = 2;

			VariableOccurrence expIntersect[MAX_COUNT_VAR] = {
				{"a", {3,1}},
				{"a", {3,4}},
				{"a", {4,5}},
			};
			int expSize = 3;

			VariableOccurrence actualIntersect[MAX_COUNT_VAR];
			int actualSize = intersectVariableOccurrenceByName(srcVarOcc1, sizeSrc1, srcVarOcc2, sizeSrc2, actualIntersect);
			sortVariableOccurrencesArrayByOccurrence(actualIntersect, actualSize);

			int sizesAreEquals = expSize == actualSize;
			int intersectionAreEquals = memcmp(actualIntersect, expIntersect, sizeof(VariableOccurrence) * expSize) == 0;

			Assert::IsTrue(sizesAreEquals && intersectionAreEquals);
		}

		TEST_METHOD(Intersection_of_two_arrays_by_several_common_names)
		{
			VariableOccurrence srcVarOcc1[MAX_COUNT_VAR] = {
				{"a", {4,5}},
				{"b", {4,9}},
				{"b", {0,1}}
			};
			int sizeSrc1 = 3;
			VariableOccurrence srcVarOcc2[MAX_COUNT_VAR] = {
				{"a", {3,1}},
				{"a", {3,4}},
				{"b", {1,1}},
				{"c", {0,0}},
				{"c", {0,2}}
			};
			int sizeSrc2 = 5;

			VariableOccurrence expIntersect[MAX_COUNT_VAR] = {
				{"b", {0,1}},
				{"b", {1,1}},
				{"a", {3,1}},
				{"a", {3,4}},
				{"a", {4,5}},
				{"b", {4,9}}
			};
			int expSize = 6;

			VariableOccurrence actualIntersect[MAX_COUNT_VAR];
			int actualSize = intersectVariableOccurrenceByName(srcVarOcc1, sizeSrc1, srcVarOcc2, sizeSrc2, actualIntersect);
			sortVariableOccurrencesArrayByOccurrence(actualIntersect, actualSize);

			int sizesAreEquals = expSize == actualSize;
			int intersectionAreEquals = memcmp(actualIntersect, expIntersect, sizeof(VariableOccurrence) * expSize) == 0;

			Assert::IsTrue(sizesAreEquals && intersectionAreEquals);
		}

		TEST_METHOD(No_intersection_by_name) 
		{
			VariableOccurrence srcVarOcc1[MAX_COUNT_VAR] = {
				{"a", {4,5}},
				{"b", {4,9}},
				{"b", {0,1}}
			};
			int sizeSrc1 = 3;
			VariableOccurrence srcVarOcc2[MAX_COUNT_VAR] = {
				{"z", {3,1}},
				{"x", {3,4}},
				{"x", {1,1}},
				{"c", {0,0}},
				{"t", {0,2}}
			};
			int sizeSrc2 = 5;

			VariableOccurrence expIntersect[MAX_COUNT_VAR];
			int expSize = 0;

			VariableOccurrence actualIntersect[MAX_COUNT_VAR];
			int actualSize = intersectVariableOccurrenceByName(srcVarOcc1, sizeSrc1, srcVarOcc2, sizeSrc2, actualIntersect);
			sortVariableOccurrencesArrayByOccurrence(actualIntersect, actualSize);

			int sizesAreEquals = expSize == actualSize;
			int intersectionAreEquals = memcmp(actualIntersect, expIntersect, sizeof(VariableOccurrence) * expSize) == 0;

			Assert::IsTrue(sizesAreEquals && intersectionAreEquals);
		}
	};

	TEST_CLASS(test_func_cmpReportRecords)
	{
		TEST_METHOD(twoReportRecordsAreEquals)
		{
			struct ReportRecord record1 = { 1, "name" };
			struct ReportRecord record2 = { 1, "name" };

			int expCompareResult = 1; // equals
			int actualCompareResult = cmpReportRecords(&record1, &record2);

			Assert::AreEqual(expCompareResult, actualCompareResult);
		}

		TEST_METHOD(twoReportRecordsAreNotEqualsBecauseNumberStringOfRecordsNotEquals)
		{
			struct ReportRecord record1 = { 1, "name" };
			struct ReportRecord record2 = { 2, "name" };

			int expCompareResult = 0; // equals
			int actualCompareResult = cmpReportRecords(&record1, &record2);

			Assert::AreEqual(expCompareResult, actualCompareResult);
		}

		TEST_METHOD(twoReportRecordsAreNotEqualsBecauseNameVarNotEquals)
		{
			struct ReportRecord record1 = { 0, "namename" };
			struct ReportRecord record2 = { 1, "name" };

			int expCompareResult = 0; // equals
			int actualCompareResult = cmpReportRecords(&record1, &record2);

			Assert::AreEqual(expCompareResult, actualCompareResult);
		}
	};

	TEST_CLASS(test_func_cmpReports)
	{
		TEST_METHOD(oneOfTheTwoReportsIsEmpty)
		{
			const int sizeReport1 = 2;
			ReportRecord report1[sizeReport1] = {
				{3, "a"},
				{5, "name"}
			};

			const int sizeReport2 = 0;
			struct ReportRecord report2[MAX_COUNT_STRING];

			int expCompareReportResult = 0;
			int actualCompareReportResult = cmpReports(report1, sizeReport1, report2, sizeReport2);

			Assert::AreEqual(expCompareReportResult, actualCompareReportResult);
		}

		TEST_METHOD(twoReportAreEquals)
		{
			const int sizeReport1 = 2;
			ReportRecord report1[sizeReport1] = {
				{3, "a"},
				{5, "name"}
			};

			const int sizeReport2 = 2;
			ReportRecord report2[MAX_COUNT_STRING] = {
				{3, "a"},
				{5, "name"}
			};

			int expCompareReportResult = 1;
			int actualCompareReportResult = cmpReports(report1, sizeReport1, report2, sizeReport2);

			Assert::AreEqual(expCompareReportResult, actualCompareReportResult);
		}

		TEST_METHOD(twoReportAreNotEqualsByNames)
		{
			const int sizeReport1 = 2;
			ReportRecord report1[sizeReport1] = {
				{3, "a"},
				{5, "namename"}
			};

			const int sizeReport2 = 2;
			ReportRecord report2[sizeReport2] = {
				{3, "a"},
				{5, "name"}
			};

			int expCompareReportResult = 0;
			int actualCompareReportResult = cmpReports(report1, sizeReport1, report2, sizeReport2);

			Assert::AreEqual(expCompareReportResult, actualCompareReportResult);
		}
	};

	TEST_CLASS(test_func_containsInRepord)
	{
		TEST_METHOD(Report_is_empty)
		{
			Report report;
			int sizeReport = 0;

			ReportRecord record = { 2, "a" };

			int expResult = 0;
			int actualResult = containsInRepord(&record, report, sizeReport);

			Assert::IsTrue(expResult == actualResult);
		}

		TEST_METHOD(Record_contains_in_report_consist_from_single_element)
		{
			Report report =
			{
				{2, "a"}
			};
			int sizeReport = 1;

			ReportRecord record = { 2, "a" };

			int expResult = 1;
			int actualResult = containsInRepord(&record, report, sizeReport);

			Assert::IsTrue(expResult == actualResult);
		}

		TEST_METHOD(In_report_contains_record_with_same_index_of_string_but_different_value) 
		{
			Report report =
			{
				{2, "a"},
				{2, "b"},
				{2, "c"},
				{9, "q"}
			};
			int sizeReport = 4;

			ReportRecord record = { 2, "x" };

			int expResult = 0;
			int actualResult = containsInRepord(&record, report, sizeReport);

			Assert::IsTrue(expResult == actualResult);
		}

		TEST_METHOD(In_report_contains_record_with_equal_values_but_different_infex_of_string) 
		{
			Report report =
			{
				{3, "x"},
				{3, "b"},
				{3, "c"},
				{9, "q"}
			};
			int sizeReport = 4;

			ReportRecord record = { 2, "x" };

			int expResult = 0;
			int actualResult = containsInRepord(&record, report, sizeReport);

			Assert::IsTrue(expResult == actualResult);
		}

		TEST_METHOD(The_element_you_are_looking_for_is_in_the_array_and_is_at_the_beginning)
		{
			Report report =
			{
				{2, "x"},
				{3, "b"},
				{3, "c"},
				{9, "q"}
			};
			int sizeReport = 4;

			ReportRecord record = { 2, "x" };

			int expResult = 1;
			int actualResult = containsInRepord(&record, report, sizeReport);

			Assert::IsTrue(expResult == actualResult);
		}

		TEST_METHOD(The_element_you_are_looking_for_is_in_the_array_and_is_at_the_end)
		{
			Report report =
			{
				{3, "b"},
				{3, "c"},
				{9, "q"},
				{2, "x"}
			};
			int sizeReport = 4;

			ReportRecord record = { 2, "x" };

			int expResult = 1;
			int actualResult = containsInRepord(&record, report, sizeReport);

			Assert::IsTrue(expResult == actualResult);
		}
	};

	TEST_CLASS(test_func_containsInVariableOccurrenceArray) 
	{
		TEST_METHOD(Empty_array) 
		{
			const int size = 0;
			VariableOccurrence arr[MAX_COUNT_VAR];

			VariableOccurrence searchElement = { "x", {0,1} };

			int expResult = 0;
			int actualResult = containsInVariableOccurrenceArray(&searchElement, arr, size);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(Search_in_signle_elemenet_arr)
		{
			const int size = 1;
			VariableOccurrence arr[MAX_COUNT_VAR] = {
				{"x",{0,2}}
			};

			VariableOccurrence searchElement = { "x", {0,1} };

			int expResult = 0;
			int actualResult = containsInVariableOccurrenceArray(&searchElement, arr, size);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(Searching_and_finding_an_element_from_a_single_element_array)
		{
			const int size = 1;
			VariableOccurrence arr[MAX_COUNT_VAR] = {
				{"x",{0,2}}
			};

			VariableOccurrence searchElement = { "x", {0,2} };

			int expResult = 1;
			int actualResult = containsInVariableOccurrenceArray(&searchElement, arr, size);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(Searching_in_an_array_consisting_of_several_elements) 
		{
			const int size = 4;
			VariableOccurrence arr[MAX_COUNT_VAR] = {
				{"b", {5,0}},
				{"a", {6,0}},
				{"c", {0,1}},
				{"b", {5,2}}
			};

			VariableOccurrence searchElement = { "c", {0,1} };

			int expResult = 1;
			int actualResult = containsInVariableOccurrenceArray(&searchElement, arr, size);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(The_element_you_are_looking_for_is_in_the_array_and_is_at_the_beginning)
		{
			const int size = 4;
			VariableOccurrence arr[MAX_COUNT_VAR] = {
				{"b", {5,0}},
				{"a", {6,0}},
				{"c", {0,1}},
				{"b", {5,2}}
			};

			VariableOccurrence searchElement = { "b", {5,0} };

			int expResult = 1;
			int actualResult = containsInVariableOccurrenceArray(&searchElement, arr, size);

			Assert::AreEqual(expResult, actualResult);
		}

		TEST_METHOD(The_element_you_are_looking_for_is_in_the_array_and_is_at_the_end)
		{
			const int size = 4;
			VariableOccurrence arr[MAX_COUNT_VAR] = {
				{"b", {5,0}},
				{"a", {6,0}},
				{"c", {0,1}},
				{"b", {5,2}}
			};

			VariableOccurrence searchElement = { "b", {5,2} };

			int expResult = 1;
			int actualResult = containsInVariableOccurrenceArray(&searchElement, arr, size);

			Assert::AreEqual(expResult, actualResult);
		}
	};
}