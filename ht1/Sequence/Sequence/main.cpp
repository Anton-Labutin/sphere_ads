//
//  main.cpp
//  Sequence
//
//  Created by Лабутин Антон Александрович on 17.03.2021.
//

/*
Последовательность строк

Последовательность строк формируется следующим образом:

Первая строка состоит из цифры 1.

Каждая из последующих строк формируется из номера строки, записанного в виде последовательности десятичных цифр, за которым дописана предыдущая строка и затем перевёрнутая предыдущая строка.

Вот несколько первых строк:

1
211
3211112
432111122111123
5432111122111123321111221111234
Заметьте, что десятая строка начнётся с символов 10, одиннадцатая — с символов 11 и так далее.

Ваша задача заключается в том, чтобы по заданному номеру строки и номеру её элемента вывести символ, стоящий в ней на указанном месте.

Input format

N M

P1 P2 ... PM

Ограничения:

1⩽N⩽30

1⩽M⩽100000

1⩽Pi⩽length(string).

Нумерация строк и символов в строках начинается с единицы.

Output format

M символов, не разделённых пробелами, соответствующие позициям Pi.

Examples

Input

5 5
2 4 6 8 10
    
Output

42112
*/

#include <iostream>

using std::cin;
using std::cout;
using std::endl;


using ull = unsigned long long;


ull
findCharByPos(ull pos, ull currStrNum)
{
    if (currStrNum > 9) {
        if (pos > 1) {
            ull strLen = (1ull << currStrNum) - 2ull + (1ull << (currStrNum - 9));

            if (pos <= ((strLen + 1) >> 1)) {
                return findCharByPos(pos - 2, currStrNum - 1);
            } else {
                return findCharByPos(strLen - pos - 1, currStrNum - 1);
            }
        } else {
            return (pos == 0) ? (currStrNum / 10) : (currStrNum % 10);
        }
    } else {
        if (pos) {
            ull strLen = (1ull << currStrNum) - 1;

            if (pos <= (strLen >> 1)) {
                return findCharByPos(pos - 1, currStrNum - 1);
            } else {
                return findCharByPos(strLen - pos - 1, currStrNum - 1);
            }
        } else {
            return currStrNum;
        }
    }
}


int
main()
{
    int N, M;
    cin >> N >> M;

    int currP;
    while (M--) {
        cin >> currP;
        cout << findCharByPos(currP - 1, N);
    }
    cout << endl;

    return 0;
}
