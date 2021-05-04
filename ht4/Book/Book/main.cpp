//
//  main.cpp
//  Book
//
//  Created by Лабутин Антон Александрович on 08.04.2021.
//

/*
 Издательство

 Очень плодовитый автор Правдолюбов принёс в издательство свою новую эпопею, от которой издательству отказаться не удалось (как ни тяжела ноша издательства, а адвокат у Правдолюбова был очень известным, что тут поделаешь). В эпопее много глав (1⩽N⩽1000000), в каждой из которых было до 10000 страниц. Издать такой монументальный труд в виде одного тома оказалось никак невозможно, поэтому эпопею для печати потребовалось разбить на тома. Как обычно, каждый том содержит последовательные главы книги. Было решено издать сей продукт творчества в K томах, причём размер каждого тома в страницах должен быть ограничен каким-то числом M.

 Ваша задача — найти такое минимальное число M, чтобы при разбиении книги на тома размер тома не превосходил M и при этом потребовалось бы не более K томов.

 Input format

 K N

 V1 V2 ... VN

 Output format

 M

 Examples

 Input

 3 6
 2 3 1 2 1 1

 Output

 4

 Notes

 В условии из примера при размере тома в 4 страницы существует следующее разбиение книги на тома: {2}, {3,1}, {2,1,1}. Нетрудно убедиться, что при размере тома в 3 страницы такого разбиения не существует.
 */

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using ull = unsigned long long;


ull
calcPgsPerVlm(const vector<unsigned> &chapters, ull maxPgsPerChp, ull totalPgsCnt, unsigned vlmCnt)
{
    if (vlmCnt == 1 || chapters.size() == 1) {
        return totalPgsCnt;
    }

    ull minPgsPerVlm = maxPgsPerChp;
    ull maxPgsPerVlm = totalPgsCnt;

    ull pgsPerVlm = 0;
    ull curPgsPerVlm = 0;
    while (true) {
        curPgsPerVlm = (minPgsPerVlm + maxPgsPerVlm) >> 1;
        if (curPgsPerVlm == pgsPerVlm) {
            break;
        }

        ull curVlmCnt = 0;
        ull curPgsCnt = 0;

        for (size_t i = 0; i < chapters.size(); ) {
            while (i < chapters.size() && curPgsCnt + chapters[i] <= curPgsPerVlm) {
                curPgsCnt += chapters[i];
                ++i;
            }

            ++curVlmCnt;
            curPgsCnt = 0;
        }

        if (curVlmCnt <= vlmCnt) {
            if (pgsPerVlm == 0 || curPgsPerVlm < pgsPerVlm) {
            	pgsPerVlm = curPgsPerVlm;
            }

            maxPgsPerVlm = curPgsPerVlm;
        } else {
            if (minPgsPerVlm == curPgsPerVlm || maxPgsPerVlm == curPgsPerVlm) {
                break;
            }

            minPgsPerVlm = curPgsPerVlm;
        }
    }

    return pgsPerVlm;
}


int
main()
{
    unsigned chpCnt; // N
    unsigned vlmCnt; // K

    scanf("%u%u", &vlmCnt, &chpCnt);

    vector<unsigned> chapters(chpCnt);
    ull maxPgsPerChp = 0;
    ull totalPgsCnt = 0;
    for (unsigned i = 0; i < chpCnt; ++i) {
        scanf("%u", &chapters[i]);

        if (chapters[i] > maxPgsPerChp) {
            maxPgsPerChp = chapters[i];
        }

        totalPgsCnt += chapters[i];
    }

    ull curPgsPerVlm = calcPgsPerVlm(chapters, maxPgsPerChp, totalPgsCnt, vlmCnt);

    printf("%llu\n", curPgsPerVlm);

    return 0;
}
