//
//  main.cpp
//  Aliens
//
//  Created by Лабутин Антон Александрович on 29.03.2021.
//

/*
 Чуждые элементы

 Последовательность из 2⩽N⩽1000000 элементов содержит натуральные числа от 1 до 1018. Назовём пару соседних чисел, которая имеет общие множители, большие единицы, родственниками. В исходную последовательность вставляют натуральные числа (чуждые элементы) таким образом, что в итоговой последовательности не остаётся родственников. Требуется определить минимально возможную сумму чуждых элементов. Пример: в исходную последовательность
 4 8 9 10
 можно вставить чуждый элемент 5 после 4:
 4 5 8 9 10
 после чего последовательность не содержит родственников.
 Input format
 N
 X1
 X2
 ...
 XN

 Output format
 Sum
 Examples
 Input
 10
 4
 8
 1
 2
 4
 2
 1
 7
 62
 3

 Output
 3
 */

#include <cstdio>

using ull = unsigned long long;


ull
calcGCD(ull a, ull b)
{
    if (a % b == 0) {
        return b;
    }

    if (b % a == 0) {
        return a;
    }

    if (a > b) {
        return calcGCD(a % b, b);
    }

    return calcGCD(a, b % a);
}


int
main()
{
    unsigned N;
    scanf("%u", &N);

    ull a;
    scanf("%llu", &a);

    ull b;
    ull gcd;
    ull aliensMinSum = 0;

    while (--N) {
        scanf("%llu", &b);

        gcd = calcGCD(a, b);
        // printf("gcd(%llu, %llu) = %llu\n", a, b, gcd);
        aliensMinSum += (gcd > 1);

        a = b;
    }

    printf("%llu\n", aliensMinSum);

    return 0;
}
