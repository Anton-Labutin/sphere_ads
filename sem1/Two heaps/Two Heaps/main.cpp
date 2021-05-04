//
//  main.cpp
//  Two Heaps
//
//  Created by Лабутин Антон Александрович on 10.03.2021.
//

#include <iostream>

/*
 Имеется 2 ⩽ N ⩽ 23 камня с целочисленными весами W1, W2, ... , WN.
 Требуется разложить их на две кучи таким образом, чтобы разница в весе куч
 была минимальной. Каждый камень должен принадлежать ровно одной куче.

 Формат входных данных
 N
 W1 W2 ... WN

 Формат результата
 Минимальная неотрицательная разница в весе куч.

 Примеры

 Входные данные
 5
 8 9 6 9 8
 Результат работы
 4

 Входные данные
 6
 14 2 12 9 9 8
 Результат работы
 2
 */

// the backpack task implementation
int
main()
{
    unsigned N; // faster than size_t
    scanf("%u", &N);

    int W[25];

    long long total = 0; // total weight

    for (unsigned i = 0; i < N; ++i) {
        scanf("%d", &W[i]);
        total += W[i];
    }

    long long min = 1e18;
    unsigned lim = 1 << N;

    for (unsigned u = 0; u < lim; ++u) {
        // u - generator of the 1st heap
        long long part = 0; // partial sum of the 1st heap

        /* for (unsigned bitIdx = 0; bitIdx < N; ++bitIdx) {
         // if bitIdx'th bit in u is set 1 then the rock - in the 1st heap
         if ((u >> bitIdx) & 1) {
         part += W[bitIdx];
         }
         } */
        for (unsigned bitIdx = 0, v = u; v != 0; v >>= 1, ++bitIdx) { // faster
            // if bitIdx'th bit in u is set 1 then the rock - in the 1st heap

            /* if (v & 1) {
             part += W[bitIdx];
             } */

            part += W[bitIdx] * (v & 1); // faster than 3 times than if !
        }

        // part - the weight of the 1st heap - INVARIANT !
        // total - part - the weight of the 2d heap
        long long dist = (total - part) - part; // diff between the weights
        if (dist < 0) {
            dist = -dist;
        }
        if (dist < min) {
            min = dist;
        }
    }

    printf("%lld\n", min);
    
    return 0;
}
