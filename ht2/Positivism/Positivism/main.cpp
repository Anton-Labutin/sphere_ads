//
//  main.cpp
//  Positivism
//
//  Created by Лабутин Антон Александрович on 30.03.2021.
//

/*
 Позитивизм

 У Иеремии родители — философы. Он часто слышит их разговоры, но мало что в них понимает. Сам Иеремия учится в информатическом классе физматшколы, и философия его пока не интересует.
 Недавно он услышал новое для себя слово: позитивизм. Он постеснялся спросить своих родителей, что это слово обозначает, и узнал в Википедии, что-то про эмпирические и философские исследования. Так как слово ему понравилось, он загорелся идеей провести какие-то исследования, а так, как недавно в школе они проходили матрицы, вопрос, что же будет объектом исследования, оказался для него очевидным.
 Он называет позитивной матрицей такую двумерную матрицу, у которой сумма элементов каждой из строк неотрицательна и сумма элементов каждого из столбцов тоже неотрицательна.
 Он поставил перед собой задачу установить, каждую ли из матриц можно сделать позитивной, имея ровно две операции: смену всех знаков на противоположные либо для всех элементов строки, либо для всех элементов столбца. Операции первого вида он записывал, как
 l y,
 где y — номер инвертируемой строки, а второго — как
 c x,
 где x — номер инвертируемого столбца. И столбцы и строки нумеруются с нуля. l — первая буква слова line, c — первая буква слова column.
 Он проделал серию экспериментов и убедился, что если решение существует, то оно может быть не единственным.
 Ваша задача состоит в том, чтобы помочь Иеремии, написав программу, которая либо сообщит, что не существует такой последовательности операций, чтобы матрица стала позитивной, либо выдаст любую последовательность операций, приводящую в конечном итоге к позитивной матрице.

 Input format
 В первой строке — числа N и M — количество строк и столбцов соответственно. Эти числа не превосходят 100.
 В каждой из следующих N строк содержатся значения элементов каждой строки. Ни одно из этих чисел по абсолютной величине не превосходит 106.

 Output format
 Если матрицу можно сделать позитивной, то решение должно состоять из произвольного числа строк указанного выше вида. Если матрица позитивна с самого начала, программа ничего не должна выводить.

 Если её позитивной сделать нельзя, нужно вывести одно слово: Impossible.

 Examples
 Input
 3 3
 1 -10 8
 2 1   3
 1 7   4
 Output
 l 0
 c 2
 Input
 2 2
 1 2
 3 4
 Output

 */

#include <cstdio>
#include <vector>
#include <string>

using std::string;
using std::vector;

int
main()
{
    unsigned N, M;
    scanf("%u%u", &N, &M);

    int num;

    vector<vector<int>> matrix(N, vector<int>(M, 0));
    vector<int> lineSum(N, 0);
    vector<int> clmSum(M, 0);

    for (unsigned i = 0; i < N; ++i) {
        for (unsigned j = 0; j < M; ++j) {
            scanf("%d", &num);

            matrix[i][j] = num;
            lineSum[i] += num;
            clmSum[j] += num;
        }
    }

    bool hasNegSum = true;
    while (hasNegSum) {
        hasNegSum = false;

        for (unsigned i = 0; i < N; ++i) {
            if (lineSum[i] < 0) {
                lineSum[i] *= -1;

                printf("l %d\n", i);
                for (unsigned j = 0; j < M; ++j) {
                    matrix[i][j] *= -1;
                    clmSum[j] += 2 * matrix[i][j];
                }
            }
        }

        for (unsigned j = 0; j < M; ++j) {
            if (clmSum[j] < 0) {
                clmSum[j] *= -1;

                printf("c %d\n", j);
                for (unsigned i = 0; i < N; ++i) {
                    matrix[i][j] *= -1;
                    lineSum[i] += 2 * matrix[i][j];

                    if (lineSum[i] < 0) {
                        hasNegSum = true;
                    }
                }
            }
        }
    }


    return 0;
}
