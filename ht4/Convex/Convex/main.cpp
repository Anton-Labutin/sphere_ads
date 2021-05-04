//
//  main.cpp
//  Convex
//
//  Created by Лабутин Антон Александрович on 18.04.2021.
//

/*
 Выпуклая оболочка

 Выпуклая оболочка из множества точек на плоскости --- наименьший выпуклый многоугольник, содержащий все точки множества. Требуется по заданным точкам определить длину периметра выпуклой оболочки этого множества.

 Input format

 На вход подаётся число 3⩽N⩽500000 — число точек множества.

 В следующих N строках содержатся пары координат -10000⩽Xi,Yi⩽10000 i-й точки множества. Все координаты целочисленные.

 Output format

 Одно вещественное число — периметр требуемого многоугольника с двумя знаками после запятой.

 Examples

 Input

 5
 2 1
 2 2
 2 3
 3 2
 1 2

 Output

 5.66
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;


using Point = struct Point {
    int x;
    int y;
};


bool
cmpPoints (const Point& a, const Point& b)
{
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}


double
doubleTriangleArea(const Point &a, const Point &b, const Point &c)
{
    return (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
}


// поворот по часовой стрелке
bool
clockwise (const Point &a, const Point &b, const Point &c)
{
    return doubleTriangleArea(a, b, c) < 0;
}

// поворот против часовой стрелки
bool
counterClockwise (const Point &a, const Point &b, const Point &c)
{
    return doubleTriangleArea(a, b, c) > 0;
}


double
calcDist(const Point &a, const Point &b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}


double
convexHullPerimeter (vector<Point> &points)
{
    sort (points.begin(), points.end(), cmpPoints);

    Point p1 = points[0];
    Point p2 = points.back();

    vector<Point> upConvexHull, downConvexHull;
    upConvexHull.push_back(p1);
    downConvexHull.push_back(p1);

    for (size_t i = 1; i < points.size(); ++i) {
        if (i == points.size() - 1 ||
            clockwise(p1, points[i], p2)) {
            while (upConvexHull.size() >= 2 &&
                   ! clockwise (upConvexHull[upConvexHull.size() - 2],
                                upConvexHull[upConvexHull.size() - 1],
                                points[i])) {
                upConvexHull.pop_back();
            }

            upConvexHull.push_back (points[i]);
        }

        if (i == points.size() - 1 ||
            counterClockwise (p1, points[i], p2)) {
            while (downConvexHull.size() >= 2 &&
                   ! counterClockwise (downConvexHull[downConvexHull.size() - 2],
                                       downConvexHull[downConvexHull.size() - 1],
                                       points[i])) {
                downConvexHull.pop_back();
            }

            downConvexHull.push_back(points[i]);
        }
    }

    double perimeter = 0.0;
    for (size_t i = 1; i < upConvexHull.size(); ++i) {
        perimeter += calcDist(upConvexHull[i], upConvexHull[i - 1]);
    }

    for (size_t i = 1; i < downConvexHull.size(); ++i) {
        perimeter += calcDist(downConvexHull[i], downConvexHull[i - 1]);
    }

    return perimeter;
}


int
main()
{
    unsigned N;
    scanf("%u", &N);

    vector<Point> points(N);
    for (size_t i = 0; i < points.size(); ++i) {
        Point p;
        scanf("%d%d", &p.x, &p.y);

        points[i] = p;
    }

    double perimeter = convexHullPerimeter(points);

    printf("%.2lf\n", perimeter);

    return 0;
}
