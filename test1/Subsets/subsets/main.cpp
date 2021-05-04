//
//  main.cpp
//  subsets
//
//  Created by Лабутин Антон Александрович on 23.03.2021.
//

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>


using std::string;
using std::map;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

using ull = unsigned long long;

void
findAllMultiSubsets(map<char, unsigned> &setCharCnt, vector<string> &subsets, ull curSubsetPos)
{
    string curSet;
    for (auto &[c, cnt] : setCharCnt) {
        if (cnt) {
            curSet += c;
            --cnt;
        }
    }

    if (curSet.size() == 0) {
        return;
    }

    ull curSetCard = (1ull << curSet.size());
    ull curLen = subsets.size();
    for (ull i = 1; i < curSetCard; ++i) {
        string curSubset;

        for (ull j = i, curSetPos = 0; j; j >>= 1, ++curSetPos) {
            if (j & 1) {
                curSubset += curSet[curSetPos];
            }
        }

        for (ull j = curSubsetPos; j < curLen; ++j) {
            std::sort(subsets[i].begin(), subsets[i].end());
            if (subsets[j].find(curSubset) != std::string::npos) {
                subsets.push_back(subsets[j] + curSubset);
            }
        }
    }

    findAllMultiSubsets(setCharCnt, subsets, curSubsetPos + subsets.size() - curLen);
}


int
main()
{
    string str;
    cin >> str;

    map<char, unsigned> setCharCnt;

    for (char c: str) {
        setCharCnt[c]++;
    }

    vector<string> subsets;

    string curSet;
    for (auto &[c, cnt] : setCharCnt) {
        if (cnt) {
            curSet += c;
            --cnt;
        }
    }

    ull curSetCard = (1ull << curSet.size());
    for (ull i = 0; i < curSetCard; ++i) {
        string curSubset;

        for (ull j = i, curSetPos = 0; j; j >>= 1, ++curSetPos) {
            if (j & 1) {
                curSubset += curSet[curSetPos];
            }
        }

        subsets.push_back(curSubset);
    }

    findAllMultiSubsets(setCharCnt, subsets, 1);

    for (const string& subset : subsets) {
        cout << subset << endl;
    }

    return 0;
}
