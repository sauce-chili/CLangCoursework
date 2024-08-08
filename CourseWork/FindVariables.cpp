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
	// ��������� ������������ ���������, ������ ������ ��������� ������ �����
	if (cmpOccurrence(&searchRange.start, &searchRange.end) > 0)
	{
		return 0;
	}
	
	// ������� ��������� ������������� ����������
	int countOccurrence = 0;

	// ���� ������������� ���������� �� ���� ������� ���������� ���������
	for (int idxString = searchRange.start.verIndex; idxString <= searchRange.end.verIndex; idxString++)
	{
		// ��������� �� ������ � ����� ������ ������ ������������� ���������� � ������� ������
		char* startStr = NULL;
		char* endStr = NULL;
		// ���������� ������ � ����� ������ ������������ ���������� � ������� ������,
		// � ������ ������ ��������� � �����������.
		determineBordersOfSearchInLineOfCode(idxString, searchRange, &code, &startStr, &endStr);
		
		// ������� ��� ������������� ���������� � ������
		Word singleLetterVars[MAX_COUNT_VAR_IN_STRING];
		int countOfSingleLetterVars = findSingleLetterVariablesInString(startStr, endStr, singleLetterVars);

		int i;
		for (i = 0; i < countOfSingleLetterVars; i++) 
		{
			Word* w = &singleLetterVars[i];

			// ���������� ������ ������������ ���������� � ������ ������
			char* ptrToStartStr = code.text[idxString];
			int hor = w->start - ptrToStartStr;

			int ver = idxString;

			// �������� ��������� ������������ �����
			char varName[MAX_VAR_LENGTH];
			wordToStr(w, varName);

			// ��������� � ������ ��������� ������������� ����������
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
	// ��������� ������������ �������� ������ ������
	if (startStr == NULL || endStr == NULL || singleLetterVarsInString == NULL || startStr > endStr) 
	{
		return 0; // ����� ��������� ����������
	}

	// ��������� ������ � ��������� �������� �� �����
	Word words[MAX_COUNT_VAR_IN_STRING];
	int countWords = strToWords(startStr, endStr, words);

	if(countWords == 0)
	{
		return 0;
	}

	// ��������� ������ �����
	int count = 0;
	for (int i = 0; i < countWords; i++)
	{
		// ����, ��������������� � ��� �������� ����� ����������(while, if, for � ��...) ��� ��������
		int wordIsNotFunctionOrOperator = ! isOperatorOrFunction(&words[i], endStr);
		// ��������� ����� �����
		int wordLen = getWordLength(&words[i]);
		int isSingleLetterWord = wordLen == 1;

		// ���� ����� �� �������� ��� ������� � �������������, �� ��������� � ������ ������������� ����������
		if (wordIsNotFunctionOrOperator && isSingleLetterWord)
		{
			singleLetterVarsInString[count] = words[i];
			count++;
		}
	}

	return count;
}