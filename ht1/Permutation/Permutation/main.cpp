//
//  main.cpp
//  Permutation
//
//  Created by Лабутин Антон Александрович on 15.03.2021.
//

/*
Перестановки

Как известно, из множества из N различных предметов можно сделать N! различных перестановок.

Если предметы можно сравнивать между собой, то перестановки можно перенумеровать в лексикографическом порядке. Например, перестановки множества {1,2,3} будут идти в следующем порядке: {1,2,3}, {1,3,2}, {2,1,3}, {2,3,1}, {3,1,2}, {3,2,1}.

Таким образом, все перестановки множества различных элементов можно пронумеровать от 1 до N!.

В нашей задаче мы будем переставлять элементы из множества натуральных чисел от 1 до N.

Input format

На вход программы подаётся два числа — количество предметов в перестановке 2⩽N⩽20 и номер перестановки 1⩽M⩽2×1018.

Output format

Вывести через пробел элементы перестановки, имеющей номер M.

Examples

Input

5 
120
    
Output

5 4 3 2 1
    
Input

10 
73238    
    
Output

1 3 9 6 8 4 7 2 10 5
*/

#include <iostream>
#include <vector>

using std::vector;
using std::ostream;
using std::cin;
using std::cout;
using std::endl;

using ULL = unsigned long long;


ostream&
operator << (ostream& out, vector<unsigned> &v)
{
    for (const auto& v_el : v) {
        out << v_el << " ";
    }

    out << endl;

    return out;
}


unsigned
findNotUsedDigit(unsigned currDigit, const vector<bool> &digitsUsed)
{
    unsigned digit = 1;
    unsigned pos = 0;

    while (digit < digitsUsed.size()) {
        if (! digitsUsed[digit++]) {
            ++pos;
        }

        if (currDigit == pos) {
            break;
        }
    }

    return digit - 1;
}


vector<unsigned>
findPermutByNum(int N, ULL M)
{
    vector<unsigned> permut;

    vector<ULL> fact = {1, 1, 2, 6, 24, 120, 720, 5040, 40320,
        362'880, 3'628'800, 39'916'800, 479'001'600, 6'227'020'800, 87'178'291'200,
        1'307'674'368'000, 20'922'789'888'000, 355'687'428'096'000,
        6'402'373'705'728'000, 121'645'100'408'832'000
    };

    vector<bool> digitsUsed(N + 1, false);

    ULL currM = M;
    unsigned currDigit;
    int i = N - 1;
    unsigned pos;

    while (i > -1) {
        currDigit = static_cast<unsigned>((currM - 1) / fact[i]) + 1;

        pos = findNotUsedDigit(currDigit, digitsUsed);
        permut.push_back(pos);
        digitsUsed[pos] = true;

        currM = (currM - 1) % fact[i--] + 1;
    }

    return permut;
}


int
main()
{
    int N;
    ULL M;
    cin >> N >> M;

    vector<unsigned> permut = findPermutByNum(N, M);

    cout << permut;

    return 0;
}
