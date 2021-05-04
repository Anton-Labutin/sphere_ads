//
//  main.cpp
//  Life
//
//  Created by Лабутин Антон Александрович on 30.04.2021.
//

/*
 Жизнь

 Клеточные автоматы — одно из важных понятий математического моделирования. Одним из первых клеточных автоматов была игра Жизнь. Она была изобретена в 1970-м году американским математиком Конвеем.

 У автора игра происходит на бесконечной доске. У нас столько времени и столько пространства нет, поэтому ограничимся конечной. Игровое поле — двумерно, оно состоит из клеток, у каждой из которых ровно восемь соседей (на бесконечной доске). В клетках может зарождаться жизнь (живые клетки) и в клетках жизни может не быть (мёртвые клетки).

 На каждом такте происходит следующий процесс:

 если живая клетка имеет двух или трёх живых соседей, то она остаётся жить, в противном случае она погибает от одиночества или перенаселения;
 если мёртвая клетка имеет ровно трёх живых соседей, в ней зарождается жизнь.
 Вот пример: позиция
 ABCDEFGHIJ
 0 ..#.......
 1 ...#......
 2 .###......
 3 ..........
 4 ..........
 5 ..........

 на следующем такте становится
 ABCDEFGHIJ
 0 ..........
 1 .#.#......
 2 ..##......
 3 ..#.......
 4 ..........
 5 ..........

 так как погибают от одиночества клетки C1 и B2, при этом рождаются клетки C3 и B1.

 Ваша задача заключается в том, чтобы, имея начальную позицию, вывести ту, которая получится после нескольких тактов.

 Input format

 Первая строка содержит 4 числа— размер игрового поля 5⩽N,M⩽5000, количество живых клеток 4⩽L⩽5000 и количество тактов игры 1⩽K⩽100000.

 В следующих L строках содержатся координаты живых клеток 0⩽Xi<N 0⩽Yi<M

 Требуется вывести координаты всех живых клеток заключительной позиции в лексикографическом порядке по одной клетке на строку.

 Гарантируется, что в любой из позиций количество живых клеток в игре ни в один момент времени не превзойдёт 100000.

 За пределами доски жизнь зародиться не может.

 Output format

 Examples

 Input

 6 9 5 1
 0 2
 1 3
 2 1
 2 2
 2 3

 Output

 1 1
 1 3
 2 2
 2 3
 3 2

 Input

 4 4 4 4
 1 1
 1 2
 2 1
 2 2

 Output

 1 1
 1 2
 2 1
 2 2
 */

#include <iostream>
#include <set>
#include <map>

using namespace std;
using ull = unsigned long long;
using ll = long long;


constexpr ull NEIGHBOUR_CELLS_MAX_CNT = 8;
ll gameFieldRowCnt; // N
ll gameFieldClmCnt; // M


using GameField = struct Point {
    Point(ll x_ = 0, ll y_ = 0)
    	: x(x_), y(y_)
    {}

    ll x;
    ll y;
};


struct CompGameFields {
    bool
    operator() (const GameField &gf1, const GameField &gf2) const
    {
        return (gf1.x < gf2.x) ||
        ((gf1.x == gf2.x) && (gf1.y < gf2.y));
    }
};


void
addNeighbours(map<ull, set<GameField, CompGameFields>> &neighbourCells,
              const GameField &field)
{
    ll dx[] = {-1, 0, 1};
    ll dy[] = {-1, 0, 1};

    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            if (dx[i] != 0 || dy[j] != 0) {
                ll new_x = field.x + dx[i];

                if (new_x >= 0 && new_x < gameFieldRowCnt) {
                    ll new_y = field.y + dy[j];

                    if (new_y >= 0 && new_y < gameFieldClmCnt) {
                        GameField point( {new_x, new_y} );

                        ull k = 1;
                        auto pointIt = neighbourCells[k].begin();
                        while (k <= NEIGHBOUR_CELLS_MAX_CNT &&
                               ((pointIt = neighbourCells[k].find(point)) == neighbourCells[k].end())) {
                            ++k;
                        }

                        if (k > NEIGHBOUR_CELLS_MAX_CNT) {
                            neighbourCells[1].insert(point);
                        } else {
                            if (k < NEIGHBOUR_CELLS_MAX_CNT) {
                                neighbourCells[k].erase(pointIt);
                                neighbourCells[k + 1].insert(point);
                            }
                        }
                    }
                }
            }
        }
    }
}


void
getNewGameField(set<GameField, CompGameFields> &liveCells,
                map<ull, set<GameField, CompGameFields>> &neighbourCells,
                ll gameFieldRowCnt, ll gameFieldClmCnt, ull stepsCnt)
{
    for (ull step = 0; step < stepsCnt && liveCells.size(); ++step) {
        for (const auto &liveCell : liveCells) {
            addNeighbours(neighbourCells, liveCell);
        }

        /* for (const auto &cells : neighbourCells) {
            cout << cells.first << "-> { ";
            for (const auto &cell : cells.second) {
                cout << "(" << cell.x << ", " << cell.y << "), ";
            }
            cout << "}" << endl;
        } */

        set<GameField, CompGameFields> deletedCells;
        for (const auto &liveCell : liveCells) {

            if ((neighbourCells[2].find(liveCell) == neighbourCells[2].end()) &&
                (neighbourCells[3].find(liveCell) == neighbourCells[3].end())) {
                deletedCells.insert(liveCell);
            }
        }

        for (const auto &cell : deletedCells) {
            liveCells.erase(cell);
        }
        deletedCells.clear();

        for (auto &cell : neighbourCells[3]) {
            liveCells.insert(cell);
        }

        for (size_t i = 1; i <= NEIGHBOUR_CELLS_MAX_CNT; ++i) {
            neighbourCells[i].clear();
        }
    }
}


int
main()
{
    cin >> gameFieldRowCnt >> gameFieldClmCnt;

    ull liveCellsCnt; // L
    cin >> liveCellsCnt;

    ull stepsCnt; // K
    cin >> stepsCnt;

    set<GameField, CompGameFields> liveCells;
    map<ull, set<GameField, CompGameFields>> neighbourCells;
    for (ull i = 1; i <= NEIGHBOUR_CELLS_MAX_CNT; ++i) {
        neighbourCells[i] = set<GameField, CompGameFields>();
    }

    for (ull i = 0; i < liveCellsCnt; ++i) {
        ll x, y;
        cin >> x >> y;
        GameField field(x, y);
        liveCells.insert(field);
    }

    getNewGameField(liveCells, neighbourCells, gameFieldRowCnt, gameFieldClmCnt, stepsCnt);

    for (const auto &liveCell : liveCells) {
        cout << liveCell.x << " " << liveCell.y << endl;
    }

    return 0;
}
