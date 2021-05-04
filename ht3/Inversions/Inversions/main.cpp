//
//  main.cpp
//  Inversions
//
//  Created by Лабутин Антон Александрович on 08.04.2021.
//

/*
 Инверсии

 Известно, что сложность сортировки может определяться числом инверсий — пар элементов последовательности, расположенных не в надлежащем порядке.
 Например, в последовательности {4,5,1,2}, которую нужно упорядочить по неубыванию, имеются следующие пары, образующие инверсии: (4,1), (4,2), (5,1), (5,2).
 Требуется установить, а сколько же инверсий в заданной последовательности длины N, которую нужно упорядочить по неубыванию. Имеется не более 10000000 целых чисел, каждое из которых лежит в диапазоне от -1000000000 до 1000000000.

 Input format
 N
 A1
 A2
 ...
 AN

 Output format
 Количество инверсий в последовательности

 Examples

 Input
 10
 -19
 -43
 -95
 -31
 71
 -59
 -15
 -85
 98
 -22

 Output
 19
 */

#include <iostream>
#include <vector>

using namespace std;

using ull = unsigned long long;


ull
merge(vector<int>& numbers, vector<int>& numbersCopy, size_t lIdx, size_t avgIdx, size_t rIdx)
{
    size_t left = lIdx;
    size_t right = avgIdx;
    size_t result = 0;

    ull numOfInv = 0;

    while (left < avgIdx && right < rIdx) {
        if (numbers[left] <= numbers[right]) {
            numbersCopy[result++] = numbers[left++];
        } else {
            numbersCopy[result++] = numbers[right++];
            numOfInv += avgIdx - left;
        }
    }

    while (left < avgIdx) {
        numbersCopy[result++] = numbers[left++];
    }

    while (right < rIdx) {
        numbersCopy[result++] = numbers[right++];
    }

    for (size_t copy = lIdx; copy < rIdx; ++copy) {
        numbers[copy] = numbersCopy[copy - lIdx];
    }

    return numOfInv;
}


ull
calcNumOfInv(vector<int> &numbers, vector<int> &numbersCopy, size_t lIdx, size_t rIdx)
{
    ull numOfInv = 0;

    if (rIdx <= lIdx + 1) {
        return numOfInv;
    }

    size_t avgIdx = (lIdx + rIdx) / 2;

    numOfInv += calcNumOfInv(numbers, numbersCopy, lIdx, avgIdx);
    numOfInv += calcNumOfInv(numbers, numbersCopy, avgIdx, rIdx);

    numOfInv += merge(numbers, numbersCopy, lIdx, avgIdx, rIdx);

    return numOfInv;
}


int
main()
{
    unsigned N;
    cin >> N;

    vector<int> numbers(N);
    for (size_t i = 0; i < numbers.size(); ++i) {
        cin >> numbers[i];
    }

    vector<int> numbersCopy(numbers.size());

    cout << calcNumOfInv(numbers, numbersCopy, 0, numbers.size()) << endl;

    return 0;
}
