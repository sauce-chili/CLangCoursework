#include "VariableNamingInspector.h"
#include "FindVariables.h"
#include "FindLoop.h"

// Перегрузка необхидима для запуска тестов главной высчислительной функции, посколько тесты уже были написаны под данный интерфейс
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
	// задаём диапзон поиска поиска
	int lenOfLastSrt = strlen(code.text[code.countOfString - 1]);
	Range searchRange = { { 0,0 }, { code.countOfString - 1, lenOfLastSrt } };

	// ищём в указанном диапазоне все однобуквенные переменные
	VariableOccurrence singleLettetVars[MAX_COUNT_VAR];
	int countOfVars = findSingleLetterVariablesInCode(searchRange, code, singleLettetVars);

	// ищём в указанном диапазоне все переменные циклов
	VariableOccurrence varsOfLoop[MAX_COUNT_VAR];
	int countOfLoopVars = findLoopVariables(singleLettetVars, countOfVars, &code, varsOfLoop);

	char namesOfLoopsVars[MAX_COUNT_VAR];
	int countOfNamesLoopVars = 0;
	// Записываем имена переменных, который будут считаться хорошими во всем коде.
	// Хорошими однобуквенными переменными называют переменные, которые испольщуются как в заголовке, так и в теле цикла 
	for (int i = 0; i < countOfLoopVars; i++) 
	{
		if (strstr(namesOfLoopsVars, varsOfLoop[i].name) == NULL) 
		{
			namesOfLoopsVars[countOfNamesLoopVars] = varsOfLoop[i].name[0];
			countOfNamesLoopVars++;
		}
	}

	// формируем массив плохих переменных, где хранится экземпялр структуры ReportRecord,
	// которая содердит индекс строки, где использовалась переменная, и имя переменной.
	int sizeOfReport = 0;
	for (int i = 0; i < countOfVars; i++) 
	{
		// флаг, сигнализирующий о том встречалась ли текущая переменная в списке переменных цикла
		int isNameOfGoodVar = strstr(namesOfLoopsVars, singleLettetVars[i].name) != NULL;

		if (isNameOfGoodVar) continue;

		ReportRecord r;
		r.indexStr = singleLettetVars[i].occurrence.verIndex;
		strcpy_s(r.value, singleLettetVars[i].name);

		// флаг , сигнализирующий о том, что текущая переменная уже была добавлена в списко плохих переменных,
		// повторное добавление может проихойти если одна и та же переменная использовалась в строке несколько раз
		int isNotAdded = ! containsInRepord(&r, report,sizeOfReport);

		if (isNotAdded) 
		{
			// добавляем в списо плохих переменных
			report[sizeOfReport] = r;
			sizeOfReport++;
		}
	}

	return sizeOfReport;
}

int findLoopVariables(VariableOccurrence codeVariables[], int countOfCodeVars, Text* code, VariableOccurrence loopVariables[])
{
	Range searchLoopRange = { { 0,0 }, {code->countOfString - 1, strlen(code->text[code->countOfString - 1])} };
	
	// ищем вхождения всех циклов в коде
	LoopOccurrence loopsOcc[MAX_COUNT_LOOP];
	int countOfLoops = findLoopsOccurrenceInCode(searchLoopRange, code, loopsOcc);

	int  countOfLoopVars = 0;

	for (int i = 0; i < countOfLoops; i++) 
	{
		// массив для хранения переменных заголовка
		VariableOccurrence loopHeaderVar[MAX_COUNT_VAR_IN_STRING];
		int countOfLoopHeadersVar = 0;

		// Т.к заголовок цикла fок состоит из трех частей, то его нужно обрабатывать отдельно  
		if (loopsOcc[i].type == TYPE_LOOP::FOR)
		{
			Range headerRange = loopsOcc[i].header;

			int idxStr = headerRange.start.verIndex;
			int idxStartHeaderInStr = headerRange.start.horIndex;
			
			// определяем позицию конца блока инициализации
			char* ptrToEndInitializationPart = strstr(code->text[idxStr], ";");
			int idxOfEndInitializationPart = ptrToEndInitializationPart - code->text[idxStr];

			// определяем позицию конца блока условия
			char* ptrToEndConditionPart = strstr(ptrToEndInitializationPart + 1, ";");
			int idxOfEndConditionPart = ptrToEndConditionPart - code->text[idxStr];

			// формируем диапазон, которому должны принадлежать переменные блока инициализации
			Range rangeOfPartInizialization = { {idxStr, idxStartHeaderInStr}, {idxStr, idxOfEndInitializationPart} };
			// формируем диапазон, которому должны принадлежать переменные блока условия 
			Range rangeOfPartCondition = { rangeOfPartInizialization.end, {idxStr, idxOfEndConditionPart} };

			// определяем какие вхождения переменных принадлежат блоку инициализации
			VariableOccurrence initOccurrences[MAX_COUNT_VAR_IN_STRING];
			int sizeInitOccurrences = collectVariableOccurrenceFromRange(&rangeOfPartInizialization, codeVariables, countOfCodeVars, initOccurrences);

			// определяем какие вхождения переменных принадлежат блоку условия
			VariableOccurrence conditionOccurrence[MAX_COUNT_VAR_IN_STRING];
			int sizeConditionOccurrences = collectVariableOccurrenceFromRange(&rangeOfPartCondition, codeVariables, countOfCodeVars, conditionOccurrence);

			// определяем вхождения переменных, которые принадлежат обоим блокам: инициализации и условия, такие переменные по условию задания
			// считаются переменными заголовка. Формируем массив куда будут добавлены вхождения переменных из обоих блоков, если имена переменных совпадают
			countOfLoopHeadersVar = intersectVariableOccurrenceByName(initOccurrences, sizeInitOccurrences,
																			conditionOccurrence, sizeConditionOccurrences, 
																			loopHeaderVar);
			// устанавливаем начало диапазона тела цикла на конец блока условия,
			// тк по условию задания 3-я часть цикла for - тело цикла
			loopsOcc[i].body.start = rangeOfPartCondition.end;
		}
		else 
		{
			// определяем вхождения переменных заголовка
			countOfLoopHeadersVar = collectVariableOccurrenceFromRange(&loopsOcc[i].header, codeVariables, countOfCodeVars, loopHeaderVar);
		}
		// определяем вхождения переменных тела
		VariableOccurrence loopBodyVar[MAX_COUNT_VAR_IN_STRING];
		int countOfLoopBodyVar = collectVariableOccurrenceFromRange(&loopsOcc[i].body, codeVariables, countOfCodeVars, loopBodyVar);

		// определяем вхождения переменных имена которых присутсвую как в теле, так и заголовке цикла.
		// такие переменных по условию задания являются переменными цикла
		countOfLoopVars += intersectVariableOccurrenceByName(
			loopHeaderVar, countOfLoopHeadersVar,
			loopBodyVar, countOfLoopBodyVar,
			(loopVariables + countOfLoopVars)
		);
	}

	// сортируем вхождения переменных по удаленности вхождения от начала текста для удобства
	// работы с выходными данными
	sortVariableOccurrencesArrayByOccurrence(loopVariables, countOfLoopVars);

	return countOfLoopVars;
}