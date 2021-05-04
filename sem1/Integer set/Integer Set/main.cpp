//
//  main.cpp
//  Seminar 1
//
//  Created by Лабутин Антон Александрович on 09.03.2021.
//

#include <cstdio>
#include <iostream>
#include <cassert>


// множество чисел 0, 1, 2, ..., N - 1
class MyIntSet {
public:
    using ChunkType = unsigned long long; // unsigned - for bit operations
    const size_t CHUNKSIZE = 64; // 64 bits are faster than 8 bits times 8

    MyIntSet(size_t size)
    {
        chunksCnt = (size + CHUNKSIZE - 1) / CHUNKSIZE; // ceiling round
        body = new ChunkType[chunksCnt];
        setSize = size;

        for (size_t i = 0; i < chunksCnt; ++i) {
            body[i] = 0; // ith number is not in the set; otherwise body[i] = 1;
        }

        printf("Size used: %zu bytes\n", chunksCnt * sizeof(ChunkType));
    }

    void
    Insert(size_t elem)
    {
        if (elem >= setSize) {
            return;
        }

        body[elem / CHUNKSIZE] |= 1 << (elem % CHUNKSIZE); // set (elem % CHUNKSIZE)th bit = 1 in the (elem / CHUNKSIZE)th chunk
    }

    void
    Erase(size_t elem)
    {
        if (elem >= setSize) {
            return;
        }

        body[elem / CHUNKSIZE] &= ~(1 << (elem % CHUNKSIZE)); // set (elem % CHUNKSIZE)th bit = 0 in the (elem / CHUNKSIZE)th chunk
    }

    bool
    In(size_t elem)
    {
        if (elem >= setSize) {
            return false;
        }

        return (body[elem / CHUNKSIZE] >> (elem % CHUNKSIZE)) & 1;
    }

    ~MyIntSet()
    {
        delete[] body;
    }
private:
    ChunkType *body;
    size_t setSize;
    size_t chunksCnt;
};


int
main(int argc, const char * argv[])
{
    MyIntSet s1(1000);

    for (int i = 0; i < 10; ++i) {
        s1.Insert(i * i);
    }

    assert(s1.In(64));
    s1.Erase(64);
    assert(! s1.In(64));

    return 0;
}
