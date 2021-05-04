//
//  main.cpp
//  Anagrams
//
//  Created by Лабутин Антон Александрович on 15.04.2021.
//

/*
 Анаграммы

 Как известно, анаграммами называются слова, которые могут получиться друг из друга путём перестановки букв, например LOOP, POOL, POLO. Будем называть все слова такого рода комплектом.

 Требуется определить число комплектов во входном множестве.

 Input format

 На вход программы подаётся число слов 1⩽N⩽100000. В каждой из очередных N строк присутствует одно слово, состоящее из заглавных букв латинского алфавита. Все слова имеют одинаковую длину 3⩽L⩽10000.
 Output format

 NumberOfComplects
 Examples

 Input

 8
 BCB
 ABA
 BCB
 BAA
 BBC
 CCB
 CBC
 CBC

 Output

 3
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>

using namespace std;

int
main()
{
    size_t N;
    scanf("%zu\n", &N);
    char *word = (char*) malloc(10002 * sizeof(char));

    set<vector<unsigned>> anagrams;
    size_t allLettersCnt = 26;

    for (size_t i = 0; i < N; ++i) {
        //fgets(word, 10002, stdin);
        scanf("%s", word);
        size_t wordLen = strlen(word);

        vector<unsigned> lettersCnt(allLettersCnt, 0);
        for (size_t i = 0; i < wordLen; ++i) {
            lettersCnt[word[i] - 'A'] += 1;
        }

        anagrams.insert(move(lettersCnt));
    }

    printf("%zu\n", anagrams.size());
    free(word);

    return 0;
}
