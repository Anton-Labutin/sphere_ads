//
//  main.cpp
//  Tiles
//
//  Created by Лабутин Антон Александрович on 15.04.2021.
//
/*
Tiles

 Перебирая свои школьные архивы, Елпидифор вспомнил, что его школьные годы прошли плодотворно и он получил очень много грамот за примерное поведение, успехи в рисовании, математические олимпиады - и ещё много за что.

 Оказалось, что все грамоты имеют один и тот же размер W*H и текст на всех из них располагается в одной и той же ориентации. Память есть память и ему захотелось, чтобы все эти грамоты были на виду. У него имеется возможность заказать квадратный стенд на фабрике, где работает его одноклассник. Фабрика имеет возможность изготавливать такие стенды с любой стороной квадрата, лишь бы она может быть выражена целым числом. Так как цена заказа зависит от размера стенда, хотелось бы заплатить сумму поменьше.

 Input format

 Входные данные содержат три числа: 1⩽W,H,N⩽109.

 Output format

 Одно целое число — минимальная сторона квадратного стенда, на котором могут разместиться все грамоты. Грамоты могут касаться сторонами, но не пересекаться.

 Examples

 Input

 2 6 15

 Output

 16
 Input

 126576 1984212 88812374

 Output

 4723436592
 */

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using ull = unsigned long long;


ull
calcSquareSide(ull W, ull H, ull N)
{
    ull maxSide = max(W, H);
    ull minSide = min(W, H);

    ull maxSideCnt = 1;
    ull minSideCnt = 1;
    ull inSquareCnt = 0;

    while (true) {
        inSquareCnt = maxSideCnt * minSideCnt;
        
        if (inSquareCnt >= N) {
            return max(maxSideCnt * maxSide, minSideCnt * minSide);
        }

        if ((minSideCnt + 1) * minSide > (maxSideCnt + 1) * maxSide) {
            ++maxSideCnt;
        } else {
            ++minSideCnt;
        }
    }
}


int
main()
{
    ull W, H;
    ull N;

    scanf("%llu%llu%llu", &W, &H, &N);

    ull squareSide = calcSquareSide(W, H, N);

    printf("%llu\n", squareSide);

    return 0;
}
