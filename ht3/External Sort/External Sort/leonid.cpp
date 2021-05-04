//
//  leonid.cpp
//  External Sort
//
//  Created by Лабутин Антон Александрович on 25.04.2021.
//

#include <stdio.h>
#include <string.h>
#include <unistd.h>

const int LEN = 10002;

int
main()
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");
    FILE* tmp1 = fopen("tmp1.txt", "w+");
    FILE* tmp2 = fopen("tmp2.txt", "w+");
    FILE* tmp3 = fopen("tmp3.txt", "w+");

    char s[LEN];
    char s1[LEN];
    char s2[LEN];

    size_t n = 0; // count of strings in 'in'

    while(fgets(s, LEN, in)) {
        ++n;
        fputs(s, tmp3);
    }
	fputc('\n',tmp3);

    size_t series_size = 1, merge_size = 2;
    while(merge_size < 2 * n) {
        truncate("tmp3.txt", ftell(tmp3)); // укоротить файл до длинны ftell(tmp3) = позиции в файле

        rewind(tmp3); // установить указатель чтения / записи в начало
        rewind(tmp1);
        rewind(tmp2);

        bool file1 = true;
        size_t count = 0;
        while(fgets(s, LEN, tmp3)) {
            ++count;
            fputs(s, file1 ? tmp1 : tmp2);
            if(count == series_size)
            {
                count = 0;
                file1 = !file1;
            }
        }

        truncate("tmp1.txt", ftell(tmp1));
        truncate("tmp2.txt", ftell(tmp2));

        rewind(tmp1);
        rewind(tmp2);
        rewind(tmp3);

        size_t i = 0, j = 0;
        char* k1 = fgets(s1, LEN, tmp1);
        char* k2 = fgets(s2, LEN, tmp2);
        while(k1 && k2)  {
            while(k1 && k2)  {
                if(strcmp(s1,s2)<0)  {
                    fputs(s1, tmp3);
                    k1 = fgets(s1, LEN, tmp1);
                    if(++i == series_size)
                        break;
                }
                else {
                    fputs(s2, tmp3);
                    k2 = fgets(s2, LEN, tmp2);
                    if (++j == series_size) {
                        break;
                    }
                }
            }
            while(k1) {
                if(i == series_size) {
                    break;
                }
                fputs(s1, tmp3);
                k1 = fgets(s1, LEN, tmp1);
                ++i;
            }
            while(k2) {
                if(j == series_size) {
                    break;
                }
                fputs(s2, tmp3);
                k2 = fgets(s2, LEN, tmp2);
                ++j;
            }
            i = 0;
            j = 0;
        }
        while(k1) {
            fputs(s1, tmp3);
            k1 = fgets(s1, LEN, tmp1);
        }
        while(k2) {
            fputs(s2, tmp3);
            k2 = fgets(s2, LEN, tmp2);
        }
        series_size = merge_size;
        merge_size *= 2;
    }
    rewind(tmp3);
    while(fgets(s, LEN, tmp3)) {
        fputs(s, out);
    }
}
