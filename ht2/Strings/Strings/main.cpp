//
//  main.cpp
//  Strings
//
//  Created by Лабутин Антон Александрович on 25.03.2021.
//

/*
 Количество подстрок

 Назовём подстрокой любой набор подряд идущих символов строки. Например, в строке aba можно найти три подстроки длины один: a, b, a, две подстроки длины два: ab и ba, а также одну подстроку длины 3: aba.
 Две подстроки здесь совпадают, поэтому различных подстрок здесь 5.
 Нужно для заданной строки, состоящей из строчных букв латинского алфавита, определить, сколько в ней можно найти различных подстрок.

 Input format
 Строка, длиной от 5 до 10000 символов.

 Output format
 Количество различных подстрок в данной строке.

 Examples

 Input
 abracadabra

 Output
 54
 */


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

using ull = unsigned long long;
using STR_IT = string::iterator;
using STR_R_IT = string::reverse_iterator;


void
calcZFunc(const STR_IT& it_begin, const STR_IT& it_end,
          vector<unsigned> &zFunc)
{
    for (STR_IT it = it_begin + 1, l_it = it_begin, r_it = it_begin;
        it != it_end; ++it) {
        STR_IT trav_it = (it > r_it ?
                          it :
                          it + std::min<unsigned>(static_cast<unsigned>(r_it - it) + 1ull,  zFunc[static_cast<unsigned>(it - l_it)]));

        while (trav_it != it_end && (*trav_it == *(it_begin + (trav_it - it)))) {
            ++trav_it;
        }

        zFunc[it - it_begin] = trav_it - it;

        if (trav_it > r_it) {
            l_it = it;
            r_it = --trav_it;
        }
    }
}


ull
calcSubstrCnt(const string& str)
{
    string currStr;
    currStr = str[0];
    vector<unsigned> zFunc(str.size());
    ull substrCnt = 1;

    for (size_t i = 1; i < str.size(); ++i) {
        currStr += str[i];

        zFunc[0] = 0;
        std::reverse(currStr.begin(), currStr.end());
        calcZFunc(currStr.begin(), currStr.end(), zFunc);
        std::reverse(currStr.begin(), currStr.end());

        substrCnt += currStr.size() - *std::max_element(zFunc.begin(), zFunc.begin() + i + 1);

        zFunc.clear();
    }

    return substrCnt;
}


int
main(int argc, const char * argv[])
{
    string str;
    cin >> str;

    ull substrCnt = calcSubstrCnt(str);

    cout <<substrCnt << endl;

    return 0;
}
