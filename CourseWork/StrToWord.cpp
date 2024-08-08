#include "StrToWord.h"
#include <cctype>

// ������� ����� ������� ��������� � �������� strToWord(...), ������� �� �������� � ���������

/**
* \brief ������� ���������� ��������� ������, ����������� � ��������� ������ �����
* \param[in] � - ��������� �� ������, ������� ���������� ���������
* \return 1 - ���� ������ ����������� � ��������� �������� ������ �����, 0 - ���� ���
*/
static int isCharOfWord(const char* const c);

/**
* \brief ������� ���������� ��������� ������, ����������� � ��������� ������� �����
* \param[in] � - ��������� �� ������, ������� ���������� ���������
* \return 1 - ���� ������ ����������� � ��������� �������� ������ �����, 0 - ���� ���
*/
static int isCharOfStartWord(const char* const c);

/**
* \brief ���������� ������ � ����� ����� �� ������� ��������� *currentChar
* \param[in/out] currentChar - ��������� �� ��������� ������� ������� �����
* \detail ����� ������������� ������� currentChar ����� ��������� �� ��������� �� ������ ������
* \param[in] endStr - ��������� ����� ������
* \param[out] word - �������� ��������, ���������� �� ������ ����� ����� �������� ������ *currentChar, ���������� �� ����� ��������� ��������
*/
static void determineBordersOfWord(char** currentChar,const char* const endStr, Word* word);

/**
* \brief ������� ���������� �����, �� ������� ��������� currentChar
* \param[in/out] currentChar - ��������� �� ��������� ������� ������� �����
* \detail ����� ������������� ������� currentChar ����� ��������� �� ��������� �� ������ ������
* \param[in] - endStr - ��������� ����� ������
*/
static void skipWord(char** currentChar,const char* const endStr);

int strToWords(char* startStr, char* endStr, Word words[MAX_COUNT_VAR_IN_STRING + 1])
{
	int countOfWords = 0;

	// ��� ������� ������� ����� ���������
	for (char* ptr = startStr; ptr <= endStr; ptr++) 
	{
		// ���� ������ - �����, �� ���������� ��� � ������� ���������
		if (isdigit(*ptr))
		{
			skipWord(&ptr, endStr);
		}
		// ���� ������� ������ ����� ���� ������� �����, �� ���������� ������� �����
		// ��������� ������ � ������ ���� � ������� ��������� �� �����
		if (isCharOfStartWord(ptr)) 
		{
			determineBordersOfWord(&ptr, endStr, &words[countOfWords]);
			countOfWords++;
		}
	}

	return countOfWords;
}

static void skipWord(char** currentChar, const char* const endStr)
{
	while (*currentChar != endStr && isCharOfWord(*currentChar))
	{
		(*currentChar)++;
	}
}

static int isCharOfWord(const char* const c)
{
	return isalnum(*c) || *c == '_';
}

static int isCharOfStartWord(const char* const c)
{
	return isalpha(*c) || *c == '_';
}

static void determineBordersOfWord(char** currentChar, const char* const endStr, Word* word)
{
	word->start = *currentChar;
	// Do not change the sequence of conditions so as not to go out of memory
	while (*currentChar <= endStr && isCharOfWord(*currentChar))
	{
		(*currentChar)++;
	}
	word->end = (*currentChar) - 1;
}

int getWordLength(const Word* word)
{
	return  (word->start == NULL || word->end == NULL) ? 0 : word->end - word->start + 1;
}

int wordToStr(const Word* word, char str[])
{
	int len = getWordLength(word);

	if (len == 0) return len;

	strncpy_s(str, len + 1, word->start, len);
	str[len] = '\0';

	return len;
}

 /* ------------------------- Deprecated -------------------- */

//int strToWords(char* currentChar, char* endStr, Word words[MAX_COUNT_VAR_IN_STRING + 1])
//{
//	int countOfWords = 0;
//
//	char* cur = currentChar;
//
//	int word_was_met = 0;
//	int prevCharWasDigit = 0;
//	while (cur != endStr)
//	{
//		int current_char_is_separator = isCharOfWord(cur);
//
//
//		if (!word_was_met && (isalpha(*cur) || *cur == '_'))
//		{
//			words[countOfWords].start = (char*)cur;
//			word_was_met = 1;
//		}
//		else if (word_was_met && current_char_is_separator)
//		{
//			words[countOfWords].end = (char*)(cur - 1);
//
//			word_was_met = 0;
//			countOfWords++;
//		}
//
//		cur++;
//		prevCharWasDigit = isdigit(*(cur - 1));
//
//		//we skip everything that could be a number. For example words like: 4LL
//		if (prevCharWasDigit && !word_was_met) 
//		{
//			while (cur != endStr && !isCharOfWord(cur)) { cur++; }
//		}
//	}
//	if (word_was_met)
//	{
//		words[countOfWords].end = (char*)(cur - 1);
//		countOfWords++;
//	}
//
//	return countOfWords;
//}

