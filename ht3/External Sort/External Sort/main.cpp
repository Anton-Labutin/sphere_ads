//
//  main.cpp
//  External Sort
//
//  Created by Лабутин Антон Александрович on 21.04.2021.
//

/*
 Внешняя сортировка

 В файле "input.txt" содержатся строки символов, длина каждой строки не превышает 10000 байт. Файл нужно отсортировать в лексикографическом порядке и вывести результат в файл "output.txt". Вот беда, файл занимает много мегабайт, а в вашем распоряжение оказывается вычислительная система с памятью всего в 256 килобайт. Но файл должен быть отсортирован!

 Input format

 Будьте внимательны, в этой задаче придётся использовать файловый ввод/вывод. Входной файл "input.txt" содержит неотсортированные строки символов без управляющих и пробельных (ASCII коды от 33 до 126).
 Output format

 Отсортированная версия входного файла.
 Examples

 Input in input.txt

 aksjdfhaskjdh
 alsdajsldjaslkdjaslkdj
 asldkjaslkdjlkjq
 qweqweqweqweqweqwe
 pqiwepoiqwpoeiqwpeoiqwpeo
 qpeoiqwpoeiqwpe

 Output in output.txt

 aksjdfhaskjdh
 alsdajsldjaslkdjaslkdj
 asldkjaslkdjlkjq
 pqiwepoiqwpoeiqwpeoiqwpeo
 qpeoiqwpoeiqwpe
 qweqweqweqweqweqwe
 */

#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>

using namespace std;


void
externalSort(FILE *input, FILE *output)
{
    const char *tape1File = "tape1.txt";
    const char *tape2File = "tape2.txt";
    const char *mergeTapeFile = "merge_tape.txt";
    const char STR_SEPARATOR = '\n';
    const unsigned MAX_STR_SIZE = 10000;

    FILE *tape1 = fopen(tape1File, "rw");
    FILE *tape2 = fopen(tape2File, "rw");
    FILE *mergeTape = fopen(mergeTapeFile, "rw");

    char str[MAX_STR_SIZE + 1];
    bool writeToTape1 = true;
    bool isReadFirstStr = true;
    bool isReadSecondStr = true;

    while (fscanf(input, "%s", str) > 0) {
        cout << "Read : " << str << endl;
        if (writeToTape1) {
            if (! isReadFirstStr) {
                fprintf(tape1, "%c", STR_SEPARATOR);
            }

            fprintf(tape1, "%s", str);

            writeToTape1 = false;
            isReadFirstStr = false;
        } else {
            if (! isReadSecondStr) {
                fprintf(tape2, "%c", STR_SEPARATOR);
            }
            fprintf(tape2, "%s", str);

            writeToTape1 = true;
            isReadSecondStr = false;
        }
    }

    char str1[MAX_STR_SIZE + 1];
    char str2[MAX_STR_SIZE + 1];

    bool isReadFromTape1 = false;
    bool isReadFromTape2 = false;
    bool isReadFirstStrFromTape1 = true;
    bool isReadFirstStrFromTape2 = true;

    while (! feof(tape1) || ! feof(tape2)) {
        if (! feof(tape1)) {
            fscanf(tape1, "%s", str1);
            cout << str1 << endl;
            isReadFromTape1 = true;
        }
        if (! feof(tape2)) {
            fscanf(tape2, "%s", str2);
            cout << str2 << endl;
            isReadFromTape2 = true;
        }

        if (isReadFromTape1 && isReadFromTape2) {
            if (strcmp(str1, str2) < 0) {
                if (! isReadFirstStrFromTape1) {
                    fprintf(mergeTape, "%c", STR_SEPARATOR);
                }

                fprintf(mergeTape, "%s", str1);
                fprintf(mergeTape, "%c", STR_SEPARATOR);
                fprintf(mergeTape, "%s", str2);
            } else {
                if (! isReadFirstStrFromTape2) {
                    fprintf(mergeTape, "%c", STR_SEPARATOR);
                }

                fprintf(mergeTape, "%s", str2);
                fprintf(mergeTape, "%c", STR_SEPARATOR);
                fprintf(mergeTape, "%s", str1);
            }
        } else {
            while (isReadFromTape1) {
                if (! isReadFirstStrFromTape1) {
                    fprintf(mergeTape, "%c", STR_SEPARATOR);
                }
                fprintf(mergeTape, "%s", str1);
            }

            while (isReadFromTape2) {
                if (! isReadFirstStrFromTape2) {
                    fprintf(mergeTape, "%c", STR_SEPARATOR);
                }
                fprintf(mergeTape, "%s", str2);
            }
        }

        cout << ferror(mergeTape) << endl;

        isReadFromTape1 = false;
        isReadFromTape2 = false;
        isReadFirstStrFromTape1 = false;
        isReadFirstStrFromTape2 = false;
    }
}


int
main()
{
    const char *inputFile = "input.txt";
    const char *outputFile = "output.txt";

    FILE *input = fopen(inputFile, "r");
    FILE *output = fopen(outputFile, "w");

    externalSort(input, output);

    return 0;
}
