//
//  main.cpp
//  dance
//
//  Created by Лабутин Антон Александрович on 23.03.2021.
//

/*
 Танец точек

 На прямой располагается 1⩽N⩽10000 точек с целочисленными координатами −109⩽Vi⩽109. Каждой из точек разрешается сделать ровно одно движение (танцевальное па) в любом направлении на расстояние не больше 0⩽L⩽108 и остановиться на другой позиции. Какое минимальное количество точек может оказаться после окончания танца (все точки после танца, оказывающиеся на одной позиции сливаются в одну)?

 Input format

 L N
 V1
 V2
 ...
 VN

 Output format

 MinimalNumberOfPoints

 Examples

 Input
 10 5
 30 3 14 19 21

 Output
 2
 */

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::sort;

using ull = unsigned long long;
using ll = long long;

int
main()
{
    ull N, L;
    ll V;

    scanf("%llu%llu", &L, &N);

    vector<ll> points;
    for (ull i = 0; i < N; ++i) {
        scanf("%lld", &V);
        points.push_back(V);
    }

    sort(points.begin(), points.end());

    ull pointsMinCnt = 1;
    ll curMax = points[0] + 2 * L;

    for (ull i = 0; i < N; ++i) {
        if (points[i] > curMax) {
            ++pointsMinCnt;
            curMax = points[i] + 2 * L;
        }
    }

    printf("%llu\n", pointsMinCnt);

    return 0;
}
