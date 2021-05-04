//
//  main.cpp
//  Sequence
//
//  Created by Лабутин Антон Александрович on 17.03.2021.
//

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
