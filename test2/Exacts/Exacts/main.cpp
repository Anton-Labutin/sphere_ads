//
//  main.cpp
//  Exacts
//
//  Created by Лабутин Антон Александрович on 15.04.2021.
//

/*
 Точные суммы

 Умеете ли вы быстро искать нужное? На вход программы подаётся массив V размером 10⩽N⩽100000 целых чисел, каждое из которых лежит в диапазоне от -109 до 109 и 1⩽M⩽100000 образцов. Для каждого образца требуется определить, существует ли такая пара чисел, принадлежащих массиву, которая даёт в сумме ровно значение образца.

 Input format

 N M

 V1

 V2

 ...

 VN

 P1

 P2

 ...

 PM

 Output format

 Требуется вывести ровно M строк. Если не существует такой пары чисел в массиве, сумма которых равна Pi, то нужно вывести строку Not found. Если же такая пара существует, нужно её вывести в порядке неубывания. Если таких пар несколько, вывести ту из возможных пар, первый элемент которой наименьший из всех возможных.

 Examples

 Input

 10 4
 2
 3
 5
 6
 4
 7
 4
 1
 2
 4
 13
 14
 4
 18

 Output

 6 7
 Not found
 1 3
 Not found

 */


#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int
main()
{
    size_t N;
    size_t M;

    scanf("%zu%zu", &N, &M);

    vector<int> numbers(N);
    for (size_t i = 0; i < N; ++i) {
        scanf("%d", &numbers[i]);
    }

    sort(numbers.begin(), numbers.end());

    int query;
    bool isFound = false;

    for (size_t i = 0; i < M; ++i) {
        scanf("%d", &query);

        size_t left = 0;
        size_t right = numbers.size() - 1;
        while (left != right) {
            long long sum = numbers[left] + numbers[right];
            if (sum < query) {
                ++left;
            } else {
                if (sum > query) {
                    --right;
                } else {
                    isFound = true;
                    break;
                }
            }
        }

        if (isFound) {
            printf("%d %d\n", numbers[left], numbers[right]);
            isFound = false;
        } else {
            printf("Not found\n");
        }
    }

    return 0;
}
