//
//  main.cpp
//  String Covering
//
//  Created by Лабутин Антон Александрович on 16.03.2021.
//

/*
 Задача о покрытии строки.
 Имеется набор строк s_i - слов, каждое из которых не начинается с другого
 (префиксный код).
 Вход: строка p.
 Выход: можно ли составить слово p из слов s_i.

 Решение на основе префиксного дерева.
 */

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

// #define NDEBUG - комментирование assert'ов

using namespace std;

struct PrefixTree {
    PrefixTree* children[3] = {nullptr, nullptr, nullptr}; // условились, что
    // вход состоит из букв a, b, c
    bool isLeaf;
};


PrefixTree*
buildTree(const vector<string> &words)
{
    PrefixTree *root = new PrefixTree();

    for (const auto &word : words) {
        auto ptr = root;

        for (auto c : word) {
            assert(c >= 'a' && c <= 'c');
            if (ptr -> children[c - 'a'] == nullptr) {
                ptr -> children[c - 'a'] = new PrefixTree();
            }

            ptr = ptr -> children[c - 'a'];
            assert(! ptr -> isLeaf); // проверка кода на префиксность
        }

        assert(ptr -> children[0] == nullptr &&
               ptr -> children[1] == nullptr &&
               ptr -> children[2] == nullptr);

        ptr -> isLeaf = true;
    }

    return root;
}


bool
checkTree(const PrefixTree *pt, const string &sentence)
{
    auto ptr = pt;

    for (auto c : sentence) {
        if (c < 'a' || c > 'c') {
            return false;
        }

        ptr = ptr -> children[c - 'a'];

        if (ptr == nullptr) {
            return false;
        }
        if (ptr -> isLeaf) {
            ptr = pt;
        }
    }

    return ptr == pt;
}


int
main()
{
    string sentence;
    getline(cin, sentence);
    vector<string> words;

    while (true) {
        string word;
        getline(cin, word);
        if (word.empty()) {
            break;
        }
        words.push_back(word);
    }

    PrefixTree *pt = buildTree(words);
    bool ok = checkTree(pt, sentence);

    cout << (ok ? "OK" : "FAIL") << endl;

    return 0;
}
