#include "Common.h"
#include <cstring>

/**
 * ������� ����������� �������� �� ����� ���������� ��� ��������
 * \details ������� ���� ������ ����� ����� ����� ������ �� ������ �������, ���� ��� `)`.
 * ���� ���� ������ ����� `(`, �� �������, ��� ����� ��� ������� ��� �������� ����� while, if, swithc � ��
 * \param[in] - word - �����
 * \param[in] - ����� ������
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
 * ������� ��������� ����� ���������� � ������.
 *
 * \param [in] str - ���������, � �������� ����� ��������� �����.

 * \return ��������� �� ������� ���������� � ������ ��� NULL, ���� ���������� �� ������.
 */
char* findOneLineCommentInString(char str[])
{
	return strstr(str, "//");
}

/*
 *	\brief ������� ������������ ������� ������ � ������ ����.
 *	\details ������� ���������� ������� ������ � ������ ������� ����������� � ���� � ������ ��������� �����.
 *	���� ������� ������ ��������� � range.start.verInd, �� ����� ������� ����������� ������ range.start.horInd, ���� ���������� �� ���������� �����,
 *	e��� ������� ������ ��������� � range.end.verind, �� ������ ������� ����������� ������ range.end.horInd, ���� ���������� �� ���������� �����,
 *	�� ���� ��������� ������ ����� range.start � range.end ����� ������� ����� ����� � ������� ������� ������,
 *  � ������ ����� ������ ��� ������ ����������.
 *
 *	\param[in] idxCurrantStr - ������ ���������.
 *	\param[in] searchRange - ����������� ����� � code.
 *  \param[in] code - ����� ���������.
 *	\param[out] startPtr - ��������� �� ������ ������.
 *  \param[out] endPtr - ��������� �� ����� ������.
 */
void determineBordersOfSearchInLineOfCode(int idxCurrentStr, Range range, Text* code, char** startSearch, char** endSearch)
{
	// ���������� ��������� ������� ������ � ������: ���� ������ �������� ������� ���������� ��������,
	// �� �������� ������� ������ ������� ��������� � ���������, ���� ������ �� ������ ���������,
	// �� ��������� �� ������ ������ � ������ ������ ������� ������
	*startSearch = &(idxCurrentStr == range.start.verIndex ?
		code->text[idxCurrentStr][range.start.horIndex] : code->text[idxCurrentStr][0]);

	// �������� ����� ������� ���������� � ������
	char* ptrToStartCommnet = findOneLineCommentInString(*startSearch);

	int len = strlen(code->text[idxCurrentStr]);

	// ���������� �������� ������� ������: ���� � ������ ������ ����������, �������� ������� ����� ������ ����������,
	// ���� ��� �� ����� ������
	*endSearch = ptrToStartCommnet != NULL ? ptrToStartCommnet : &code->text[idxCurrentStr][len];

	// ���� ������� ������ �������� ������ ��������� � ����������� ����� ����� ����� ������ ���������� ������,
	// ��� ��������� � ����� ���������, �� ��������� ������ ������ ������� ��������� � ���������
	int idxRightBorder = *endSearch - code->text[idxCurrentStr];
	if (idxCurrentStr == range.end.verIndex && (range.end.horIndex < idxRightBorder)) 
	{
		*endSearch = &code->text[idxCurrentStr][range.end.horIndex];
	}
}

/**
 * ���������� ������ ��������� �������� ������������ ���� �������.
 * 
 * \details "������������" ����� ���������� ����,����� ��������� �������� �������
 * ����������� ���������� ���-�� ����������� � ����������� �������
 * \param[in] - openig - ����������� �����
 * \param[in] - closing - ����������� �����
 * \param[in] - searchRange - �������� ������ �������
 * \param[in] - code - ��� ���������
 * \param[out] - opennigOccurrence - ��������� ������������ ������
 * \param[out] - closingOccurrence - ��������� ������������ ������
 * \return 0 - ���� ������� ����� ������ � �������� ���������, -1 ���� ���������� ����� ������������ ���� �������
 * �.� ����������� ������� ������ ��� �����������
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
	// ��������� �� ����� �� ����������� � ����������� �����
	if (strcmp(openig, closing) == 0) 
	{
		return ERROR_RESULT;
	}

	int countOpenningToken = 0;
	int countClosingToken = 0;

	// ����, ��������������� � ���, ���� �� ������� ������
	int openigOccurrenceWasFound = 0;
	int closingOccurrenceWasFound = 0;

	// ������������ ������ ������� ��������� 
	for (int idxStr = searchRange.start.verIndex; idxStr <= searchRange.end.verIndex; idxStr++) 
	{
		// ��������� �� ������ � ����� ������ ������ ������������� ���������� � ������� ������
		char* startStr = NULL;
		char* endStr = NULL;
		// ���������� ������ � ����� ������ ������������ ���������� � ������� ������,
		// � ������ ������ ��������� � �����������.
		determineBordersOfSearchInLineOfCode(idxStr, searchRange, code, &startStr, &endStr);

		// ��� ������� ������������ ������ � ������, ���� ��� ���� � ������ ��� ����������� ������ ����� ��������� ������
		for (
			char* ptrToOpeningToken = strstr(startStr, openig);
			ptrToOpeningToken != NULL && ptrToOpeningToken <= endStr;
			ptrToOpeningToken = strstr(ptrToOpeningToken + 1, openig)
			)
		{

			if (! openigOccurrenceWasFound)
			{
				// ���������� ������� ������� ���������� ������������ ������
				opennigOccurrence->verIndex = idxStr;
				opennigOccurrence->horIndex = ptrToOpeningToken - code->text[idxStr];
				openigOccurrenceWasFound = 1;
			}
			// ����������� ������� ��� ������� ���������� ������������ ������, ����� ����� ����������� ������������� ����
			// ��� ������� ���������� ������
			countOpenningToken++;
		}

		if (! openigOccurrenceWasFound)
		{
			continue;
		}
		// ��� ������� ������������ ������ � ������, ���� �� ����� ������� ������������ ����
		// ��� ������� ��������� ������������ ������ ��� �� ����� ��������� ����� ������� ������
		for (
			char* ptrToClosingToken = strstr(startStr, closing);
			ptrToClosingToken != NULL &&
			ptrToClosingToken <= endStr &&
			!closingOccurrenceWasFound;
			ptrToClosingToken = strstr(ptrToClosingToken + 1, closing)
			)
		{
			Occurrence occ = { idxStr, ptrToClosingToken - code->text[idxStr] };
			// ��������� ���������� �� ����������� ����� ������ ������������
			int locatedAfterOpening = cmpOccurrence(opennigOccurrence, &occ) < 0;

			if (locatedAfterOpening)
			{
				countClosingToken++;
				// ���� ������� ������������ ���� ��� ������������ ������, �� ���������� ��� ���������
				if (countOpenningToken == countClosingToken)
				{
					*closingOccurrence = occ;
					closingOccurrenceWasFound = 1;
				}
			}

		}

		// ��������� ������� ��� ����� ������ ������������ ��������� ��� �������� ���� �������
		if (openigOccurrenceWasFound && closingOccurrenceWasFound) 
		{
			return 0;
		}
	}

	return ERROR_RESULT;
}

/*
* ������� ��������� ��������������� �� ��������� Occurrence
* \param[in] - occ
* \return 1 - ���� ���������������, 0 ���� ���
*/
int isInitializedOccurrence(const Occurrence* occ) 
{
	return	occ->verIndex != UNINITED_OCCURRENCE.verIndex &&
			occ->horIndex != UNINITED_OCCURRENCE.horIndex;
}

/*
* ������� ��������� ��������������� �� ��������� Range
* \param[in] - range
* \return 1 - ���� ���������������, 0 ���� ���
*/
int isInitializedRange(const Range* range) 
{
	return	isInitializedOccurrence(&range->start) &&
			isInitializedOccurrence(&range->end);
}

/*
* ������� ��������� ��������������� �� ��������� LoopOccurrence
* \param[in] - loopOcc
* \return 1 - ���� ���������������, 0 ���� ���
*/
int isInitializedLoopOccurrence(const LoopOccurrence* loopOcc)
{
	return	isInitializedRange(&loopOcc->body) &&
			isInitializedRange(&loopOcc->header) &&
			loopOcc->type != UNINITED_LOOP_OCCURRENCE.type;
}

/*
 *	\brief ������� ��������� �������� ��� ��������� � ������
 *
 *	\param[in] occ1 - ������ ���������
 *	\param[in] occ2 - ����������� ����� � code
 *	\return - 0 ���� ��������� �����; 1 ���� ������ ����������� occ1; -1 - ���� ������ ���������� occ2
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
* ������� ��������� ��������� ��������� Occurrence � ������ ��������� range(������� ������������)
* \param[in] - range
* \param[in] - occ
* \return 1 - ���� ���������, 0 - ���� ���
*/
int inRange(const Range* range, const Occurrence* occ) 
{
	int resultCmpWithStartBorder = cmpOccurrence(occ, &range->start);
	int resultCmpWithEndBorder = cmpOccurrence(occ, &range->end);

	return resultCmpWithStartBorder >= 0 && resultCmpWithEndBorder <= 0;
}

/*
* ������� �������� ��� �������� �� srcVarOccurrence, ����������� � ������ ��������� range, � collector
* \param[in] - range - �������� � ������ �������� ������ ��������� ���������� ����������� � collector
* \param[in] - srcVarOccurrence - ������, ������ �������� ����� ����������� ����� ��������� ������������� range
* \param[in] - countOfVarOccurrences - ����������� ��������� � srcVarOccurrence
* \param[out] - collector - ��������
* \return ����������� ���������, ����������� � collector
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
* ������� ��������� ��������� ��������� VariableOccurrence varOcc � ������� arr[]
* \param[in] - varOcc - ������� ���������
* \param[in] - arr - ������
* \param[in] - size - ������ �������
* \return 1 - ���� ���������, 0 - ���� ���
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
 * ������� ���������� �������� � ����� ������ �� �������� srcVarOcc1[] � srcVarOcc2[] � ������ intersectionByName
 *
 * \param[in] - srcVarOcc1[]
 * \param[in] - sizeSrc1
 * \param[in] - srcVarOcc1[]
 * \param[in] - sizeSrc2
 * \param[out] - intersectionByName - ��������������� ��������� ��������� � ����� ��������
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

	// ��� ������� ��������� ��������� �� ������� ���������
	for (int i = 0; i < sizeSrc1; i++) 
	{
		// ������� ������� ��������� �� ���� ������� �� � ����� ������ ���������� �� ���������������� �� �����
		// � ������� �� ���� ��������� � ������ ����������� �� ������
		int notAdded = 1;
		// ��� ������� ��������� ���������� �� ������ ���������
		for (int j = 0; j < sizeSrc2; j++) 
		{
			// ���������� ��������� ���������� �� ������ ���������� �� ������
			if (strcmp(srcVarOcc1[i].name, srcVarOcc2[j].name) == 0) 
			{
				// ���� ����� ������� � ������� �� ������� ��������� �� ���� �� ��� �������� � ������ �����������, �� ��������� ���
				if (notAdded && !containsInVariableOccurrenceArray(&srcVarOcc1[i], intersectionByName, count))
				{
					intersectionByName[count] = srcVarOcc1[i];
					count++;
					notAdded = 0;
				}
				// ���� ����� ������� � ������� �� ������� ��������� �� ���� �� ��� �������� � ������ �����������, �� ��������� ���
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
			// ���� ���������� ������� ���������� ������ ��������, �� ������ �� �������
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
 * \brief ������� ��������� ���������� �� � report ������� record
 *
 * \param [in] record - ����������� �������.
 * \param [in] report - ������ � ������� ����� ���� �����.
 * \param [in] size - ������ ������.
 *
 * \return ���������� 1 - ���� record ���������� ������ report
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
* ������� ���������� ���������� �������� record1 � record2
* \param[in] - record1
* \param[in] - record2
* \return 1 ���� �����, 0 - ���� ���
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
* ������� ���������� report1 � report2
* \param[in] - report1
* \param[in] - size_report1 -  ������ report1
* \param[in] - report2
* \param[in] - size_report2 - ������ report2
* \return 1 ���� �����, 0 - ���� ���
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