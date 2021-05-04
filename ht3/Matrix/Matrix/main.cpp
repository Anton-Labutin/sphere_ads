//
//  main.cpp
//  Matrix
//
//  Created by Лабутин Антон Александрович on 07.04.2021.
//

/*
 Сортировка матрицы

 Если можно сравнивать строки, почему бы нельзя было сравнивать и матрицы, то есть двумерные массивы? Для простоты положим, что операция сравнения определена только для матриц с одинаковым количеством строк и столбцов.

 Пронумеруем элементы матрицы слева направо и сверху вниз, например, матрица 3*4 будет пронумерована так:
 1 2 3 4
 5 6 7 8
 9 10 11 12

 Сравнение матриц заключается в следующем: сравниваются первые элементы. Если один из них больше, то больше и соответствующая матрица. Если они равны, то берётся второй элемент и т. д. Такое сравнение называется лексикографическим.

 Вам дана матрица из N строк и M столбцов, 3⩽N,M⩽500, состоящая из различных целых чисел от 1 до 231-1.

 Разрешается переставлять произвольное количество раз любые две строки или любые два столбца. Ваша задача получить такими перестановками лексикографически наименьшую матрицу и вывести её.

 Input format

 N M
 A11 A12 ... A1M
 A21 A22 ... A2M
 ...
 AN1 AN2 ... ANM

 Output format

 Лексикографически наименьшая матрица из всех возможных после произвольного количества перестановок строк и столбцов.

 Examples

 Input

 3 3
 4 9 2
 3 5 7
 8 1 6

 Output

 1 6 8
 5 7 3
 9 2 4

 Input

 4 4
 16 3 2 13
 5 10 11 8
 9 6 7 12
 4 15 14 1

 Output

 1 4 14 15
 8 5 11 10
 12 9 7 6
 13 16 2 3
 */

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;


void
findLexMinMatrix(const vector<vector<unsigned>> &matrix,
                vector<unsigned> &sortedRowNum,
                vector<unsigned> &sortedClmNum)
{
    pair<unsigned, unsigned> matrixMinElIdx = {0, 0};

    for (unsigned i = 0; i < matrix.size(); ++i) {
        for (unsigned j = 0; j < matrix[0].size(); ++j) {
            if (matrix[i][j] < matrix[matrixMinElIdx.first][matrixMinElIdx.second]) {
                matrixMinElIdx.first = i;
                matrixMinElIdx.second = j;
            }
        }
    }

    sort(sortedRowNum.begin(), sortedRowNum.end(),
         [&](unsigned row1, unsigned row2) {
        return matrix[row1][matrixMinElIdx.second] < matrix[row2][matrixMinElIdx.second];
    });

    sort(sortedClmNum.begin(), sortedClmNum.end(),
         [&](unsigned clm1, unsigned clm2) {
        return matrix[sortedRowNum[0]][clm1] < matrix[sortedRowNum[0]][clm2];
    });
}


int
main()
{
    unsigned N, M;
    cin >> N >> M;

    vector<vector<unsigned>> matrix(N, vector<unsigned>(M, 0));
    vector<unsigned> sortedRowNum(N, 0);
    vector<unsigned> sortedClmNum(M, 0);

    for (unsigned i = 0; i < N; ++i) {
        for (unsigned j = 0; j < M; ++j) {
            cin >> matrix[i][j];

            sortedClmNum[j] = j;
        }

        sortedRowNum[i] = i;
    }

    findLexMinMatrix(matrix, sortedRowNum, sortedClmNum);

    for (unsigned i = 0; i < sortedRowNum.size(); ++i) {
        for (unsigned j = 0; j < sortedClmNum.size(); ++j) {
            if (j) {
                cout << " ";
            }
            cout << matrix[sortedRowNum[i]][sortedClmNum[j]];
        }
        cout << endl;
    }

    return 0;
}
