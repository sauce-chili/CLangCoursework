#include "pch.h"
#include "CppUnitTest.h"
#include "../CourseWork_Smirnov/Common.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommonTests
{
	TEST_CLASS(test_func_findOneLineCommentInString) 
	{
		TEST_METHOD(The_one_line_comment_is_at_the_beginning_of_the_line) 
		{
			char str[] = "// commnet in biginning string";

			char* expPositionsOfComment = str;

			char* actualPositionOfComment = findOneLineCommentInString(str);

			Assert::AreEqual(expPositionsOfComment, actualPositionOfComment);
		}

		TEST_METHOD(The_one_line_comment_is_in_the_middle_of_the_line)
		{
			char str[] = "        // commnet in biginning string";

			char* expPositionsOfComment = &str[8];

			char* actualPositionOfComment = findOneLineCommentInString(str);

			Assert::AreEqual(expPositionsOfComment, actualPositionOfComment);
		}

		TEST_METHOD(A_one_line_comment_is_found_after_some_expression) 
		{
			char str[] = "while(1)// <- simple header loop";

			char* expPositionsOfComment = &str[8];

			char* actualPositionOfComment = findOneLineCommentInString(str);

			Assert::AreEqual(expPositionsOfComment, actualPositionOfComment);
		}

		TEST_METHOD(Double_comment_after_expression)
		{
			char str[] = "while(1)//  //<- simple header loop";

			char* expPositionsOfComment = &str[8];

			char* actualPositionOfComment = findOneLineCommentInString(str);

			Assert::AreEqual(expPositionsOfComment, actualPositionOfComment);
		}
	};
}