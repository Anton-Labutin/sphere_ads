//
//  main.cpp
//  XORMAX
//
//  Created by Лабутин Антон Александрович on 20.04.2021.
//

/*
 Исключительные исключающие или

 Умеете ли вы быстро находить требуемое, например, в массиве чисел обнаружить такое число, операция XOR которого с заданным даёт наибольший результат?

 Input format

 В первой строке входного файла — число команд 10⩽N⩽500000. Каждая из последующих N строк имеет один и тот же формат: тип команды и аргумент команды. Аргумент команды — натуральное число от 1 до 4'000'000'000. Все команды оперируют с одним массивом, пустым вначале. Ни в один момент работы программы массив не может содержать двух или более одинаковых элементов.

 Команда типа 1 вставляет свой аргумент M в массив. Если элемент с таким значением уже существовал, то операция эквивалентна пустой.

 Команда типа 2 удаляет из массива свой аргумент. Если элемента с таким значением в массиве не существует, ничего не происходит.

 Команда типа 3 — найти такой элемент в массиве Ai, что операция исключающего или (XOR) над этим элементом и аргументом M команды даст наибольшее из всех возможных значениий. Это — единственная команда, после которой требуется вывести результат операции, найденный элемент Ai.

 Output format

 Должно быть выведено количество строк, совпадающее с числом команд типа 3. Для каждой команды типа 3 нужно вывести соответствующий элемент Ai.

 В приведённом примере после первых четырёх команд массив содержит числа 6, 19, 33, 55. Для числа 10 значения операций XOR с элементами массива следующие: 6 XOR 10 = 12, 19 XOR 10 = 25, 33 XOR 10 = 43 и 55 XOR 10 = 61. Поэтому в ответ на этот запрос следует вывести 55.

 Examples

 Input

 9
 1 6
 1 19
 1 33
 1 55
 3 10
 3 20
 3 30
 3 40
 3 50

 Output

 55
 33
 33
 19
 6
 */

#include <iostream>

using namespace std;

using ull = unsigned long long;

constexpr size_t BITS_PER_BYTE = 8;


class BitTree {
    enum BitValue {
		ZERO_BIT = 0,
        UNIT_BIT = 1
    };

    struct Node {
        BitValue bit = ZERO_BIT;
        ull number;

        Node *parent = nullptr;
        Node *zeroBit = nullptr;
        Node *unitBit = nullptr;
    };

    Node *zeroBitRoot = nullptr;
    Node *unitBitRoot = nullptr;

public:
    BitTree()
    {
        zeroBitRoot = new Node;
        zeroBitRoot -> bit = ZERO_BIT;

        unitBitRoot = new Node;
        unitBitRoot -> bit = UNIT_BIT;
    }

    void
    Insert(ull num);

    void
    Delete(ull num);

    ull
    FindXORMax(ull num) const;
};


void
BitTree::Insert(ull num)
{
    size_t numBitsCnt = BITS_PER_BYTE * sizeof(decltype(num));
    size_t bitsShift = numBitsCnt - 1;

    Node *curNode = (((num >> bitsShift) & 1) == 0) ? zeroBitRoot : unitBitRoot;

    while (bitsShift--) {
        if (((num >> bitsShift) & 1) == 0) {
            if (curNode -> zeroBit == nullptr) {
                curNode -> zeroBit = new Node;
                curNode -> zeroBit -> parent = curNode;
                curNode -> zeroBit -> bit = ZERO_BIT;
            }

            curNode = curNode -> zeroBit;
        } else {
            if (curNode -> unitBit == nullptr) {
                curNode -> unitBit = new Node;
                curNode -> unitBit -> parent = curNode;
                curNode -> unitBit -> bit = UNIT_BIT;
            }

            curNode = curNode -> unitBit;
        }
    }

    curNode -> number = num;
}


void
BitTree::Delete(ull num)
{
    size_t numBitsCnt = BITS_PER_BYTE * sizeof(decltype(num));
    size_t bitsShift = numBitsCnt - 1;

    Node *curNode = (((num >> bitsShift) & 1) == 0) ? zeroBitRoot : unitBitRoot;

    while (curNode && bitsShift) {
        if (((num >> --bitsShift) & 1) == 0) {
            curNode = curNode -> zeroBit;
        } else {
            curNode = curNode -> unitBit;
        }
    }

    while (curNode && (curNode -> parent) &&
           (curNode -> zeroBit == nullptr) &&
           (curNode -> unitBit == nullptr)) {
        if (curNode -> bit == ZERO_BIT) {
            curNode = curNode -> parent;
            delete curNode -> zeroBit;
            curNode -> zeroBit = nullptr;
        } else {
            curNode = curNode -> parent;
            delete curNode -> unitBit;
            curNode -> unitBit = nullptr;
        }
    }
}


ull
BitTree::FindXORMax(ull num) const
{
    size_t numBitsCnt = BITS_PER_BYTE * sizeof(decltype(num));
    size_t bitsShift = numBitsCnt - 1;

    Node *curNode = ((num >> bitsShift) & 1) ? zeroBitRoot : unitBitRoot;

    if ((curNode -> zeroBit == nullptr) && (curNode -> unitBit == nullptr)) {
        curNode = (curNode == unitBitRoot) ? zeroBitRoot : unitBitRoot;
    }

    while ((curNode -> zeroBit) || (curNode -> unitBit)) {
        if (((num >> --bitsShift) & 1) == 0) {
            curNode = (curNode -> unitBit) ? (curNode -> unitBit) : (curNode -> zeroBit);
        } else {
            curNode = (curNode -> zeroBit) ? (curNode -> zeroBit) : (curNode -> unitBit);
        }
    }

    return curNode -> number;
}


enum CommandType {
    COMMAND_ONE = 1,
    COMMAND_TWO = 2,
    COMMAND_THREE = 3
};


int
main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned N;
    cin >> N;

    BitTree bitTree;

    ull arg;
    int com;
    for (unsigned i = 0; i < N; ++i) {
        cin >> com >> arg;

        switch(com) {
            case COMMAND_ONE:
                bitTree.Insert(arg);
                break;
            case COMMAND_TWO:
                bitTree.Delete(arg);
                break;
            case COMMAND_THREE:
                cout << bitTree.FindXORMax(arg) << endl;
                break;
        }
    }

    return 0;
}
