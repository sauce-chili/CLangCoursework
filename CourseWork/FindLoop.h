#pragma once
#include "Common.h"

#define TYPE_OF_LOOP 3
#define MAX_LEN_KEYWORD_OF_LOOP 6

/**
 * \brief ������� ������� ������������ ��� ������ � ����. ��� ������� ����� ��������� ���: ������ � ����� ��������� � ����.
 * \param[in] searchRange - �������� ������
 * \param[in] code - ��� ���������
 * \param[out] loopsOccurrence - ������ ���� ��������� ������ � ��������� searchRange
 * \return ���-�� ��������� � �������� ���������
 */
int findLoopsOccurrenceInCode(Range searchRange, Text* code, LoopOccurrence loopsOccurrence[MAX_COUNT_LOOP]);

/**
 * \brief ������� ���� � �������� ������ ���� �� �������� ����: while, for, do
 * \param[in] startStr - ��������� �� ������ ������
 * \param[in] endStr - ��������� �� ����� ������
 * \param[out] strTypeLoop - ��������� ������������� ���������� ��������� �����
 * \return ��������� �� ��������� �������� �����
 */
Word* findLoopKeywordInString(char* startStr, char* endStr, char* strTypeLoop = NULL);

/**
* \brief ������� ���� ������������ ��������� � ���� ����� While
* 
* \param[in] range - �������� ������
* \param[in] code - ��� ���������
* \param[out] occurrenceOfWhileLoop - ��������� ����� while � �������� ���������
*/
void findOccurrenceOfWhileLoop(Range range, Text* code, LoopOccurrence* occurrenceOfWhileLoop);

/**
* \brief ������� ���� ������������ ��������� � ���� ����� do-while
*
* \param[in] range - �������� ������
* \param[in] code - ��� ���������
* \param[out] occurrenceOfDoWhileLoop - ��������� ����� do-while � �������� ���������
*/
void findOccurrenceOfDoWhileLoop(Range range, Text* code, LoopOccurrence* occurrenceOfDoWhileLoop);

/**
* \brief ������� ���� ������������ ��������� � ���� ����� for
*
* \param[in] range - �������� ������
* \param[in] code - ��� ���������
* \param[out] occurrenceOfForLoop - ��������� ����� for � �������� ���������
*/
void findOccurrenceOfForLoop(Range range, Text* code, LoopOccurrence* occurrenceOfForLoop);