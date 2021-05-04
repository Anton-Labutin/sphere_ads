#pragma once

#include <vector>
#include "huff_tree.hpp"
#include "bitio.hpp"
#include "pq.hpp"

using namespace std;


struct tree_great {
    bool 
    operator () (tree const *l, tree const *r) {
        return l -> count <  r -> count;
    }
};


tree* 
build_tree(vector<int> const &counters) 
{
    int size = 0;
    for (auto c : counters) {
        size += c != 0;
    }

    priority_queue<tree*, tree_great> pq(size);
    for (int i = 0; i < counters.size(); ++i) {
        if (counters[i] == 0) {
            continue;
        }

        auto n = new tree();
        n -> count = counters[i];
        n -> sym = i;
        pq.insert(n);
    }

    while (pq.size() > 1) {
        auto right = *pq.fetchMin();
        pq.removeMin();
        auto left = *pq.fetchMin();
        pq.removeMin();

        tree *sum = new tree();
        sum -> count = left -> count + right -> count;
        sum -> left = left;
        sum -> right = right;
        pq.insert(sum);
    }

    auto ret = *pq.fetchMin();
    pq.removeMin();

    return ret;
}

void 
clear_tree(tree *) 
{
    return;
}


void 
walk(tree *t, vector<string> &codes, string code)
{
    if (t -> left != nullptr) {
        walk(t -> left, codes, code + "0");
    }

    if (t -> right != nullptr) {
        walk(t -> right, codes, code + "1");
    }

    if (t -> left == nullptr && t -> right == nullptr) {
        codes[t -> sym] = code;
    }
}


void 
out_tree_and_file(tree *t, bitio_out bout, FILE *fin) 
{
    vector<string> codes(257); 
    
    walk(t, codes, "");
    unsigned non_empties = 0;

    for (int c = 0; c < 257; ++c) {
        if (codes[c].empty()) {
            continue;
        }
        ++non_empties;
        // if (c < 32) {
        //    printf("%0x2f ", c); // управляющие символы
        //} else {
        //    printf("'%c' ", c);
        //}
        //printf("%s\n", codes[c].c_str());
    }

    // 9 - число бит для кодирования длины последовательности
    bout.out(9, non_empties);

    for (int c = 0; c < 257; ++c) {
        if (codes[c].empty()) continue;

        bout.out(9, c);
        // 5 - число бит для кодов символов от 0 до 32
        bout.out(5, (unsigned) codes[c].size());

        for (auto q : codes[c]) {
            bout.out(q != '0');
        }
    }

    rewind(fin);
    for (int c = getc(fin); c != EOF; c = getc(fin)) {
        for (auto q : codes[c]) {
            bout.out(q != '0');
        }
    }

    for (auto q : codes[256]) {
        bout.out(q != '0');
    }
}

tree* 
in_tree(bitio_in &bin) 
{
    // vector<string> codes(257);
    tree *root = new tree();
    unsigned non_empties = bin.in(9);
    
    for (unsigned i = 0; i < non_empties; ++i) {
        auto curr = root;
        unsigned c = bin.in(9);
        unsigned len = bin.in(5);
        for (unsigned q = 0; q < len; ++q) {
            bool bit = bin.in(); 
            //codes[c].push_back('0' + bin.in());
            if (bit && curr -> right == nullptr) {
                curr -> right = new tree();
            } else {
                if (! bit && curr -> left == nullptr) {
                    curr -> left = new tree();
                }
            }

            if (bit) {
                curr = curr -> right;
            } else {
                curr = curr -> left;
            }
        }

        curr -> sym = c; 

       // printf("'%c'='%s'\n", c, codes[c].c_str());
    }

    return root;
}


void 
out_decoded(tree *t, bitio_in &bin, string const &name) 
{
    FILE *out = fopen(name.c_str(), "wb");
    auto curr = t;
    
    for (;;) {
        auto bit = bin.in();
        if (bit == 0) {
            curr = curr -> left;
        } else {
            curr = curr -> right;
        }

        if (curr -> sym == 256) {
            break;
        }

        if (curr -> sym >= 0) {
            putc(curr -> sym, out);
            curr = t;
        }
    }

    fclose(out);
}
