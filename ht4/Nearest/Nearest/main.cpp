//
//  main.cpp
//  Nearest
//
//  Created by Лабутин Антон Александрович on 12.04.2021.
//

/*
 Минимальное расстояние

 На плоскости расположено 2⩽N⩽500000 различных точек с вещественными координатами. Требуется найти пару таких точек, расстояние между которыми минимально.

 Input format

 N

 X1

 X2

 ...

 XN

 Output format

 Требуется вывести минимальное расстояние из всех возможных пар точек с десятью знаками после запятой и сами точки в порядке возрастания их номеров в исходном файле. Нумерация точек начинается с единицы. Если имеются пары точек с одинаковым расстоянием, то вывести пару с наименьшими номерами.

 Examples

 Input

 5
 1 1
 -3 3
 -3 -3
 3 -3
 3 3

 Output

 2.8284271247 1 5

 Input

 10
 -2.0963 7.5352
 4.1049 -8.3162
 8.8663 -3.9484
 -0.2246 5.8565
 -9.2426 -0.9568
 -1.5535 -9.8134
 6.6213 3.8424
 -1.1678 -6.3822
 -6.3482 5.6182
 4.9898 2.9222

 Output

 1.8731151299 7 10
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <cmath>

using namespace std;

using Point = struct Point {
    double x;
    double y;
    size_t num;
};


using NearestPoints = struct NearestPoints {
    double minDist = numeric_limits<double>::max();
    size_t firstIdx;
    size_t secondIdx;
};


inline bool
compPointsY (const Point &a, const Point &b)
{
    return a.y < b.y;
}


inline double
calcDist (const Point &a, const Point &b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}


constexpr size_t THRESHOLD = 4;

void
calcMinDist (vector<Point> &points, size_t leftIdx, size_t rightIdx, NearestPoints &res)
{
    if (rightIdx - leftIdx <= THRESHOLD) {
        double dist;
        for (size_t i = leftIdx; i < rightIdx; ++i) {
            for (size_t j = i + 1; j < rightIdx; ++j) {
                dist = calcDist (points[i], points[j]);

                if (dist < res.minDist) {
                    res.minDist = dist;
                    res.firstIdx = min(points[i].num, points[j].num);
                    res.secondIdx = max(points[i].num, points[j].num);
                }
            }
        }

        sort (points.begin() + leftIdx, points.begin() + rightIdx, compPointsY);
        return;
    }

    size_t midIdx = (leftIdx + rightIdx) >> 1;
    double midIdxPointX = points[midIdx].x;

    calcMinDist (points, leftIdx, midIdx, res);
    calcMinDist (points, midIdx, rightIdx, res);

    vector<Point> tempPoints(rightIdx - leftIdx);

    merge (points.begin() + leftIdx, points.begin() + midIdx,
           points.begin() + midIdx, points.begin() + rightIdx,
           tempPoints.begin(), compPointsY);

    copy(tempPoints.begin(), tempPoints.end(), points.begin() + leftIdx);

    {
        size_t tempSize = 0;
        double dist;

        for (size_t i = leftIdx; i < rightIdx; ++i) {
            if (abs(points[i].x - midIdxPointX) < res.minDist) {
                for (size_t j = tempSize; j > 0 && (points[i].y - tempPoints[j - 1].y < res.minDist); --j) {
                    dist = calcDist (points[i], tempPoints[j - 1]);

                    if (dist < res.minDist) {
                        res.minDist = dist;
                        res.firstIdx = min(points[i].num, tempPoints[j - 1].num);
                        res.secondIdx = max(points[i].num, tempPoints[j - 1].num);
                    }
                }

                tempPoints[tempSize++] = points[i];
            }
        }
    }
}


inline bool
cmpPointsX (const Point &a, const Point &b) {
    return (a.x < b.x) || ((a.x == b.x) && (a.y < b.y));
}


int
main()
{
    size_t pointsCnt; // N
    cin >> pointsCnt;

    vector<Point> points(pointsCnt);
    {
        double x, y;
    	for (size_t i = 0; i < pointsCnt; ++i) {
        	cin >> x >> y;
            points[i] = {x, y, i + 1};
    	}
    }

    sort (points.begin(), points.end(), cmpPointsX);

    NearestPoints res;
    calcMinDist (points, 0, points.size(), res);

    cout << fixed << setprecision(10) << res.minDist << " " << res.firstIdx << " " << res.secondIdx << endl;

    return 0;
}
