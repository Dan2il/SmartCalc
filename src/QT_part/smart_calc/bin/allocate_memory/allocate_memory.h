/*!
 * \file allocate_memory.h
 */

#ifndef BIN_ALLOCATE_MEMORY_H
#define BIN_ALLOCATE_MEMORY_H

// #include <malloc.h>
#include <stdlib.h>

#include "../processing_errors/processing_errors.h"

/*!
 * \brief GetMemory Функция-обертка для выделения памяти.
 * \param errors переменная, для сохранения ошибки, в случае ее выявления
 * \param allocate_size количество обьектов для выделения
 * \param size_type размер типа, для которого выделяется память
 * \return Возвращает указатель void указывающий на первый элемент выделенного
 * участка памяти
 */
void *GetMemory(ErrorsType *errors, int allocate_size, int size_type);

/*!
 * \brief CheckArgumentsForGetMemory Проверяет корректность поданных в GetMemory
 * данных
 */
ErrorsType CheckArgumentsForGetMemory(int allocate_size, int size_type);

#endif
