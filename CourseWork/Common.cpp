#include "Common.h"
#include <cstring>

/**
 * Функция опеределяет является ли слово оператором или функцией
 * \details Функция ищет первый после конца слова символ не равный пробелы, табу или `)`.
 * Если этот символ равен `(`, то считаем, что слово это функциф или оператор вроде while, if, swithc и тд
 * \param[in] - word - слово
 * \param[in] - конец строки
 */
int isOperatorOrFunction(const Word* word, const char* const endStr)
{
	char* cur = word->end + 1;
	while (cur != endStr && (*cur == ' ' || *cur == '\t' || *cur == ')'))
	{
		cur++;
	}

	return *cur == '(';
}

/**
 * Функция выполняет поиск коментария в строке.
 *
 * \param [in] str - указатель, с которого будет начинатся поиск.

 * \return Указатель на позицию коментария в строке или NULL, если коментарий не найден.
 */
char* findOneLineCommentInString(char str[])
{
	return strstr(str, "//");
}

/*
 *	\brief Функция определяющая границы поиска в строке кода.
 *	\details Функция определяет границы поиска с учётом наличия коментариев к коде и границ заданного поиск.
 *	Если текущая строка совпадает с range.start.verInd, то левая граница принимается равной range.start.horInd, если коментарий не расположен ранее,
 *	eсли текущая строка совпадает с range.end.verind, то правая граница принимается равной range.end.horInd, если коментарий не расположен ранее,
 *	во всех остальный строка между range.start и range.end левая граница будет равна с первому символу строки,
 *  а правая концу строки или началу коментария.
 *
 *	\param[in] idxCurrantStr - первое вхождения.
 *	\param[in] searchRange - колличество строк в code.
 *  \param[in] code - текст программы.
 *	\param[out] startPtr - указатель на начало поиска.
 *  \param[out] endPtr - указатель на конец поиска.
 */
void determineBordersOfSearchInLineOfCode(int idxCurrentStr, Range range, Text* code, char** startSearch, char** endSearch)
{
	// Определяем начальную позицию поиска в строке: если строка является началом указанного дипазона,
	// то выбираем началом поиска позицию указанную в диапазоне, если строка не начало диапазона,
	// то принимаем за начало поиска в строке начало текущей строке
	*startSearch = &(idxCurrentStr == range.start.verIndex ?
		code->text[idxCurrentStr][range.start.horIndex] : code->text[idxCurrentStr][0]);

	// пытаемся найти позицию коментария в строке
	char* ptrToStartCommnet = findOneLineCommentInString(*startSearch);

	int len = strlen(code->text[idxCurrentStr]);

	// Определяем конечную позицию поиска: если в строке найден коментарий, коцечная позиция равна началу коментария,
	// если нет то концу строки
	*endSearch = ptrToStartCommnet != NULL ? ptrToStartCommnet : &code->text[idxCurrentStr][len];

	// если текущая строка является концом диапазона и назначенные конец ранее конец поиска расположен дальше,
	// чем указанный в конце диапазона, то назначаем концом поиска позицию указанную в диапазоне
	int idxRightBorder = *endSearch - code->text[idxCurrentStr];
	if (idxCurrentStr == range.end.verIndex && (range.end.horIndex < idxRightBorder)) 
	{
		*endSearch = &code->text[idxCurrentStr][range.end.horIndex];
	}
}

/**
 * Определяет первое вхождение заданной симметричной пары токенов.
 * 
 * \details "Симметричной" парой называется пара,между позициями символов которой
 * расположено одинаковое кол-во открывающих и закрывающих токенов
 * \param[in] - openig - открывающий токен
 * \param[in] - closing - закрывающий токен
 * \param[in] - searchRange - диапазон поиска токенов
 * \param[in] - code - код программы
 * \param[out] - opennigOccurrence - положение открывающего токена
 * \param[out] - closingOccurrence - положение закрывающего токена
 * \return 0 - если удалось найти токены и диапазон корректен, -1 если невозможно найти симметричную пару токенов
 * т.е открывающих токенов больше чем закрывающих
 */
int determineOccuranceOfOpeningAndClosingToken(
	const char openig[],
	const char closing[],
	Range searchRange,
	Text* code,
	Occurrence* opennigOccurrence,
	Occurrence* closingOccurrence
) 
{
	// проверяем не равны ли открывающий и закрывающий токен
	if (strcmp(openig, closing) == 0) 
	{
		return ERROR_RESULT;
	}

	int countOpenningToken = 0;
	int countClosingToken = 0;

	// флаг, сигнализирующие о том, были ли найдены токены
	int openigOccurrenceWasFound = 0;
	int closingOccurrenceWasFound = 0;

	// обрабатываем каждую строкут диапазона 
	for (int idxStr = searchRange.start.verIndex; idxStr <= searchRange.end.verIndex; idxStr++) 
	{
		// указателя на начало и конце границ поиска однобуквенных переменных в текущей строке
		char* startStr = NULL;
		char* endStr = NULL;
		// определяем начало и конец поиска однобувенных переменных в текущей строке,
		// с учетом границ диапазона и коментариев.
		determineBordersOfSearchInLineOfCode(idxStr, searchRange, code, &startStr, &endStr);

		// для каждого открывающего токена в строке, пока они есть с строке или расположена раньше конца диапазона поиска
		for (
			char* ptrToOpeningToken = strstr(startStr, openig);
			ptrToOpeningToken != NULL && ptrToOpeningToken <= endStr;
			ptrToOpeningToken = strstr(ptrToOpeningToken + 1, openig)
			)
		{

			if (! openigOccurrenceWasFound)
			{
				// записываем позицию первого найденного открывающего токена
				opennigOccurrence->verIndex = idxStr;
				opennigOccurrence->horIndex = ptrToOpeningToken - code->text[idxStr];
				openigOccurrenceWasFound = 1;
			}
			// увеличиваем счетчик для каждого найденного открывающего токена, чтобы найти симметрично расположенную пару
			// для первого найденного токена
			countOpenningToken++;
		}

		if (! openigOccurrenceWasFound)
		{
			continue;
		}
		// для каждого закрывающего токена в строке, пока не будет найдена симметричная пара
		// для первого вхождения открывающего токена или не будет достигнут конец границы поиска
		for (
			char* ptrToClosingToken = strstr(startStr, closing);
			ptrToClosingToken != NULL &&
			ptrToClosingToken <= endStr &&
			!closingOccurrenceWasFound;
			ptrToClosingToken = strstr(ptrToClosingToken + 1, closing)
			)
		{
			Occurrence occ = { idxStr, ptrToClosingToken - code->text[idxStr] };
			// проверяем расположен ли закрывающий токен дальше открывающего
			int locatedAfterOpening = cmpOccurrence(opennigOccurrence, &occ) < 0;

			if (locatedAfterOpening)
			{
				countClosingToken++;
				// если найдена симметричная пара для открывающего токена, то записываем его вхождение
				if (countOpenningToken == countClosingToken)
				{
					*closingOccurrence = occ;
					closingOccurrenceWasFound = 1;
				}
			}

		}

		// проверяем удалось для найти первое симметричное вхождение для заданной пары токенов
		if (openigOccurrenceWasFound && closingOccurrenceWasFound) 
		{
			return 0;
		}
	}

	return ERROR_RESULT;
}

/*
* Функция проверяет инициализирован ли экземпляр Occurrence
* \param[in] - occ
* \return 1 - если инициалицирован, 0 если нет
*/
int isInitializedOccurrence(const Occurrence* occ) 
{
	return	occ->verIndex != UNINITED_OCCURRENCE.verIndex &&
			occ->horIndex != UNINITED_OCCURRENCE.horIndex;
}

/*
* Функция проверяет инициализирован ли экземпляр Range
* \param[in] - range
* \return 1 - есил инициалицирован, 0 если нет
*/
int isInitializedRange(const Range* range) 
{
	return	isInitializedOccurrence(&range->start) &&
			isInitializedOccurrence(&range->end);
}

/*
* Функция проверяет инициализирован ли экземпляр LoopOccurrence
* \param[in] - loopOcc
* \return 1 - если инициалицирован, 0 если нет
*/
int isInitializedLoopOccurrence(const LoopOccurrence* loopOcc)
{
	return	isInitializedRange(&loopOcc->body) &&
			isInitializedRange(&loopOcc->header) &&
			loopOcc->type != UNINITED_LOOP_OCCURRENCE.type;
}

/*
 *	\brief Функция позволяет сравнить два вхождения в тексте
 *
 *	\param[in] occ1 - первое вхождения
 *	\param[in] occ2 - колличество строк в code
 *	\return - 0 если вхождения равны; 1 если дальше расположено occ1; -1 - если дальше расположен occ2
 */
int cmpOccurrence(const Occurrence* occ1, const Occurrence* occ2)
{
	if (occ1->verIndex > occ2->verIndex) return 1;
	else if (occ1->verIndex < occ2->verIndex) return -1;
	// vertical indices are equal
	if (occ1->horIndex == occ2->horIndex) return 0;

	if (occ1->horIndex > occ2->horIndex) return 1;
	else return -1;
}

/*
* Функция проверяет находится экземпляр Occurrence в рамках диапазона range(границы включительно)
* \param[in] - range
* \param[in] - occ
* \return 1 - если находится, 0 - если нет
*/
int inRange(const Range* range, const Occurrence* occ) 
{
	int resultCmpWithStartBorder = cmpOccurrence(occ, &range->start);
	int resultCmpWithEndBorder = cmpOccurrence(occ, &range->end);

	return resultCmpWithStartBorder >= 0 && resultCmpWithEndBorder <= 0;
}

/*
* Функция собирает все элементы из srcVarOccurrence, находящиеся в рамках диапазона range, в collector
* \param[in] - range - диапазон в рамках которого должны находится переменные добавялемые в collector
* \param[in] - srcVarOccurrence - массив, внутри которого будет происходить поиск элементов принадлежащих range
* \param[in] - countOfVarOccurrences - колличество элементов в srcVarOccurrence
* \param[out] - collector - приёмкник
* \return колличество элементов, добавленных в collector
*/
int collectVariableOccurrenceFromRange(
	const Range* range,
	const VariableOccurrence varOccurrence[],
	int countOfVarOccurrences,
	VariableOccurrence collector[]
)
{
	int count = 0;

	for (int i = 0; i < countOfVarOccurrences; i++) 
	{
		if (inRange(range, &varOccurrence[i].occurrence)) 
		{
			collector[count] = varOccurrence[i];
			count++;
		}
	}

	return count;
}


/*
* Функция проверяет находится экземпляр VariableOccurrence varOcc в массиве arr[]
* \param[in] - varOcc - искомое экземпляр
* \param[in] - arr - массив
* \param[in] - size - размер массива
* \return 1 - если находится, 0 - если нет
*/
int containsInVariableOccurrenceArray(const VariableOccurrence* searchElem, const VariableOccurrence arr[], int size)
{
	for (int i = 0; i < size; i++) 
	{
		VariableOccurrence occ = arr[i];
		int equals = memcmp(&occ, searchElem, sizeof(VariableOccurrence)) == 0;
		if (equals)
		{
			return 1;
		}
	}

	return 0;
}

/*
 * Функция объединяет элементы с общим именем из массивов srcVarOcc1[] и srcVarOcc2[] в массив intersectionByName
 *
 * \param[in] - srcVarOcc1[]
 * \param[in] - sizeSrc1
 * \param[in] - srcVarOcc1[]
 * \param[in] - sizeSrc2
 * \param[out] - intersectionByName - неупорядоченное множество элементов с общим имененем
 */
int intersectVariableOccurrenceByName(
	const VariableOccurrence srcVarOcc1[],
	int sizeSrc1,
	const VariableOccurrence srcVarOcc2[],
	int sizeSrc2,
	VariableOccurrence intersectionByName[]
) 
{
	int count = 0;

	if (sizeSrc1 == 0 || sizeSrc2 == 0) 
	{
		return 0;
	}

	// для каждого вхождения перемнной из первого источника
	for (int i = 0; i < sizeSrc1; i++) 
	{
		// считаем текущей вхождение ни разу совпало ни с каким другим вхождением из второгоисточника по имени
		// и поэтому не было добавлено в список пересечений по именам
		int notAdded = 1;
		// для каждого вхождения переменной из втрого источника
		for (int j = 0; j < sizeSrc2; j++) 
		{
			// сравниваем вхождения переменных из разных источников по именам
			if (strcmp(srcVarOcc1[i].name, srcVarOcc2[j].name) == 0) 
			{
				// если имена совпали и элемент из первого источника ни разу не был добавлен в список пересечений, то добавляем его
				if (notAdded && !containsInVariableOccurrenceArray(&srcVarOcc1[i], intersectionByName, count))
				{
					intersectionByName[count] = srcVarOcc1[i];
					count++;
					notAdded = 0;
				}
				// если имена совпали и элемент из второго источника ни разу не был добавлен в список пересечений, то добавляем его
				if (!containsInVariableOccurrenceArray(&srcVarOcc2[j], intersectionByName, count)) 
				{
					intersectionByName[count] = srcVarOcc2[j];
					count++;
				}
			}
		}
	}

	return count;
}

void sortVariableOccurrencesArrayByOccurrence(VariableOccurrence srcVarOcc[], int size) 
{
	VariableOccurrence temp;
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i; j < size; j++)
		{
			// если предыдущий элемент расположен дальше текущего, то меняем их местами
			if (cmpOccurrence(&srcVarOcc[i].occurrence, &srcVarOcc[j].occurrence) > 0)
			{
				temp = srcVarOcc[i];
				srcVarOcc[i] = srcVarOcc[j];
				srcVarOcc[j] = temp;
			}
		}
	}
}

/**
 * \brief Функция проверяет содержится ли в report элемент record
 *
 * \param [in] record - проверяемый элемент.
 * \param [in] report - массив в котором будет идти поиск.
 * \param [in] size - размер массив.
 *
 * \return Возвращает 1 - если record содержится внутри report
 */
int containsInRepord(const ReportRecord* record,const Report report, int size)
{
	for (int i = 0; i < size; i++) 
	{
		if (cmpReportRecords(record, &report[i]))
		{
			return 1;
		}
	}

	return 0;
}

/*
* Функция сравнивает экземпляры структур record1 и record2
* \param[in] - record1
* \param[in] - record2
* \return 1 если равны, 0 - если нет
*/
int cmpReportRecords(const ReportRecord* record1,const ReportRecord* report2)
{
	if (record1->indexStr != report2->indexStr)
	{
		return 0;
	}

	int namesAreEquals = strcmp(record1->value, report2->value) == 0;

	if (!namesAreEquals)
	{
		return 0;
	}

	return 1;
}

/*
* Функция сравнивает report1 и report2
* \param[in] - report1
* \param[in] - size_report1 -  размер report1
* \param[in] - report2
* \param[in] - size_report2 - размер report2
* \return 1 если равны, 0 - если нет
*/
int cmpReports(struct ReportRecord report1[], int size_report1,
	struct ReportRecord report2[], int size_report2)
{
	if (size_report1 != size_report2)
	{
		return 0;
	}

	int i;
	for (i = 0; i < size_report1; i++)
	{
		if (!cmpReportRecords(&report1[i], &report2[i]))
		{
			return 0;
		}
	}

	return 1;
}