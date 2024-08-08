#pragma once
#include "Common.h"


// ������ ���������� ���������� ��� ������ � ����������� ����� �������
/*
	\brief ������� ���� ���������� � ������ ���������.
	������ ��������� ���������� �������� ��� ���������� ��������� �� ����� �����

	\param[in] code - ������������� ��� ���������
	\param[in] numberStrings - ����������� ����� � code
	\param[in, out] - ����� � �������� � ���������� � ������ ���������
	\return - ����������� �������
 */
int findBadVariablesNames(const TextContent code, int numberStrings, struct ReportRecord  badVariableReport[MAX_COUNT_STRING]);

/*
	\brief ������� ���� ���������� � ������ ���������.
	������ ��������� ���������� �������� ��� ���������� ��������� �� ����� �����

	\param[in] code - ������������� ��� ���������
	\param[in, out] - ����� � �������� � ���������� � ������ ���������
	\return - ����������� �������
 */
int findBadVariablesNames(const Text code, Report  badVariableReport);

/*
	\brief �������� ��������� ���������� ���������� ����������� ������.

	\param[in] code - ������������� ��� ���������
	\param[in, out] - ��������� ���������� �����
	\return - ����������� ��������� ���������� �����
 */
int findLoopVariables(VariableOccurrence codeVariables[], int countOfCodeVars, Text* code, VariableOccurrence loopVariables[]);