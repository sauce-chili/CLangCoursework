#pragma once

#include "Common.h"

/*
	\brief ‘ункци€ разбивает строку на слова
	\details —лово - последовательность символов состо€ща€ лишь из букв, цифр и символа "_", притом первым символом слова не можеь быть цифра
	—лово представлено экземпл€ром структуры Word, где start - это указатель на первый символ слова, end - на последний.

	\param[in] startStr - указатель на начало поиска в строке
	\param[in] endStr - указатель на конец диапазона поиска в строке
	\param[out] - words - массив экземпл€ров структуры Word
	\return - колличество слов
 */
int strToWords(char* startStr, char* endStr, Word words[MAX_COUNT_VAR_IN_STRING+1]);

/*
	\brief ‘ункци€ вычисл€ет длину слова

	\param[in] word - слово
	\return - длина слова
 */
int getWordLength(const Word* word);

/*
	\brief ‘ункци€ переобразует экземпл€р Word к строковому виду
	\details ¬ конце str добавл€етс€ символ '\0'
	\param[in] word - слово
	\paranp[out] str - строка в которую будет записано слово
	\return - длина строки, без учета '\0' в конце
 */
int wordToStr(const Word* word, char str[]);