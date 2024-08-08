#pragma once
#include "Common.h"

#define TYPE_OF_LOOP 3
#define MAX_LEN_KEYWORD_OF_LOOP 6

/**
 * \brief Функция находит расположение все циклов в коде. Для каждого цикла вхождение это: начало и конец заголовка и тела.
 * \param[in] searchRange - диапазон поиска
 * \param[in] code - код программы
 * \param[out] loopsOccurrence - массив всех вхождений циклов в диапазоне searchRange
 * \return кол-во вхождений в заданном диапазоне
 */
int findLoopsOccurrenceInCode(Range searchRange, Text* code, LoopOccurrence loopsOccurrence[MAX_COUNT_LOOP]);

/**
 * \brief Функция ищет в заданной строке одна из ключевые слов: while, for, do
 * \param[in] startStr - указатель на начало поиска
 * \param[in] endStr - указатель на конец поиска
 * \param[out] strTypeLoop - строковое предстваление найденного ключевого слова
 * \return указатель на найденное ключевое слово
 */
Word* findLoopKeywordInString(char* startStr, char* endStr, char* strTypeLoop = NULL);

/**
* \brief Функция ищет расположение заголовка и тела цикла While
* 
* \param[in] range - диапазон поиска
* \param[in] code - код программы
* \param[out] occurrenceOfWhileLoop - вхождение цикла while в заданном диапазоне
*/
void findOccurrenceOfWhileLoop(Range range, Text* code, LoopOccurrence* occurrenceOfWhileLoop);

/**
* \brief Функция ищет расположение заголовка и тела цикла do-while
*
* \param[in] range - диапахон поиска
* \param[in] code - код программы
* \param[out] occurrenceOfDoWhileLoop - вхождение цикла do-while в заданном диапазоне
*/
void findOccurrenceOfDoWhileLoop(Range range, Text* code, LoopOccurrence* occurrenceOfDoWhileLoop);

/**
* \brief Функция ищет расположение заголовка и тела цикла for
*
* \param[in] range - диапахон поиска
* \param[in] code - код программы
* \param[out] occurrenceOfForLoop - вхождение цикла for в заданном диапазоне
*/
void findOccurrenceOfForLoop(Range range, Text* code, LoopOccurrence* occurrenceOfForLoop);