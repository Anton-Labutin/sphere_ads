//
//  main.cpp
//  Median
//
//  Created by Лабутин Антон Александрович on 27.04.2021.
//

/*
 Поиск медиан

 Медиана — элемент массива, который находился бы в этом массиве после сортировки на среднем месте. При нумерации элементов массива размером N с единицы, номер медианного элемента вычисляется по выражению (N+1)/2.

 Известно, что имеются алгоритмы поиск медианы в массиве с линейной сложностью. Вам предстоит решать эту задачу много раз, поэтому стоило бы уменьшить сложность этой операции.

 Input format

 Первая строка файла содержит число запросов 5 ⩽ N ⩽ 1000000

 Запросы могут быть трёх типов:

 0 X — добавить число X в массив. В массиве может быть произвольное число одинаковых элементов.
 1 X — удалить число X из массива. Удаление несуществующего элемента эквивалентно пустой операции.
 2 — вывести медиану массива.
 Числа X по абсолютной величине не превосходят 109.

 Output format

 По одной строке на каждый запрос типа 2.

 Examples

 Input

 19
 0 1
 0 2
 2
 0 3
 2
 0 4
 2
 0 5
 2
 0 6
 2
 0 7
 2
 1 3
 2
 1 2
 2
 1 2
 2

 Output

 1
 2
 2
 3
 3
 4
 4
 5
 5
 */

#include <iostream>
#include <set>
#include <cassert>

using namespace std;

using ull = unsigned long long;
using ll = long long;


enum COMMAND_TYPE {
	ADD = 0,
    DELETE = 1,
    MEDIAN = 2
};


int
main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t N;
    cin >> N;

    multiset<ll> numbers;
    multiset<ll>::iterator medianIt = numbers.end();
    multiset<ll>::iterator tempIt;

    ll arg;
    ull command;

    for (size_t i = 0; i < N; ++i) {
        cin >> command;

        assert(command < 3);

        switch(command) {
            case ADD :
                cin >> arg;
                numbers.insert(arg);

                if (medianIt != numbers.end()) {
                    if (arg < *medianIt) {
                        if ((numbers.size() & 1) == 0) {
                            --medianIt;
                        }
                    } else {
                        if ((numbers.size() & 1) == 1) {
                            ++medianIt;
                        }
                    }
                } else {
                    medianIt = numbers.find(arg);
                }

                break;

            case DELETE :
                cin >> arg;

                if ((tempIt = numbers.find(arg)) != numbers.end()) {
                	if ((tempIt == medianIt) ||
                        (((numbers.size() & 1) == 1) && (arg > *medianIt)) ||
                        (((numbers.size() & 1) == 0) && (arg <= *medianIt))) {
						if (((numbers.size() & 1) == 1) &&
                        	((arg > *medianIt) || tempIt == medianIt)) {
                            --medianIt;
                        }

                        if (((numbers.size() & 1) == 0) &&
                            ((arg <= *medianIt))) {
                            ++medianIt;
                        }
                    }

                    numbers.erase(tempIt);
                }

                break;

            case MEDIAN :
                if (medianIt != numbers.end()) {
                    cout << *medianIt << endl;
                }

                break;
        }
    }

    return 0;
}
