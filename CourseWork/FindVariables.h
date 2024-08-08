#pragma once

#include "Common.h"

/*
	\brief ‘ункци€ ищет однобуквенные переменные в заданном диапазоне текста

	\param[in] searchRange - диапазон, внутри которого осуществл€етс€ поиск(границы включительно)
	\param[in] code - код программы
	\param[out] - singleLetterVarsInString - массив однобуквенных переменных, наход€щихс€ в заданном диапазоне
	\return - колличество однобуквенных переменных
 */
int findSingleLetterVariablesInCode(const Range searchRange, Text code, VariableOccurrence singleLetterVars[]);

// перегрузка функции необходима€ дл€ работы тестов, написанных ранее
/*
	\brief ‘ункци€ ищет однобуквенные переменные в заданном диапазоне текста
	\details ‘ункци€ используетс€ дл€ запуска функции int findSingleLetterVariablesInCode(const Range searchRange, Text code, VariableOccurrence singleLetterVars[]) на тестах.

	\param[in] searchRange - диапазон, внутри которого осуществл€етс€ поиск(границы включительно)
	\param[in] startSearch - позици€ начала поиска
	\param[in] endSearch - позици€ конца поиска
	\param[in] code - код программы
	\param[out] - singleLetterVarsInString - массив однобуквенных переменных, наход€щихс€ в заданном диапазоне
	\return - колличество однобуквенных переменных
 */
int findSingleLetterVariablesInCode(
	Occurrence startSearch,Occurrence endSearch,
	Text code, VariableOccurrence singleLetterVars[]);

/*
	\brief ‘ункци€ ищет однобуквенные переменные в заданной подстроке

	\param[in] startStr - начала строки
	\param[in] endStr - конц строки
	\param[out] - singleLetterVarsInString - массив однобуквенных переменных содержащихс€ в сроке
	\return - колличество однобуквенных переменных
 */
int findSingleLetterVariablesInString(
	char* startStr, char* endStr,
	Word singleLetterVarsInString[]
);