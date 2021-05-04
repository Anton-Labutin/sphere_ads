//
//  main.cpp
//  Table
//
//  Created by Лабутин Антон Александрович on 14.04.2021.
//

/*
 Турнирная таблица индивидуалов

 В индивидуальном первенстве по Дартс, участникам необходимо было набрать максимальное число очков за попытку. Количество попыток не ограничивалось. В протокол комиссии попадало имя участника и результат за проделанную попытку. Итоговым результатом участника считалась лучшая попытка. Если результаты совпадают, первым считается игрок показавший данный результат раньше. Помогите организаторам выстроить участников по убыванию.

 Input format

 Сначало задано число участников M (1 ≤ M ≤ 1000), затем число попыток всех участников N (1 ≤ N ≤ 100000). Далее идёт N строк вида

 Имя очки

 Участник не может набрать больше миллиарда очков за одну попытку.

 Output format

 M строк с именами участников в порядке убывания занятых мест.

 Examples

 Input
 4 6
 Ivan 2
 Boris 4
 Ivan 4
 Boris 2
 Petr 4
 David 8

 Output
 David
 Boris
 Ivan
 Petr
 */

#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <vector>


using namespace std;


struct CompPoints {
    bool
    operator() (const unsigned &pointsCnt1, const unsigned &pointsCnt2) const
    {
        return pointsCnt1 > pointsCnt2;
    }
};


int
main()
{
    unsigned peopleCnt; // M
    unsigned attemptsCnt; // N
    cin >> peopleCnt >> attemptsCnt;

    unordered_map<string, int> peoplePoints;
    map<int, vector<string>, CompPoints> pointsOrdered;

    string name;
    unsigned pointsCnt;
    for (unsigned i = 0; i < attemptsCnt; ++i) {
        cin >> name >> pointsCnt;

        if (peoplePoints.count(name)) {
            if (pointsCnt > peoplePoints[name]) {
                peoplePoints[name] = pointsCnt;
            }
        } else {
            peoplePoints[name] = pointsCnt;
        }

        pointsOrdered[pointsCnt].push_back(name);
    }

    for (auto it = pointsOrdered.begin(); it != pointsOrdered.end(); ++it) {
        for (auto const& name : it -> second) {
            if (peoplePoints[name] >= 0) {
                cout << name << endl;
                peoplePoints[name] = -1;
            }
        }
    }

    return 0;
}
