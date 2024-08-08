#pragma once
#include <cstring>

#define MAX_COUNT_STRING 20
#define MAX_CHAR_IN_STRING 80
#define MAX_COUNT_VAR_IN_STRING (MAX_CHAR_IN_STRING - 4) / 4
#define MAX_COUNT_VAR (MAX_COUNT_VAR_IN_STRING * MAX_COUNT_STRING)
#define MAX_VAR_LENGTH 2 // char + "\0"

#define MAX_COUNT_LOOP (MAX_COUNT_STRING-3)/3 

#define ERROR_RESULT -1

/**
 * Псевдоним, хранящий содержимое текста, представляющие собой двумерный массив char'ов
*/
typedef char TextContent[MAX_COUNT_STRING][MAX_CHAR_IN_STRING];

/**
 * Cтруктура для хранения текста
*/
struct Text
{
	TextContent text;  /**< Содержимое текста */
	int countOfString; /**< Колличество строк в тексте */
};

/**
 * Структура-обертка, для хранения "плохих" переменных
 * 
 * \property indexStr - индекс строки в тексте
 * \property value - имя переменной
 */
struct ReportRecord
{
	int indexStr;
	char value[MAX_CHAR_IN_STRING];
};

typedef ReportRecord Report[MAX_COUNT_VAR];

/**
 * \brief Функция проверяет содержится ли в report элемент record
 *
 * \param [in] record - проверяемый элемент.
 * \param [in] report - массив в котором будет идти поиск.
 * \param [in] size - размер массив.
 * 
 * \return Возвращает 1 - если record содержится внутри report
 */
int containsInRepord(const ReportRecord* record, const Report report, int size);

/**
 * Структура необходимая для хранения позиции элемента в тексте
 * 
 * \property verIndex - вертикальный индекс - индес строки.
 * \property horIndex - горизонтальный индекс - индекс символа в строке.
 * \details UNINITED_OCCURRENCE - константа для обозначения некорректного или неинициализированного экземпляра структуры.
*/
struct Occurrence
{
	int verIndex = -1;
	int horIndex = -1;
} const UNINITED_OCCURRENCE = {-1, -1};

/*
 *	\brief Функция позволяет сравнить два вхождения в тексте
 *
 *	\param[in] occ1 - первое вхождения
 *	\param[in] occ2 - колличество строк в code
 *	\return - 0 если вхождения равны; 1 если дальше расположено occ1; -1 - если дальше расположен occ2
 */
int cmpOccurrence(const Occurrence* occ1, const Occurrence* occ2);

/**
 * Структура представляющая собой диапазон в текст, где start начада диапазона в тексте, end - конец 
 * \property start - вхождения символа начала диапазона
 * \property end - вхождения символа конца диапазона
 * \details UNINITED_RANGE - константа для обозначения некорректного или неинициализированного экземпляра структуры.
 */
struct Range {
	Occurrence start = UNINITED_OCCURRENCE; /**< Начало диапазона*/
	Occurrence end = UNINITED_OCCURRENCE; /**< Конец диапазона*/
} const UNINITED_RANGE = {UNINITED_OCCURRENCE, UNINITED_OCCURRENCE};

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
void determineBordersOfSearchInLineOfCode(int idxCurrentStr, Range range,Text* code, char** startPtr, char** endPtr);

/**
 * Функция выполняет поиск коментария в строке.
 *
 * \param [in] str - указатель, с которого будет начинатся поиск.

 * \return Указатель на позицию коментария в строке или NULL, если коментарий не найден.
 */
char* findOneLineCommentInString(char* str);

/**
 * Структура хранящая вхождение переменной
 * \property name - имя переменной
 * \property occurrence - позиция первого символа переменной в тексте
*/
struct VariableOccurrence {
	char name[MAX_VAR_LENGTH];
	Occurrence occurrence;
};

/**
 * Структура представялющая собой слово
 * \property start - указатель на первый символ в слова
 * \property end - указатель на последний символ в слова
*/
struct Word
{
	char* start = NULL;
	char* end = NULL;
};

typedef Range HeaderOfLoopOccurrence;

typedef Range BodyOfLoopOccurrence;

/**
 * Перечисление типов циклов
 */
enum TYPE_LOOP
{
	WHILE,
	FOR,
	DO_WHILE,
	UNKNOW
};

/**
 * Структура хранящая вхождение цикла в код
 * \propert type - тип цикла
 * \property header - положение заголовка цикла
 * \property body - положение тела цикла
 * \details UNINITED_LOOP_OCCURRENCE - константа для обозначения некорректного или неинициализированного экземпляра структуры.
*/
struct LoopOccurrence
{
	TYPE_LOOP type;
	HeaderOfLoopOccurrence header;
	BodyOfLoopOccurrence body;
} const UNINITED_LOOP_OCCURRENCE = {UNKNOW, UNINITED_RANGE, UNINITED_RANGE};

/**
 * Функция опеределяет является ли слово оператором или функцией
 * \details Функция ищет первый после конца слова символ не равный пробелы, табу или `)`.
 * Если этот символ равен `(`, то считаем, что слово это функциф или оператор вроде while, if, swithc и тд
 * \param[in] - word - слово
 * \param[in] - конец строки
 */
int isOperatorOrFunction(const Word* word, const char* const endStr);

/**
 * Определяет первое вхождение заданной симметричной пары токенов.
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
);

/*
* Функция проверяет инициализирован ли экземпляр Occurrence
* \param[in] - occ
* \return 1 - если инициалицирован, 0 если нет
*/
int isInitializedOccurrence(const Occurrence* occ);

/*
* Функция проверяет инициализирован ли экземпляр Range
* \param[in] - range
* \return 1 - есил инициалицирован, 0 если нет
*/
int isInitializedRange(const Range* range);

/*
* Функция проверяет инициализирован ли экземпляр LoopOccurrence
* \param[in] - loopOcc
* \return 1 - если инициалицирован, 0 если нет
*/
int isInitializedLoopOccurrence(const LoopOccurrence* loopOcc);

/*
* Функция проверяет находится экземпляр Occurrence в рамках диапазона range(границы включительно)
* \param[in] - range
* \param[in] - occ
* \return 1 - если находится, 0 - если нет
*/
int inRange(const Range* range, const Occurrence* occ);

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
	const VariableOccurrence srcVarOccurrence[],
	int countOfVarOccurrences,
	VariableOccurrence collector[]
);

/*
* Функция проверяет находится экземпляр VariableOccurrence varOcc в массиве arr[]
* \param[in] - varOcc - искомое экземпляр
* \param[in] - arr - массив
* \param[in] - size - размер массива
* \return 1 - если находится, 0 - если нет
*/
int containsInVariableOccurrenceArray(const VariableOccurrence* varOcc, const VariableOccurrence arr[], int size);

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
);

/**
* \brief Функция сортирует элементы массива srcVarOcc по удаленности от начала текста
* \param[in/out] - srcVarOcc - массив, который необходиом отсортировать
* \param[in] - size - размер массива
*/
void sortVariableOccurrencesArrayByOccurrence(VariableOccurrence srcVarOcc[], int size);

/*
* Функция сравнивает экземпляры структур record1 и record2
* \param[in] - record1
* \param[in] - record2
* \return 1 если равны, 0 - если нет
*/
int cmpReportRecords(const ReportRecord* record1, const ReportRecord* report2);

/*
* Функция сравнивает report1 и report2
* \param[in] - report1
* \param[in] - size_report1 -  размер report1
* \param[in] - report2
* \param[in] - size_report2 - размер report2
* \return 1 если равны, 0 - если нет
*/
int cmpReports(struct ReportRecord report1[], int size_report1,
				struct ReportRecord report2[], int size_report2);