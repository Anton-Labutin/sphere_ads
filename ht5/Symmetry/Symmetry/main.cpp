//
//  main.cpp
//  Symmetry
//
//  Created by Лабутин Антон Александрович on 14.04.2021.
//

/*
 Центральная симметрия

 Имеется множество из 4 ⩽ N ⩽ 100000 точек в декартовом трёхмерном пространстве с
 целочисленными координатами в диапазоне от -10^18 до 10^18. Интересно, есть
 ли у этого множества центр симметрии? Это вам и предстоит выяснить.

 Input format

 N

 X1 Y1 Z1

 ...

 XN YN ZN

 Output format

 Yes или No

 Examples

 Input

 4
 -10 -10 0
 10 10 0
 -10 10 0
 10 -10 0

 Output

 Yes

 Input

 4
 10 10 10
 -10 -10 0
 10 0 -10
 0 10 -10

 Output

 No
 */

#include <iostream>
#include <cstdio>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

using ll = long long;

using Point = struct Point {
    ll x;
    ll y;
    ll z;

    Point()
    {}

    Point(ll x_, ll y_, ll z_) :
    	x(x_), y(y_), z(z_)
    {}
};


struct compPoints {
    double eps = 1e-6;

	bool
    operator() (const Point& p1, const Point& p2) const
    {
        return (p1.x < p2.x) ||
        (abs(p1.x - p2.x) < eps && p1.y < p2.y) ||
        (abs(p1.x - p2.x) < eps && abs(p1.y - p2.y) < eps && p1.z < p2.z);
    }
};

/* не проходит один тест по времени
bool
defineCenter(set<Point, compPoints> &points)
{
    bool hasCenter = false;

    auto it1End = points.end();
    --it1End;

    Point mid;
    Point symForMid;

    for (auto it1 = points.begin(); ! hasCenter && it1 != it1End; ++it1) {
        auto it2 = it1;
        ++it2;

        for (; ! hasCenter && it2 != points.end(); ++it2) {
            mid.x = it1 -> x + it2 -> x;
            mid.y = it1 -> y + it2 -> y;
            mid.z = it1 -> z + it2 -> z;

            bool isMidCenter = true;
            for (auto it3 = points.begin(); it3 != points.end(); ++it3) {
                if (it3 != it1 && it3 != it2) {
                    symForMid.x = mid.x - it3 -> x;
                    symForMid.y = mid.y - it3 -> y;
                    symForMid.z = mid.z - it3 -> z;

                    if (points.count(symForMid) == 0) {
                        isMidCenter = false;
                        break;
                    }
                }
            }

            if (isMidCenter) {
                hasCenter = true;
            }
        }
    }

    return hasCenter;
}
*/


bool
defineCenter(multiset<Point, compPoints> &points)
{
    bool hasCenter = true;

    auto itFirst = points.begin();
    auto itLast = points.end();
    --itLast;

    Point firstPlusLast(itFirst -> x + itLast -> x,
                        itFirst -> y + itLast -> y,
                        itFirst -> z + itLast -> z);

    ++itFirst;
    for (; itFirst != itLast; ++itFirst) {
        Point symPoint = { firstPlusLast.x - itFirst -> x,
							firstPlusLast.y - itFirst -> y,
            				firstPlusLast.z - itFirst -> z };

        if (points.find(symPoint) == points.end()) {
            hasCenter = false;
            break;
        }
    }

    return hasCenter;
}


ostream&
operator << (ostream &out, const set<Point, compPoints> &points)
{

    out << "Print points : start" << endl;
    for (auto it = points.begin(); it != points.end(); ++it) {
        out << "(" << it -> x << ", " << it -> y << ", " << it -> z << ")" << endl;
    }
    out << "Print points : end" << endl;

    return out;
}


int
main()
{
    unsigned pointsCnt;
    scanf("%u", &pointsCnt);

    multiset<Point, compPoints> points;

    ll x, y, z;
    for (unsigned i = 0; i < pointsCnt; ++i) {
        scanf("%lld%lld%lld", &x, &y, &z);

        points.emplace(Point(x, y, z));
    }

    // cout << points;

    bool hasCenter = defineCenter(points);

    printf("%s\n", hasCenter ? "Yes" : "No");

    return 0;
}
