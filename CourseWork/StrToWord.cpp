#include "StrToWord.h"
#include <cctype>

// Функции имеют сильную связность с функцией strToWord(...), поэтому не включены в интерфейс

/**
* \brief Функция определетс являлется символ, находящийся в указателе частью слова
* \param[in] с - указатель на символ, который необходимо проверить
* \return 1 - если символ находящийся в указетеле явялется частью слова, 0 - если нет
*/
static int isCharOfWord(const char* const c);

/**
* \brief Функция определетс являлется символ, находящийся в указателе началом слова
* \param[in] с - указатель на символ, который необходимо проверить
* \return 1 - если символ находящийся в указетеле явялется начало слова, 0 - если нет
*/
static int isCharOfStartWord(const char* const c);

/**
* \brief Определяет начало и конец слова на которое ссылается *currentChar
* \param[in/out] currentChar - указатель на указатель первого символа слова
* \detail После использования функции currentChar будет указывать на следующий за словом символ
* \param[in] endStr - указатель конца поиска
* \param[out] word - выходное значение, указателем на начало слова будет значение равное *currentChar, указателем на конец найденное значение
*/
static void determineBordersOfWord(char** currentChar,const char* const endStr, Word* word);

/**
* \brief Функция пропускает слово, на которое указывает currentChar
* \param[in/out] currentChar - указатель на указатель первого символа слова
* \detail После использования функции currentChar будет указывать на следующий за словом символ
* \param[in] - endStr - указатель конца поиска
*/
static void skipWord(char** currentChar,const char* const endStr);

int strToWords(char* startStr, char* endStr, Word words[MAX_COUNT_VAR_IN_STRING + 1])
{
	int countOfWords = 0;

	// для каждого символа между границами
	for (char* ptr = startStr; ptr <= endStr; ptr++) 
	{
		// если символ - число, то пропускаем его и смещаем указатель
		if (isdigit(*ptr))
		{
			skipWord(&ptr, endStr);
		}
		// если текущий символ может быть началом слово, то определяем границы слова
		// добавляем словом в список слов и смещаем указатель за слово
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

