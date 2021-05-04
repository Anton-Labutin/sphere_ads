#include <stdio.h>
#include <string>
#include <vector>
#include "huff_tree.hpp"
#include "huff_builder.hpp"
#include "bitio.hpp"
#include <assert.h>

using namespace std;


vector<int> 
get_counters(string name) 
{
    vector<int> counters(257); // 257 = число возможных символов + символ конца файла
    FILE *in = fopen(name.c_str(), "rb");
    assert(in != nullptr);
    for (int c = getc(in); c != EOF; c = getc(in)) {
        ++counters[c];
    }

    fclose(in);
    counters[256]++; // конец файла

    return counters;
}


int 
main()
{
    {
        auto counters = get_counters("input.txt");
        auto tree = build_tree(counters);

        bitio_out bout("output.bin");
        FILE *in = fopen("input.txt", "rb");
        out_tree_and_file(tree, bout, in);
        fclose(in);
        clear_tree(tree);
    }
    {
        bitio_in bin("output.bin");
        auto tree = in_tree(bin);
        out_decoded(tree, bin, "input_new.txt");
    }

    return 0;
}
