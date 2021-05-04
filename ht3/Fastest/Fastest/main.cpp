//
//  main.cpp
//  Fastest
//
//  Created by Лабутин Антон Александрович on 18.04.2021.
//

/*
 Очень быстрая сортировка

 Уметь сортировать быстро – полезный навык. Стандартные сортировки в языках Си и C++ достаточно быстры и универсальны. К сожалению, их универсальность имеет недостаток: сложность алоритмов этих сортировки составляет O(N log(N)).

 Между тем известно, что для некоторых типов данных имеются и сортировки со сложность по времени O(N).

 Вам и предстоит такую написать.

 Файл, который вы должны послать в тестирующую систему, должен иметь реализацию ровно одной функции. Она должна ничего не вводить и ничего не выводить.


 void fast_sort(unsigned *begin, unsigned *end);

 Требуется, чтобы ваша функция отсортировала массив, заданный аргументами, по возрастанию.

 Вы можете пользоваться временными массивами в динамической памяти, память, занятая этими массивами должна быть освобождена к моменту завершения вашей функции.

 Оценка выставляется по каждому тесту отдельно в зависимости от эффективности вашего алгоритма – чем больше времени будет использовать ваша функция в данном тесте, тем меньше баллов она получит.

 Ваша программа не должна содержать функции main. Пример программы, которую можно использовать при тестировании
 */

#include <iostream>
#include <vector>
#include <utility>


using namespace std;
using ull = unsigned long long;


void
fast_sort(unsigned *begin, unsigned *end)
{
    constexpr unsigned BITS_VAL_CNT = 256;
    constexpr unsigned BITS_PER_BYTE = 8;
    constexpr unsigned MAX_BYTE_VAL = 255;
    constexpr size_t NUM_SIZE = sizeof(unsigned);
    size_t numbersCnt = end - begin;

    unsigned curBitsShift = BITS_PER_BYTE;

    unsigned *sortedNumbers = (unsigned*) calloc(numbersCnt, NUM_SIZE);

    for (size_t byteIdx = 0; byteIdx < NUM_SIZE; ++byteIdx) {
        vector<unsigned> bitsPerByteCnt(BITS_VAL_CNT, 0);
        for (size_t numIdx = 0; numIdx < numbersCnt; ++numIdx) {
            bitsPerByteCnt[(begin[numIdx] >> (curBitsShift - BITS_PER_BYTE)) & MAX_BYTE_VAL] += 1;
        }

        vector<unsigned> posInSortedNumbers(BITS_VAL_CNT, 0);
        for (size_t bitValIdx = 1; bitValIdx < BITS_VAL_CNT; ++bitValIdx) {
            posInSortedNumbers[bitValIdx] = posInSortedNumbers[bitValIdx - 1] +
            	bitsPerByteCnt[bitValIdx - 1];
        }

        for (size_t numIdx = 0; numIdx < numbersCnt; ++numIdx) {
            sortedNumbers[posInSortedNumbers[
                                             (begin[numIdx] >> (curBitsShift - BITS_PER_BYTE)) & MAX_BYTE_VAL
                                             ]++
                          ] = begin[numIdx];
        }

        swap(begin, sortedNumbers);

        curBitsShift += BITS_PER_BYTE;
    }

    free(sortedNumbers);
}


int
main()
{
    unsigned array[] = {3, 1, 4, 1, 5, 9, 2, 6};
    size_t arrSize = 8;
    // unsigned array[] = {135, 216, 317, 193, 345, 211, 330, 417, 219, 333, 666};
    // size_t arrSize = 11;
    //unsigned array[] = {143, 2453, 947, 12, 54835, 223, 545, 6345, 34, 1, 35, 76756, 234, 54653, 99895 , 12, 532432, 2523, 23, 5435, 6522, 7428, 12, 0, 54645, 24, 7667, 123, 81274773, 212434, 5346453, 2421, 52242442, 3783428, 1897328428, 8582, 2785, 113, 56, 2, 545, 2895};
    //size_t arrSize = 42;

    unsigned *end = array + arrSize;

    fast_sort(array, end);

    for (size_t numIdx = 0; numIdx < arrSize; ++numIdx) {
        printf("%d ", array[numIdx]);
    }
    printf("\n");

    return 0;
}
