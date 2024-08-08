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
	// �������� ������������ ���������, ����� ������ ��������� ������ ������
	if (cmpOccurrence(&searchRange.end, &searchRange.start) < 0)
	{
		return 0;
	}

	// ���-�� ��������� ��������� ������
	int countOccurrence = 0;

	// ��� ������ ������ � ���������
	int idxString;
	for (idxString = searchRange.start.verIndex; idxString <= searchRange.end.verIndex; idxString++)
	{
		// ��������� �� ������ � ����� ������ ������ ������������� ���������� � ������� ������
		char* startStr = NULL;
		char* endStr = NULL;
		// ���������� ������ � ����� ������ ������������ ���������� � ������� ������,
		// � ������ ������ ��������� � �����������.
		determineBordersOfSearchInLineOfCode(idxString, searchRange, code, &startStr, &endStr);

		// ���� �������� ����� ����� � ������
		char strTypeLoop[MAX_LEN_KEYWORD_OF_LOOP];
		const Word* keywordOfLoop = findLoopKeywordInString(startStr, endStr, strTypeLoop);
		// ���� �������� ����� �� �������, �� ��������� � ��������� ������
		if (keywordOfLoop == NULL) continue;

		// ���������� �������� ������ ��������� �����
		int idxFirstLetterOfKeyword = keywordOfLoop->start - code->text[idxString];
		Range searchLoopRange = { {idxString, idxFirstLetterOfKeyword}, searchRange.end };

		// � ����������� �� ���� ����� �������� �������������� ������� ��� ���������� ��������� �����
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
		
		// ��������� ������� �� ����� ��������� �����
		if (isInitializedLoopOccurrence(&loopOcc))
		{
			*loopsOccurrence = loopOcc;
			// ���������� ��� ��������� ������ �� ������ �����: ��������� ��� ����, ����� �� ��������� �������� ������ ������ ���� �� ���������
			Occurrence newSearchStart = cmpOccurrence(&loopOcc.body.end, &loopOcc.header.end) > 0 ? loopOcc.body.end : loopOcc.header.end;
			searchRange.start = newSearchStart;
			// ��������� ������� ������
			idxString = newSearchStart.verIndex;
			
			countOccurrence++;
			loopsOccurrence++;
			// �������� ����� ��������� � ���� ���������� ����� ������
			countOccurrence += findLoopsOccurrenceInCode(loopOcc.body, code, loopsOccurrence);
		}
	}

	return countOccurrence;
}

Word* findLoopKeywordInString(char* startStr, char* endStr, char* strTypeLoop)
{
	// ��������� ������ �� �����
	Word words[MAX_COUNT_VAR_IN_STRING];
	int countWords = strToWords(startStr, endStr, words);

	// ���� � ������ �������� �����
	for (int i = 0; i < countWords; i++)
	{
		Word* w = &words[i];

		// ���� ����� ����� ������ ������������ ��������� ����� ��������� �����,
		// �� ��������� � ���������� �����
		int len = getWordLength(w);
		if (len >= MAX_LEN_KEYWORD_OF_LOOP) continue;

		// �������� ��������� ������������ �����
		char word[MAX_LEN_KEYWORD_OF_LOOP];
		wordToStr(w, word);

		// ��������� ��������� �� ����� � ����� �� �������� ���� �����
		for (int type = IDX_WHILE; type <= IDX_DO_WHILE; type++)
		{
			if (strcmp(word, LOOP_KEY_WORDS[type]) == 0)
			{
				// ���� ��������� ������� � ������� ������������� ��������� �����,
				// �� �������� ��� � ���������� ������
				if (strTypeLoop != NULL)
				{
					strncpy_s(strTypeLoop, len + 1, w->start, len);
				}
				// ���������� ��������� �� ��������� ������� �����
				return w;
			}
		}
	}

	return NULL;
}

void findOccurrenceOfWhileLoop(Range range, Text* code, LoopOccurrence* occurrenceOfWhileLoop) 
{

	// ����������� �������� ������������ ���������
	HeaderOfLoopOccurrence header;
	int headerWasFound = determineOccuranceOfOpeningAndClosingToken("(", ")", range, code, &header.start, &header.end);

	if (headerWasFound == ERROR_RESULT) 
	{
		return;
	}

	// ���������� �������� ���������� ����
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
	// ����������� �������� ������������ ���������
	HeaderOfLoopOccurrence header;
	int headerWasFound = determineOccuranceOfOpeningAndClosingToken("(", ")", range, code, &header.start, &header.end);

	if (headerWasFound == ERROR_RESULT) 
	{
		*occurrenceOfForLoop = UNINITED_LOOP_OCCURRENCE;
		return;
	}

	// ���������� �������� ���������� ����
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
	// ���������� �������� ���������� ����
	BodyOfLoopOccurrence body;
	int bodyWasFound = determineOccuranceOfOpeningAndClosingToken("{", "}", range, code, &body.start, &body.end);

	if (bodyWasFound == ERROR_RESULT) 
	{
		return;
	}

	Range rangeSearchHeader = { body.end, range.end };
	// ����������� �������� ������������ ���������
	HeaderOfLoopOccurrence header;
	int headerWasFound = determineOccuranceOfOpeningAndClosingToken("(", ")", rangeSearchHeader, code, &header.start, &header.end);

	if (headerWasFound == ERROR_RESULT)
	{
		return;
	}

	occurrenceOfDoWhileLoop->header = header;
	occurrenceOfDoWhileLoop->body = body;
}