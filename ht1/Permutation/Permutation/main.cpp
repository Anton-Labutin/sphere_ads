//
//  main.cpp
//  Permutation
//
//  Created by Лабутин Антон Александрович on 15.03.2021.
//

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
