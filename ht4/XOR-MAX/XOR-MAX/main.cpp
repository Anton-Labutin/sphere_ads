//
//  main.cpp
//  XOR-MAX
//
//  Created by Лабутин Антон Александрович on 12.04.2021.
//

/*
 Запросы XOR и MAX

 Достаточно легко быстро выполнить операции XOR или MAX над всеми элементами массива или над его срезом. Можно ли это делать быстро, если элементы массива постоянно меняются?

 Input format

 В первой строке файла содержатся два числа: количество элементов в массиве V: 5⩽N⩽1000000 и количество запросов 1⩽M⩽1000000. Каждый элемент массива имеет тип данных int.

 В следующих N строках перечислены все элементы массива.

 Далее следует M строк запросов. Каждый запрос — отдельная строка, состоящая из кода запроса, который может быть равен 1, 2 или 3 и аргументов запроса.

 Запросы с кодами 1 и 2 содержат два аргумента: начало 0⩽L<N и конец отрезка 0⩽R<N подмассива, L⩽R.

 В ответ на этот запрос программа должна вывести значение либо операции XOR (если код операции 1), либо операции MAX (если код операции 2) над элементами массива от L до R включительно, над отрезком, закрытого на левом и правом концах.

 Запрос с кодом 3 тоже содержит два аргумента, первый из которых есть номер элемента массива V, а второй – его новое значение.

 Количество выведенных строк должно совпадать с количеством запросов с кодами 1 или 2.

 Output format

 Протокол работы программы — результаты исполнения запросов с кодами 1 и 2.

 Examples

 Input

 8 10
 3
 1
 7
 4
 5
 8
 5
 7
 3 0 6
 1 0 5
 1 5 5
 2 4 7
 1 1 3
 3 1 3
 1 6 7
 1 6 6
 1 3 6
 3 1 2

 Output

 9
 8
 8
 2
 2
 5
 12
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <limits>
#include <cassert>

using namespace std;

enum REQUEST {
	XOR = 1,
    MAX = 2,
    UPDATE = 3
};


class SegTree {
    using NODE = struct BHEAP_NODE {
        int maxEl = numeric_limits<int>::min();
        int xorEl = 0;
    };

    vector<NODE> bheap;
    size_t arrSize = 0;

    void
    UpdateTree(size_t bheapIdx)
    {
        size_t leftChildIdx = (bheapIdx << 1) + 1;
        size_t rightChildIdx = leftChildIdx + 1;

        bool maxElChanged = false;
        bool xorElChanged = false;

        int newMax = max(bheap[leftChildIdx].maxEl,
                         bheap[rightChildIdx].maxEl);

        if (bheap[bheapIdx].maxEl != newMax) {
            bheap[bheapIdx].maxEl = newMax;
            maxElChanged = true;
        }

        int newXor = bheap[leftChildIdx].xorEl xor
        			bheap[rightChildIdx].xorEl;

        if (bheap[bheapIdx].xorEl != newXor) {
            bheap[bheapIdx].xorEl = newXor;
            xorElChanged = true;
        }

        if (bheapIdx > 0 && (maxElChanged || xorElChanged)) {
            UpdateTree(((bheapIdx + 1) >> 1) - 1);
        }
    }

    int
    CalcMAX_(size_t leftIdx, size_t rightIdx)
    {
		int maxVal = numeric_limits<int>::min();

    	if (leftIdx % 2 == 0) {
        	maxVal = max(maxVal, bheap[leftIdx++].maxEl);
    	}

    	if (rightIdx % 2 == 1) {
        	maxVal = max(maxVal, bheap[rightIdx--].maxEl);
    	}

    	if (leftIdx < rightIdx) {
        	maxVal = max(maxVal, CalcMAX_(((leftIdx + 1) >> 1) - 1, ((rightIdx + 1) >> 1) - 1));
    	}

        return maxVal;
    }

    int
    CalcXOR_(size_t leftIdx, size_t rightIdx)
    {
        int xorVal = 0;

        if (leftIdx % 2 == 0) {
            xorVal = xorVal xor bheap[leftIdx++].xorEl;
        }

        if (rightIdx % 2 == 1) {
            xorVal = xorVal xor bheap[rightIdx--].xorEl;
        }

        if (leftIdx < rightIdx) {
            xorVal = xorVal xor CalcXOR_(((leftIdx + 1) >> 1) - 1, ((rightIdx + 1) >> 1) - 1);
        }

        return xorVal;
    }

public:
	SegTree(size_t size)
	{
        arrSize = size;

        size_t heapSize = 1;
        while (heapSize < size) {
            heapSize <<= 1;
        }

        // cout << "heapSize = " << heapSize - 1 << endl;

        bheap = vector<NODE>((heapSize << 1) - 1);
    }

    void
    Insert(size_t arrIdx, int el)
    {
        assert(arrIdx < arrSize);

        size_t bheapIdx = (bheap.size() >> 1) + arrIdx;
        bheap[bheapIdx] = {el, el};

        UpdateTree(((bheapIdx + 1) >> 1) - 1);
    }

	int
    CalcXOR(size_t leftIdx, size_t rightIdx)
    {
        leftIdx += (bheap.size() >> 1);
        rightIdx += (bheap.size() >> 1);

        return CalcXOR_(leftIdx, rightIdx);
    }

    int
    CalcMAX(size_t leftIdx, size_t rightIdx)
    {
        leftIdx += (bheap.size() >> 1);
        rightIdx += (bheap.size() >> 1);

        return CalcMAX_(leftIdx, rightIdx);
    }

    void
    Update(size_t arrIdx, int arrVal)
    {
        assert(arrIdx < arrSize);

        size_t bheapIdx = arrIdx + (((bheap.size() + 1) >> 1) - 1);
        bheap[bheapIdx].maxEl = arrVal;
        bheap[bheapIdx].xorEl = arrVal;

        UpdateTree(((bheapIdx + 1) >> 1) - 1);
    }

    void
    Print() const
    {
        cout << "MAX: ";
        for (size_t i = 0; i < bheap.size(); ++i) {
            cout << bheap[i].maxEl << " ";
        }
        cout << endl;

        cout << "XOR: ";
        for (size_t i = 0; i < bheap.size(); ++i) {
            cout << bheap[i].xorEl << " ";
        }
        cout << endl;
    }
};

int
main()
{
    size_t numCnt;
    size_t reqCnt;
    scanf("%zu%zu", &numCnt, &reqCnt);

    int num;
    SegTree segTree(numCnt);
    for (size_t i = 0; i < numCnt; ++i) {
        scanf("%d", &num);
        segTree.Insert(i, num);
    }

    // segTree.Print();

    {
    	int reqCode;
    	size_t leftIdx, rightIdx;
    	size_t arrIdx;
        int arrVal;

    	for (size_t i = 0; i < reqCnt; ++i) {
            scanf("%d", &reqCode);

        	switch(reqCode) {
            	case REQUEST::XOR:
                    scanf("%zu%zu", &leftIdx, &rightIdx);
                    printf("%d\n", segTree.CalcXOR(leftIdx, rightIdx));
                	break;
            	case REQUEST::MAX:
                    scanf("%zu%zu", &leftIdx, &rightIdx);
                    printf("%d\n", segTree.CalcMAX(leftIdx, rightIdx));
                	break;
            	case REQUEST::UPDATE:
                    scanf("%zu%d", &arrIdx, &arrVal);
                    segTree.Update(arrIdx, arrVal);
                    // segTree.Print();
                	break;
            	default:
                	throw std::invalid_argument("reqCode");
        	}
    	}
    }

    return 0;
}
