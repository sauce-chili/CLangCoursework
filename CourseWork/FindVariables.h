#pragma once

#include "Common.h"

/*
	\brief ������� ���� ������������� ���������� � �������� ��������� ������

	\param[in] searchRange - ��������, ������ �������� �������������� �����(������� ������������)
	\param[in] code - ��� ���������
	\param[out] - singleLetterVarsInString - ������ ������������� ����������, ����������� � �������� ���������
	\return - ����������� ������������� ����������
 */
int findSingleLetterVariablesInCode(const Range searchRange, Text code, VariableOccurrence singleLetterVars[]);

// ���������� ������� ����������� ��� ������ ������, ���������� �����
/*
	\brief ������� ���� ������������� ���������� � �������� ��������� ������
	\details ������� ������������ ��� ������� ������� int findSingleLetterVariablesInCode(const Range searchRange, Text code, VariableOccurrence singleLetterVars[]) �� ������.

	\param[in] searchRange - ��������, ������ �������� �������������� �����(������� ������������)
	\param[in] startSearch - ������� ������ ������
	\param[in] endSearch - ������� ����� ������
	\param[in] code - ��� ���������
	\param[out] - singleLetterVarsInString - ������ ������������� ����������, ����������� � �������� ���������
	\return - ����������� ������������� ����������
 */
int findSingleLetterVariablesInCode(
	Occurrence startSearch,Occurrence endSearch,
	Text code, VariableOccurrence singleLetterVars[]);

/*
	\brief ������� ���� ������������� ���������� � �������� ���������

	\param[in] startStr - ������ ������
	\param[in] endStr - ���� ������
	\param[out] - singleLetterVarsInString - ������ ������������� ���������� ������������ � �����
	\return - ����������� ������������� ����������
 */
int findSingleLetterVariablesInString(
	char* startStr, char* endStr,
	Word singleLetterVarsInString[]
);