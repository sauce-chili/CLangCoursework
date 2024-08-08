#include "Common.h"
#include "FindLoop.h"
#include "StrToWord.h"

static enum IDX_LOOP_KEYWORDS {
	IDX_WHILE,
	IDX_FOR,
	IDX_DO_WHILE
};
static const char LOOP_KEY_WORDS[TYPE_OF_LOOP][MAX_LEN_KEYWORD_OF_LOOP] = {
	"while",
	"for",
	"do"
};
static void(*const LOOP_OCCURRENCE_FINDER[TYPE_OF_LOOP])(Range, Text*, LoopOccurrence*) = {
	findOccurrenceOfWhileLoop,
	findOccurrenceOfForLoop,
	findOccurrenceOfDoWhileLoop
};

int findLoopsOccurrenceInCode(Range searchRange, Text* code, LoopOccurrence loopsOccurrence[MAX_COUNT_LOOP])
{
	// проверка корректности диапазона, конец должен находится дальше начала
	if (cmpOccurrence(&searchRange.end, &searchRange.start) < 0)
	{
		return 0;
	}

	// кол-во найденных вхождений циклов
	int countOccurrence = 0;

	// для каждой строки в диапазоне
	int idxString;
	for (idxString = searchRange.start.verIndex; idxString <= searchRange.end.verIndex; idxString++)
	{
		// указателя на начало и конце границ поиска однобуквенных переменных в текущей строке
		char* startStr = NULL;
		char* endStr = NULL;
		// определяем начало и конец поиска однобувенных переменных в текущей строке,
		// с учетом границ диапазона и коментариев.
		determineBordersOfSearchInLineOfCode(idxString, searchRange, code, &startStr, &endStr);

		// ищем ключевое слово цикла в строке
		char strTypeLoop[MAX_LEN_KEYWORD_OF_LOOP];
		const Word* keywordOfLoop = findLoopKeywordInString(startStr, endStr, strTypeLoop);
		// если ключевое слово не найдено, то переходим в следующей строке
		if (keywordOfLoop == NULL) continue;

		// определяем диапазон поиска вхождения цикла
		int idxFirstLetterOfKeyword = keywordOfLoop->start - code->text[idxString];
		Range searchLoopRange = { {idxString, idxFirstLetterOfKeyword}, searchRange.end };

		// в зависимости от вида цикла вызываем соответсвенную функцию для опредления вхождения цикла
		LoopOccurrence loopOcc;
		for (int type = IDX_WHILE; type <= IDX_DO_WHILE; type++)
		{
			if (strcmp(strTypeLoop, LOOP_KEY_WORDS[type]) == 0) 
			{
				loopOcc.type = (TYPE_LOOP)type;
				LOOP_OCCURRENCE_FINDER[type](searchLoopRange, code, &loopOcc);
				break;
			}
		}
		
		// проверяем удалось ли найти вхождение цикла
		if (isInitializedLoopOccurrence(&loopOcc))
		{
			*loopsOccurrence = loopOcc;
			// определяем что находится дальше от начала текта: заголовок или тело, чтобы на следующей итерации начать искать цикл за найденным
			Occurrence newSearchStart = cmpOccurrence(&loopOcc.body.end, &loopOcc.header.end) > 0 ? loopOcc.body.end : loopOcc.header.end;
			searchRange.start = newSearchStart;
			// обновляем текущую строку
			idxString = newSearchStart.verIndex;
			
			countOccurrence++;
			loopsOccurrence++;
			// начинаем поиск вложенных в тело найденного цикла циклов
			countOccurrence += findLoopsOccurrenceInCode(loopOcc.body, code, loopsOccurrence);
		}
	}

	return countOccurrence;
}

Word* findLoopKeywordInString(char* startStr, char* endStr, char* strTypeLoop)
{
	// разбиваем строки на слова
	Word words[MAX_COUNT_VAR_IN_STRING];
	int countWords = strToWords(startStr, endStr, words);

	// ищем в строке ключевое слово
	for (int i = 0; i < countWords; i++)
	{
		Word* w = &words[i];

		// если длина слова больше максимальной возможной длины ключевого слова,
		// то переходим к следующему слову
		int len = getWordLength(w);
		if (len >= MAX_LEN_KEYWORD_OF_LOOP) continue;

		// получаем строковое предствалени слова
		char word[MAX_LEN_KEYWORD_OF_LOOP];
		wordToStr(w, word);

		// проверяем совпадает ли слово с одним из ключевых слов цикла
		for (int type = IDX_WHILE; type <= IDX_DO_WHILE; type++)
		{
			if (strcmp(word, LOOP_KEY_WORDS[type]) == 0)
			{
				// если требуется вернуть и строкое представление ключевого слова,
				// то копируем его в переданный массив
				if (strTypeLoop != NULL)
				{
					strncpy_s(strTypeLoop, len + 1, w->start, len);
				}
				// возвращаем указатель на найденное ключево слово
				return w;
			}
		}
	}

	return NULL;
}

void findOccurrenceOfWhileLoop(Range range, Text* code, LoopOccurrence* occurrenceOfWhileLoop) 
{

	// опредлеляем диапазон расположения заголовка
	HeaderOfLoopOccurrence header;
	int headerWasFound = determineOccuranceOfOpeningAndClosingToken("(", ")", range, code, &header.start, &header.end);

	if (headerWasFound == ERROR_RESULT) 
	{
		return;
	}

	// определяем диапазон нахождения тела
	Range bodySearchRange = { header.end, range.end };
	BodyOfLoopOccurrence body;
	int bodyWasFound = determineOccuranceOfOpeningAndClosingToken("{", "}", bodySearchRange, code, &body.start, &body.end);

	if (bodyWasFound == ERROR_RESULT) 
	{
		return;
	}

	occurrenceOfWhileLoop->header = header;
	occurrenceOfWhileLoop->body = body;
	
}

void findOccurrenceOfForLoop(Range range, Text* code, LoopOccurrence* occurrenceOfForLoop)
{
	// опредлеляем диапазон расположения заголовка
	HeaderOfLoopOccurrence header;
	int headerWasFound = determineOccuranceOfOpeningAndClosingToken("(", ")", range, code, &header.start, &header.end);

	if (headerWasFound == ERROR_RESULT) 
	{
		*occurrenceOfForLoop = UNINITED_LOOP_OCCURRENCE;
		return;
	}

	// определяем диапазон нахождения тела
	Range bodySearchRange = { header.end, range.end };
	BodyOfLoopOccurrence body;
	int bodyWasFound = determineOccuranceOfOpeningAndClosingToken("{", "}", bodySearchRange, code, &body.start, &body.end);

	if (bodyWasFound == ERROR_RESULT) 
	{
		*occurrenceOfForLoop = UNINITED_LOOP_OCCURRENCE;
		return;
	}

	occurrenceOfForLoop->header = header;
	occurrenceOfForLoop->body = body;
}

void findOccurrenceOfDoWhileLoop(Range range, Text* code, LoopOccurrence* occurrenceOfDoWhileLoop) 
{
	// определяем диапазон нахождения тела
	BodyOfLoopOccurrence body;
	int bodyWasFound = determineOccuranceOfOpeningAndClosingToken("{", "}", range, code, &body.start, &body.end);

	if (bodyWasFound == ERROR_RESULT) 
	{
		return;
	}

	Range rangeSearchHeader = { body.end, range.end };
	// опредлеляем диапазон расположения заголовка
	HeaderOfLoopOccurrence header;
	int headerWasFound = determineOccuranceOfOpeningAndClosingToken("(", ")", rangeSearchHeader, code, &header.start, &header.end);

	if (headerWasFound == ERROR_RESULT)
	{
		return;
	}

	occurrenceOfDoWhileLoop->header = header;
	occurrenceOfDoWhileLoop->body = body;
}