//
//  main.cpp
//  Circus
//
//  Created by Лабутин Антон Александрович on 28.03.2021.
//

/*
 Башня

 В Бурляндск приехал цирк. Одним из привлекающих внимание горожан номеров всегда было построение как можно более высокой башни из группы циркачей.
 В построенной башне один циркач стоит на земле, второй - на его плечах, третий - на плечах второго, и так далее. У циркача под номером i вес равен wi, а сила — fi. Сила — способность удерживать на себе заданный вес. Точно известно, что более тяжёлый циркач является и более сильным. Впрочем, циркачи с одинаковым весом могут иметь различную силу.

 Input format
 Первая строка ввода содержит 4⩽N⩽3000 — количество человек в команде, которые хотят построить башню.
 Каждая их последующих строк содержит по два числа — вес и силу участника команды. Все числа — положительные целые, меньшие 100000.

 Output format
 Максимальная высота башни, которую может построить эта команда.

 Examples

 Input
 4
 5 13
 16 20
 1 9
 13 15

 Output
 4
 */

#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using std::vector;
using std::multiset;

using Performer = struct Performer {
    unsigned weight;
    unsigned force;
};

using vec_Perf = vector<Performer>;
using ull = unsigned long long;


int
main()
{
    unsigned N;
    scanf("%u", &N);

    unsigned w, f;

    vec_Perf performers;

    for (unsigned i = 0; i < N; ++i) {
        scanf("%u%u", &w, &f);
        performers.push_back({w, f});
    }

    std::sort(performers.begin(), performers.end(),
              [](const Performer& p1, const Performer& p2) {
        return (p1.weight + p1.force) < (p2.weight + p2.force);
    });



    auto msetComp = [](const Performer& p1, const Performer& p2) {
        return p1.weight > p2.weight;
    };

    multiset<Performer, decltype(msetComp)> tower(msetComp);
    ull towerWeight = 0;
    for (Performer& p : performers) {
        if (p.force >= towerWeight) {
            towerWeight += p.weight;
            tower.insert(p);
        } else {
            unsigned maxWeight = tower.begin() -> weight;
            if (p.force >= towerWeight - maxWeight && p.weight < maxWeight) {
                towerWeight -= maxWeight;
                tower.erase(tower.begin());
                towerWeight += p.weight;
                tower.insert(p);
            }
        }
    }

    printf("%zu\n", tower.size());

    return 0;
}
