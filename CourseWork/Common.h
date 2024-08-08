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
 * ���������, �������� ���������� ������, �������������� ����� ��������� ������ char'��
*/
typedef char TextContent[MAX_COUNT_STRING][MAX_CHAR_IN_STRING];

/**
 * C�������� ��� �������� ������
*/
struct Text
{
	TextContent text;  /**< ���������� ������ */
	int countOfString; /**< ����������� ����� � ������ */
};

/**
 * ���������-�������, ��� �������� "������" ����������
 * 
 * \property indexStr - ������ ������ � ������
 * \property value - ��� ����������
 */
struct ReportRecord
{
	int indexStr;
	char value[MAX_CHAR_IN_STRING];
};

typedef ReportRecord Report[MAX_COUNT_VAR];

/**
 * \brief ������� ��������� ���������� �� � report ������� record
 *
 * \param [in] record - ����������� �������.
 * \param [in] report - ������ � ������� ����� ���� �����.
 * \param [in] size - ������ ������.
 * 
 * \return ���������� 1 - ���� record ���������� ������ report
 */
int containsInRepord(const ReportRecord* record, const Report report, int size);

/**
 * ��������� ����������� ��� �������� ������� �������� � ������
 * 
 * \property verIndex - ������������ ������ - ����� ������.
 * \property horIndex - �������������� ������ - ������ ������� � ������.
 * \details UNINITED_OCCURRENCE - ��������� ��� ����������� ������������� ��� ��������������������� ���������� ���������.
*/
struct Occurrence
{
	int verIndex = -1;
	int horIndex = -1;
} const UNINITED_OCCURRENCE = {-1, -1};

/*
 *	\brief ������� ��������� �������� ��� ��������� � ������
 *
 *	\param[in] occ1 - ������ ���������
 *	\param[in] occ2 - ����������� ����� � code
 *	\return - 0 ���� ��������� �����; 1 ���� ������ ����������� occ1; -1 - ���� ������ ���������� occ2
 */
int cmpOccurrence(const Occurrence* occ1, const Occurrence* occ2);

/**
 * ��������� �������������� ����� �������� � �����, ��� start ������ ��������� � ������, end - ����� 
 * \property start - ��������� ������� ������ ���������
 * \property end - ��������� ������� ����� ���������
 * \details UNINITED_RANGE - ��������� ��� ����������� ������������� ��� ��������������������� ���������� ���������.
 */
struct Range {
	Occurrence start = UNINITED_OCCURRENCE; /**< ������ ���������*/
	Occurrence end = UNINITED_OCCURRENCE; /**< ����� ���������*/
} const UNINITED_RANGE = {UNINITED_OCCURRENCE, UNINITED_OCCURRENCE};

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
void determineBordersOfSearchInLineOfCode(int idxCurrentStr, Range range,Text* code, char** startPtr, char** endPtr);

/**
 * ������� ��������� ����� ���������� � ������.
 *
 * \param [in] str - ���������, � �������� ����� ��������� �����.

 * \return ��������� �� ������� ���������� � ������ ��� NULL, ���� ���������� �� ������.
 */
char* findOneLineCommentInString(char* str);

/**
 * ��������� �������� ��������� ����������
 * \property name - ��� ����������
 * \property occurrence - ������� ������� ������� ���������� � ������
*/
struct VariableOccurrence {
	char name[MAX_VAR_LENGTH];
	Occurrence occurrence;
};

/**
 * ��������� �������������� ����� �����
 * \property start - ��������� �� ������ ������ � �����
 * \property end - ��������� �� ��������� ������ � �����
*/
struct Word
{
	char* start = NULL;
	char* end = NULL;
};

typedef Range HeaderOfLoopOccurrence;

typedef Range BodyOfLoopOccurrence;

/**
 * ������������ ����� ������
 */
enum TYPE_LOOP
{
	WHILE,
	FOR,
	DO_WHILE,
	UNKNOW
};

/**
 * ��������� �������� ��������� ����� � ���
 * \propert type - ��� �����
 * \property header - ��������� ��������� �����
 * \property body - ��������� ���� �����
 * \details UNINITED_LOOP_OCCURRENCE - ��������� ��� ����������� ������������� ��� ��������������������� ���������� ���������.
*/
struct LoopOccurrence
{
	TYPE_LOOP type;
	HeaderOfLoopOccurrence header;
	BodyOfLoopOccurrence body;
} const UNINITED_LOOP_OCCURRENCE = {UNKNOW, UNINITED_RANGE, UNINITED_RANGE};

/**
 * ������� ����������� �������� �� ����� ���������� ��� ��������
 * \details ������� ���� ������ ����� ����� ����� ������ �� ������ �������, ���� ��� `)`.
 * ���� ���� ������ ����� `(`, �� �������, ��� ����� ��� ������� ��� �������� ����� while, if, swithc � ��
 * \param[in] - word - �����
 * \param[in] - ����� ������
 */
int isOperatorOrFunction(const Word* word, const char* const endStr);

/**
 * ���������� ������ ��������� �������� ������������ ���� �������.
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
);

/*
* ������� ��������� ��������������� �� ��������� Occurrence
* \param[in] - occ
* \return 1 - ���� ���������������, 0 ���� ���
*/
int isInitializedOccurrence(const Occurrence* occ);

/*
* ������� ��������� ��������������� �� ��������� Range
* \param[in] - range
* \return 1 - ���� ���������������, 0 ���� ���
*/
int isInitializedRange(const Range* range);

/*
* ������� ��������� ��������������� �� ��������� LoopOccurrence
* \param[in] - loopOcc
* \return 1 - ���� ���������������, 0 ���� ���
*/
int isInitializedLoopOccurrence(const LoopOccurrence* loopOcc);

/*
* ������� ��������� ��������� ��������� Occurrence � ������ ��������� range(������� ������������)
* \param[in] - range
* \param[in] - occ
* \return 1 - ���� ���������, 0 - ���� ���
*/
int inRange(const Range* range, const Occurrence* occ);

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
	const VariableOccurrence srcVarOccurrence[],
	int countOfVarOccurrences,
	VariableOccurrence collector[]
);

/*
* ������� ��������� ��������� ��������� VariableOccurrence varOcc � ������� arr[]
* \param[in] - varOcc - ������� ���������
* \param[in] - arr - ������
* \param[in] - size - ������ �������
* \return 1 - ���� ���������, 0 - ���� ���
*/
int containsInVariableOccurrenceArray(const VariableOccurrence* varOcc, const VariableOccurrence arr[], int size);

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
);

/**
* \brief ������� ��������� �������� ������� srcVarOcc �� ����������� �� ������ ������
* \param[in/out] - srcVarOcc - ������, ������� ���������� �������������
* \param[in] - size - ������ �������
*/
void sortVariableOccurrencesArrayByOccurrence(VariableOccurrence srcVarOcc[], int size);

/*
* ������� ���������� ���������� �������� record1 � record2
* \param[in] - record1
* \param[in] - record2
* \return 1 ���� �����, 0 - ���� ���
*/
int cmpReportRecords(const ReportRecord* record1, const ReportRecord* report2);

/*
* ������� ���������� report1 � report2
* \param[in] - report1
* \param[in] - size_report1 -  ������ report1
* \param[in] - report2
* \param[in] - size_report2 - ������ report2
* \return 1 ���� �����, 0 - ���� ���
*/
int cmpReports(struct ReportRecord report1[], int size_report1,
				struct ReportRecord report2[], int size_report2);