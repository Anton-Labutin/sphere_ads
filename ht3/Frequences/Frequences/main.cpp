//
//  main.cpp
//  Frequences
//
//  Created by Лабутин Антон Александрович on 07.04.2021.
//

/*
 Подсчёт частот

 На вход подаётся строка, состоящая из букв A-Z. Необходимо вывести все буквы, которые встречаются в строке в порядке убывания частот вместе с частотой. В случае равенства частот первой должна идти буква, которая встречается в алфавите раньше.

 Input format
 Строка из букв A-Z

 Output format
 L1 C1

 ...

 Lk Ck

 где Li — буква, входящая с строку, Ci — число вхожданий буквы в строку.

 Examples

 Input
 ABRACADABRA

 Output
 A 5
 B 2
 R 2
 C 1
 D 1

 */

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

constexpr unsigned LETTERS_CNT = 26;
constexpr char FIRST_LETTER = 'A';
constexpr char LAST_LETTER = 'Z';

using CHarFreq = struct CharFreq {
    char c = 0;
    unsigned freq = 0;
};


bool
compCharFreq(const CharFreq &chfr1, const CharFreq &chfr2)
{
    return (chfr1.freq > chfr2.freq) ||
    (chfr1.freq == chfr2.freq && chfr1.c < chfr2.c);
}


int
main()
{
    string str;
    cin >> str;

    vector<CharFreq> charFreq(LETTERS_CNT);

    for (auto c : str) {
        assert(c >= FIRST_LETTER && c<= LAST_LETTER);
        charFreq[c - FIRST_LETTER].c = c;
        charFreq[c - FIRST_LETTER].freq += 1;
    }

    sort(charFreq.begin(), charFreq.end(), compCharFreq);

    for (unsigned i = 0; i < charFreq.size() && charFreq[i].freq > 0; ++i) {
        cout << charFreq[i].c << " " << charFreq[i].freq << endl;
    }

    return 0;
}
