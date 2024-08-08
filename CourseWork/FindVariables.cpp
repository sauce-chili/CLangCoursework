#include <string.h>
#include "ctype.h"

#include "Common.h"
#include "FindVariables.h"
#include "StrToWord.h"


int findSingleLetterVariablesInCode( Occurrence startSearch, Occurrence endSearch, Text code, VariableOccurrence singleLetterVars[]) 
{
	return findSingleLetterVariablesInCode({ startSearch, endSearch }, code, singleLetterVars);
}

int findSingleLetterVariablesInCode(const Range searchRange, Text code, VariableOccurrence occurrenceSingleLetterVars[])
{
	// проверяем корректность диапазона, начало должно находится раньше конца
	if (cmpOccurrence(&searchRange.start, &searchRange.end) > 0)
	{
		return 0;
	}
	
	// счетчик вхождений однобуквенной переменной
	int countOccurrence = 0;

	// ищем однобуквенные переменные во всех строках указанного диапазона
	for (int idxString = searchRange.start.verIndex; idxString <= searchRange.end.verIndex; idxString++)
	{
		// указателя на начало и конце границ поиска однобуквенных переменных в текущей строке
		char* startStr = NULL;
		char* endStr = NULL;
		// определяем начало и конец поиска однобувенных переменных в текущей строке,
		// с учетом границ диапазона и коментариев.
		determineBordersOfSearchInLineOfCode(idxString, searchRange, &code, &startStr, &endStr);
		
		// находим все однобуквенные переменные в строке
		Word singleLetterVars[MAX_COUNT_VAR_IN_STRING];
		int countOfSingleLetterVars = findSingleLetterVariablesInString(startStr, endStr, singleLetterVars);

		int i;
		for (i = 0; i < countOfSingleLetterVars; i++) 
		{
			Word* w = &singleLetterVars[i];

			// определяем индекс расположения переменной в строке текста
			char* ptrToStartStr = code.text[idxString];
			int hor = w->start - ptrToStartStr;

			int ver = idxString;

			// получаем строковое предствление слова
			char varName[MAX_VAR_LENGTH];
			wordToStr(w, varName);

			// добавляем в список вхождения однобуквенных переменных
			occurrenceSingleLetterVars[countOccurrence].occurrence.verIndex = ver;
			occurrenceSingleLetterVars[countOccurrence].occurrence.horIndex = hor;
			strcpy_s(occurrenceSingleLetterVars[countOccurrence].name, varName);

			countOccurrence++;
		}
	}

	return countOccurrence;
}

int findSingleLetterVariablesInString(char* startStr, char* endStr, Word singleLetterVarsInString[])
{
	// проверяем корректность заданных границ поиска
	if (startStr == NULL || endStr == NULL || singleLetterVarsInString == NULL || startStr > endStr) 
	{
		return 0; // поиск выполнить невозможно
	}

	// разбиваем строку в указанных границах на слова
	Word words[MAX_COUNT_VAR_IN_STRING];
	int countWords = strToWords(startStr, endStr, words);

	if(countWords == 0)
	{
		return 0;
	}

	// проверяем каждое слово
	int count = 0;
	for (int i = 0; i < countWords; i++)
	{
		// флаг, сигнализирующий о том является слово оператором(while, if, for и тд...) или функцией
		int wordIsNotFunctionOrOperator = ! isOperatorOrFunction(&words[i], endStr);
		// вычисляем длину слова
		int wordLen = getWordLength(&words[i]);
		int isSingleLetterWord = wordLen == 1;

		// если слово не оператор или функция и однобуквенное, то добавляем в список однобуквенных переменных
		if (wordIsNotFunctionOrOperator && isSingleLetterWord)
		{
			singleLetterVarsInString[count] = words[i];
			count++;
		}
	}

	return count;
}