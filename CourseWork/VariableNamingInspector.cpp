#include "VariableNamingInspector.h"
#include "FindVariables.h"
#include "FindLoop.h"

// ���������� ���������� ��� ������� ������ ������� ��������������� �������, ��������� ����� ��� ���� �������� ��� ������ ���������
int findBadVariablesNames(const char code[][80], int numberStrings, ReportRecord badVariableReport[MAX_COUNT_VAR])
{
	Text programText;
	programText.countOfString = numberStrings;
	memcpy(programText.text, code, sizeof(char) * numberStrings * MAX_CHAR_IN_STRING);

	int count = findBadVariablesNames(programText, badVariableReport);

	return count;
}

int findBadVariablesNames(Text code, Report report) 
{
	// ����� ������� ������ ������
	int lenOfLastSrt = strlen(code.text[code.countOfString - 1]);
	Range searchRange = { { 0,0 }, { code.countOfString - 1, lenOfLastSrt } };

	// ���� � ��������� ��������� ��� ������������� ����������
	VariableOccurrence singleLettetVars[MAX_COUNT_VAR];
	int countOfVars = findSingleLetterVariablesInCode(searchRange, code, singleLettetVars);

	// ���� � ��������� ��������� ��� ���������� ������
	VariableOccurrence varsOfLoop[MAX_COUNT_VAR];
	int countOfLoopVars = findLoopVariables(singleLettetVars, countOfVars, &code, varsOfLoop);

	char namesOfLoopsVars[MAX_COUNT_VAR];
	int countOfNamesLoopVars = 0;
	// ���������� ����� ����������, ������� ����� ��������� �������� �� ���� ����.
	// �������� �������������� ����������� �������� ����������, ������� ������������ ��� � ���������, ��� � � ���� ����� 
	for (int i = 0; i < countOfLoopVars; i++) 
	{
		if (strstr(namesOfLoopsVars, varsOfLoop[i].name) == NULL) 
		{
			namesOfLoopsVars[countOfNamesLoopVars] = varsOfLoop[i].name[0];
			countOfNamesLoopVars++;
		}
	}

	// ��������� ������ ������ ����������, ��� �������� ��������� ��������� ReportRecord,
	// ������� �������� ������ ������, ��� �������������� ����������, � ��� ����������.
	int sizeOfReport = 0;
	for (int i = 0; i < countOfVars; i++) 
	{
		// ����, ��������������� � ��� ����������� �� ������� ���������� � ������ ���������� �����
		int isNameOfGoodVar = strstr(namesOfLoopsVars, singleLettetVars[i].name) != NULL;

		if (isNameOfGoodVar) continue;

		ReportRecord r;
		r.indexStr = singleLettetVars[i].occurrence.verIndex;
		strcpy_s(r.value, singleLettetVars[i].name);

		// ���� , ��������������� � ���, ��� ������� ���������� ��� ���� ��������� � ������ ������ ����������,
		// ��������� ���������� ����� ��������� ���� ���� � �� �� ���������� �������������� � ������ ��������� ���
		int isNotAdded = ! containsInRepord(&r, report,sizeOfReport);

		if (isNotAdded) 
		{
			// ��������� � ����� ������ ����������
			report[sizeOfReport] = r;
			sizeOfReport++;
		}
	}

	return sizeOfReport;
}

int findLoopVariables(VariableOccurrence codeVariables[], int countOfCodeVars, Text* code, VariableOccurrence loopVariables[])
{
	Range searchLoopRange = { { 0,0 }, {code->countOfString - 1, strlen(code->text[code->countOfString - 1])} };
	
	// ���� ��������� ���� ������ � ����
	LoopOccurrence loopsOcc[MAX_COUNT_LOOP];
	int countOfLoops = findLoopsOccurrenceInCode(searchLoopRange, code, loopsOcc);

	int  countOfLoopVars = 0;

	for (int i = 0; i < countOfLoops; i++) 
	{
		// ������ ��� �������� ���������� ���������
		VariableOccurrence loopHeaderVar[MAX_COUNT_VAR_IN_STRING];
		int countOfLoopHeadersVar = 0;

		// �.� ��������� ����� f�� ������� �� ���� ������, �� ��� ����� ������������ ��������  
		if (loopsOcc[i].type == TYPE_LOOP::FOR)
		{
			Range headerRange = loopsOcc[i].header;

			int idxStr = headerRange.start.verIndex;
			int idxStartHeaderInStr = headerRange.start.horIndex;
			
			// ���������� ������� ����� ����� �������������
			char* ptrToEndInitializationPart = strstr(code->text[idxStr], ";");
			int idxOfEndInitializationPart = ptrToEndInitializationPart - code->text[idxStr];

			// ���������� ������� ����� ����� �������
			char* ptrToEndConditionPart = strstr(ptrToEndInitializationPart + 1, ";");
			int idxOfEndConditionPart = ptrToEndConditionPart - code->text[idxStr];

			// ��������� ��������, �������� ������ ������������ ���������� ����� �������������
			Range rangeOfPartInizialization = { {idxStr, idxStartHeaderInStr}, {idxStr, idxOfEndInitializationPart} };
			// ��������� ��������, �������� ������ ������������ ���������� ����� ������� 
			Range rangeOfPartCondition = { rangeOfPartInizialization.end, {idxStr, idxOfEndConditionPart} };

			// ���������� ����� ��������� ���������� ����������� ����� �������������
			VariableOccurrence initOccurrences[MAX_COUNT_VAR_IN_STRING];
			int sizeInitOccurrences = collectVariableOccurrenceFromRange(&rangeOfPartInizialization, codeVariables, countOfCodeVars, initOccurrences);

			// ���������� ����� ��������� ���������� ����������� ����� �������
			VariableOccurrence conditionOccurrence[MAX_COUNT_VAR_IN_STRING];
			int sizeConditionOccurrences = collectVariableOccurrenceFromRange(&rangeOfPartCondition, codeVariables, countOfCodeVars, conditionOccurrence);

			// ���������� ��������� ����������, ������� ����������� ����� ������: ������������� � �������, ����� ���������� �� ������� �������
			// ��������� ����������� ���������. ��������� ������ ���� ����� ��������� ��������� ���������� �� ����� ������, ���� ����� ���������� ���������
			countOfLoopHeadersVar = intersectVariableOccurrenceByName(initOccurrences, sizeInitOccurrences,
																			conditionOccurrence, sizeConditionOccurrences, 
																			loopHeaderVar);
			// ������������� ������ ��������� ���� ����� �� ����� ����� �������,
			// �� �� ������� ������� 3-� ����� ����� for - ���� �����
			loopsOcc[i].body.start = rangeOfPartCondition.end;
		}
		else 
		{
			// ���������� ��������� ���������� ���������
			countOfLoopHeadersVar = collectVariableOccurrenceFromRange(&loopsOcc[i].header, codeVariables, countOfCodeVars, loopHeaderVar);
		}
		// ���������� ��������� ���������� ����
		VariableOccurrence loopBodyVar[MAX_COUNT_VAR_IN_STRING];
		int countOfLoopBodyVar = collectVariableOccurrenceFromRange(&loopsOcc[i].body, codeVariables, countOfCodeVars, loopBodyVar);

		// ���������� ��������� ���������� ����� ������� ���������� ��� � ����, ��� � ��������� �����.
		// ����� ���������� �� ������� ������� �������� ����������� �����
		countOfLoopVars += intersectVariableOccurrenceByName(
			loopHeaderVar, countOfLoopHeadersVar,
			loopBodyVar, countOfLoopBodyVar,
			(loopVariables + countOfLoopVars)
		);
	}

	// ��������� ��������� ���������� �� ����������� ��������� �� ������ ������ ��� ��������
	// ������ � ��������� �������
	sortVariableOccurrencesArrayByOccurrence(loopVariables, countOfLoopVars);

	return countOfLoopVars;
}