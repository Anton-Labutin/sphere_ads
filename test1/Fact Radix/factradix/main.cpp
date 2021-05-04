//
//  main.cpp
//  factradix
//
//  Created by Лабутин Антон Александрович on 23.03.2021.
//

#include <cstdio>

using ull = unsigned long long;

ull
GCD(ull a, ull b)
{
    return b ? GCD(b, a % b) : a;
}


int
main()
{
    ull p, q;

    scanf("%llu%llu", &p, &q);

    ull gcd = GCD(q, p);
    // printf("gcd = %llu\n", gcd);
    p /= gcd;
    q /= gcd;
    // printf("p = %llu, q = %llu\n", p, q);

    ull currBase = 2;
    ull currDigit = 2;

    while (p % q) {
        gcd = GCD(p * currBase, q);
        // printf("gcd = %llu\n", gcd);
        p = (currBase * p) / gcd;
        q /= gcd;
        // printf("p = %llu, q = %llu\n", p, q);

        currDigit = p / q;
        printf("%llu ", currDigit);

        p = p - q * currDigit;
        ++currBase;
    }
    printf("\n");

    return 0;
}
