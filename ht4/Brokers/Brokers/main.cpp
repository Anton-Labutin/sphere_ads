//
//  main.cpp
//  Brokers
//
//  Created by Лабутин Антон Александрович on 09.04.2021.
//

/*
 Брокеры

 В стране Бурляндии фирма «Котлетный рай» имеет много отделений, работающих сравнительно автономно. После неких экономических преобразований такая форма функционирования оказалась невыгодной и фирма решила сливать капиталы отделений, образуя укрупнённые департаменты, отвечающие за несколько отделений сразу. Цель фирмы — слить все отделения в один громадный департамент, владеющий всеми капиталами.

 Первая проблема заключается в том, что по законам Бурляндии операция слияния капиталов отделений должна проводиться государственной брокерской службой, которая не может производить более одной операции слияния в одной фирме одновременно.

 Вторая проблема состоит в том, что брокерская служба берёт за свои услуги один процент всех средств, получившихся в результате слияния двух подразделений. Важно спланировать порядок операций слияния таким образом, чтобы фирма потратила на слияние как можно меньшую сумму.

 Input format

 На вход программы подаётся число отделений 2⩽N⩽1000000, за которым следует N капиталов отделений 1⩽Ci⩽1000000.
 Output format

 T — минимальная сумма из возможных, которую должна заплатить брокерам фирма «Котлетный рай», с двумя знаками после запятой.
 Examples

 Input

 5
 1
 2
 3
 4
 5

 Output

 0.33

 Input

 10
 2
 10
 100
 30
 7
 4
 15
 2
 15
 80

 Output

 6.52
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>


using ull = unsigned long long;

using namespace std;


class MinPQueue {
	vector<ull> pqueue;
    size_t elCnt;

    size_t
    GetParentIdx(size_t i) const;

    size_t
    GetLeftChildIdx(size_t i) const;

    size_t
    GetRightChildIdx(size_t i) const;

    void
    swap(size_t i, size_t j);

    void
    Heapify(size_t i);

public:
	MinPQueue(size_t maxSize = 0)
    	: pqueue(maxSize + 1, 0), elCnt(0)
    {}

	void
    Insert(ull el);

    ull
    ExtractMin();

    ull
    FetchMin();

    size_t
    GetElCnt() const;

    void
    Print() const;
};


void
MinPQueue::Print() const
{
    for (size_t i = 1; i <= elCnt; ++i) {
        cout << pqueue[i] << " ";
    }
    cout << endl;
}


size_t
MinPQueue::GetParentIdx(size_t i) const
{
    return i / 2;
}


size_t
MinPQueue::GetLeftChildIdx(size_t i) const
{
    return i + i;
}


size_t
MinPQueue::GetRightChildIdx(size_t i) const
{
    return i + i + 1;
}


void
MinPQueue::swap(size_t i, size_t j)
{
    std::swap(pqueue[i], pqueue[j]);
}


void
MinPQueue::Heapify(size_t i)
{
    while (true) {
        size_t left = GetLeftChildIdx(i);
        size_t right = GetRightChildIdx(i);
        size_t minIdx = i;

        if (left <= elCnt && pqueue[left] < pqueue[minIdx]) {
            minIdx = left;
        }

        if (right <= elCnt && pqueue[right] < pqueue[minIdx]) {
            minIdx = right;
        }

        if (minIdx == i) {
            break;
        }

        swap(i, minIdx);
        i = minIdx;
    }
}


void
MinPQueue::Insert(ull el)
{
    if (elCnt == pqueue.size()) {
        throw std::runtime_error("Insert: queue is full");
    }

    pqueue[++elCnt] = el;
    for (size_t i = elCnt;
         i > 1 && pqueue[i] < pqueue[GetParentIdx(i)];
         i = GetParentIdx(i)) {
        swap(i, GetParentIdx(i));
    }
}


ull
MinPQueue::FetchMin()
{
    if (elCnt == 0) {
        throw std::runtime_error("fetchMin: queue is empty");
    }

    return pqueue[1];
}


ull
MinPQueue::ExtractMin()
{
    ull min = FetchMin();
    pqueue[1] = pqueue[elCnt--];
    Heapify(1);

    return min;
}


size_t
MinPQueue::GetElCnt() const
{
    return elCnt;
}


int
main()
{
    ull N;
    cin >> N;

    ull cap;
    MinPQueue capitals(N);
    for (ull i = 0; i < N; ++i) {
        cin >> cap;
        capitals.Insert(cap);
    }

    ull pay = 0;
    while (capitals.GetElCnt() > 1) {
        // capitals.Print();
        ull minCap1 = capitals.ExtractMin();
        ull minCap2 = capitals.ExtractMin();
        pay += (minCap1 + minCap2);
        capitals.Insert(minCap1 + minCap2);
    }

    cout << fixed << setprecision(2) << pay / 100.0 << endl;

    return 0;
}
