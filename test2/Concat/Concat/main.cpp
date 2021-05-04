//
//  main.cpp
//  Concat
//
//  Created by Лабутин Антон Александрович on 15.04.2021.
//

/*
 Конкатенация и поворот

 Неформально определим операции конкатенации · и поворота R. Конкатенация склеивает два слова в одно: для слов u = ab и v = abb их конкатенация есть u · v = uv = ababb. Операция поворота переставляет буквы слова в обратном порядке: uR = ba, vR = bba, (uv)R = bbaba. Заметим, что для любых u и v, (uv)R = (vR)(uR).

 На вход задачи подаётся дерево, каждый узел которого является операцией конкатенации. К некоторым узлам применена операция поворота — слово, которое окажется вычисленным в узле необходимо повернуть, прежде чем продолжать вычисление. Необходимо вычислить получившееся в корне слово.

 Input format

 Деревья закодированы скобочными выражениями. Если у узла есть потомки, то потомки перечислены через запятую. Если к узлу применяется операция поворота, то она записана после закрывающей скобки. Длина описания дерева не превосходит 10000 символов. В листьях записаны слова.
 Output format

 Вычисленное слово
 Examples

 Input

 ((ab)R,(abb))


 Output

 baabb


 Input

 ((ab)R,(abb))R


 Output

 bbaab
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <string>

using namespace std;

string
parseWord(string &tree, size_t startIdx, size_t endIdx)
{
    string curWord;
    string tempWord;

    for (size_t i = startIdx; i < endIdx; ++i) {
        char c = tree[i];

        if (c == '(') {
            curWord += tempWord;

            size_t pos = 0;
            int bracketsCnt = 0;

            for (pos = i; pos < tree.size(); ++pos) {
                if (tree[pos] == '(') {
                    ++bracketsCnt;
                }
                else {
                    if (tree[pos] == ')') {
                        --bracketsCnt;
                    }
                }

                if (bracketsCnt == 0) {
                    break;
                }
            }

            if (bracketsCnt) {
                pos = tree.size() - 1;
            }

            tempWord = parseWord(tree, i + 1, pos);
            i = pos;
        } else {
            if (c == 'R') {
                reverse(tempWord.begin(), tempWord.end());
            } else {
                if (c == ',') {
                    curWord += tempWord;
                    tempWord.clear();
                } else {
                    tempWord += c;
                }
            }
        }
    }

    curWord += tempWord;

    return curWord;
}

int
main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string tree;
    cin >> tree;

    string word = parseWord(tree, 0, tree.size());

    cout << word <<endl;

    return 0;
}
