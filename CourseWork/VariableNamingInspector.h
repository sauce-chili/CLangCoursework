#pragma once
#include "Common.h"


// Данная перегрузка необходима для работы с написанными ранее тестами
/*
	\brief Функция ищет переменные с плохим названием.
	Плохим названием переменной является имя переменной состоящие из одной буквы

	\param[in] code - анализируемый код программы
	\param[in] numberStrings - колличество строк в code
	\param[in, out] - отчет с записями о переменных с плохим названием
	\return - колличество записей
 */
int findBadVariablesNames(const TextContent code, int numberStrings, struct ReportRecord  badVariableReport[MAX_COUNT_STRING]);

/*
	\brief Функция ищет переменные с плохим названием.
	Плохим названием переменной является имя переменной состоящие из одной буквы

	\param[in] code - анализируемый код программы
	\param[in, out] - отчет с записями о переменных с плохим названием
	\return - колличество записей
 */
int findBadVariablesNames(const Text code, Report  badVariableReport);

/*
	\brief Выделяет вхождения переменных являющихся переменными циклов.

	\param[in] code - анализируемый код программы
	\param[in, out] - вхождения переменных цикла
	\return - колличество вхождений переменных цикла
 */
int findLoopVariables(VariableOccurrence codeVariables[], int countOfCodeVars, Text* code, VariableOccurrence loopVariables[]);