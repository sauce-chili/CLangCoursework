#pragma once

#include "Common.h"

/*
	\brief ������� ��������� ������ �� �����
	\details ����� - ������������������ �������� ��������� ���� �� ����, ���� � ������� "_", ������ ������ �������� ����� �� ����� ���� �����
	����� ������������ ����������� ��������� Word, ��� start - ��� ��������� �� ������ ������ �����, end - �� ���������.

	\param[in] startStr - ��������� �� ������ ������ � ������
	\param[in] endStr - ��������� �� ����� ��������� ������ � ������
	\param[out] - words - ������ ����������� ��������� Word
	\return - ����������� ����
 */
int strToWords(char* startStr, char* endStr, Word words[MAX_COUNT_VAR_IN_STRING+1]);

/*
	\brief ������� ��������� ����� �����

	\param[in] word - �����
	\return - ����� �����
 */
int getWordLength(const Word* word);

/*
	\brief ������� ������������ ��������� Word � ���������� ����
	\details � ����� str ����������� ������ '\0'
	\param[in] word - �����
	\paranp[out] str - ������ � ������� ����� �������� �����
	\return - ����� ������, ��� ����� '\0' � �����
 */
int wordToStr(const Word* word, char str[]);