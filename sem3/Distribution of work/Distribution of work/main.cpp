//
//  main.cpp
//  Distribution of work
//
//  Created by Лабутин Антон Александрович on 18.03.2021.
//

/*
 Задача о распределении работ.

 Есть список рабочих и список работ.
 Каждый рабочий может выполнить только одну работу за некоторую плату.
 Каждая работа может быть выполнена только одним рабочим.

 Найти распределение работ, минимизирующее сумму выплат.
 */

#include <stdio.h>
#include <vector>

using std::vector;

using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;


struct bitset {
	void
    set(size_t bit)
    {
        val |= (1ull << bit);
    }

    void
    clear(size_t bit)
    {
        val &= ~(1ull << bit);
    }

    bool
    in(size_t bit)
    {
        return (val >> bit) & 1;
    }

    size_t val = 0; // каждый бит - номер столбца; = 1 - столбец использовать нельзя
};

const ll BIG = 1'000'000'000'000;

ll
solve(const vvll &map, size_t row, bitset mask, ll sum, ll &reached)
{
    if (sum >= reached) {
        return BIG; // отсекаем неоптимальные пути
    }

    size_t N = map.size();
    ll bestVal = BIG;

    if (row == N) {
        if (sum < reached) {
            printf("!!! new reached = %lld\n", sum);
            reached = sum;
        }
        return sum;
    }

    for (size_t clm = 0; clm < N; ++clm) {
        if (! mask.in(clm)) {
            mask.set(clm);
            auto curSum = solve(map, row + 1, mask, sum + map[row][clm], reached);
            if (sum < bestVal) {
                bestVal = curSum;
            }
            mask.clear(clm);
        }
    }

    return bestVal;
}

int
main()
{
    size_t N;
    scanf("%zu", &N);

    vvll map(N, vll(N));
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            scanf("%lld", &map[i][j]);
        }
    }

    bitset mask;
    ll reached = BIG; // текущая минимальная накопленная сумма
    ll result = solve(map, 0, mask, 0, reached);

    printf("result = %lld\n", result);

    return 0;
}
