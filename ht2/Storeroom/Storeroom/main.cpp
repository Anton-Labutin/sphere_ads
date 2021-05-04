//
//  main.cpp
//  Storeroom
//
//  Created by Лабутин Антон Александрович on 22.03.2021.
//

/*
 Камера хранения

 На железнодорожном вокзале столицы Бурляндии решили установить новую автоматическую камеру хранения. Для этого потребовалось узнать, сколько ячеек одновременно занято хранящимся багажом. Было установлено несколько датчиков использования старой камеры хранения, фиксировавших момент прихода пассажира и занятия им ячейки, а так же момент ухода пассажира и момент освобождения им ячейки. Протокол прихода и ухода пассажиров за одни сутки приведён далее. Ячейка не освобождается мгновенно, поэтому если в какое-то время один пассажир ушёл и в это же время пришёл другой пассажир, требуется две ячейки. Определите максимальное количество одновременно занятых ячеек, наблюдаемое в течении суток.

 Камера открыта круглосуточно. Времена прихода и ухода пассажиров находятся в пределах одних суток. В 00:00 камера хранения пуста.

 Формат входных данных
 N (количество пассажиров, 1⩽N⩽1000000).

 HA1:MA1 HD1:MD1
 ...
 HAN:MAN HDN:MDN

 Формат результата
 MaximumNumberOfBusyCells

 Примеры

 Входные данные
 5
 02:18 11:54
 03:18 04:16
 00:26 20:41
 17:19 20:48
 08:42 23:45

 Результат работы
 3

 Входные данные
 10
 17:59 22:58
 12:25 16:06
 09:05 18:39
 08:34 23:23
 15:59 22:53
 15:55 21:20
 18:05 22:08
 03:48 22:23
 12:50 14:41
 05:46 10:41

 Результат работы
 7
 */

#include <cstdio>
#include <vector>
#include <algorithm>

using std::vector;


constexpr unsigned MIN_PER_HOUR = 60;


using TimePoint = struct TimePoint {
	TimePoint(unsigned hour, unsigned min, bool isArr)
    	: minCntFromMidnight(min + hour * MIN_PER_HOUR), isArrival(isArr)
    {}

    unsigned minCntFromMidnight;
    bool isArrival;
};


bool
compTimes(const TimePoint& tp1, const TimePoint& tp2)
{
    return (tp1.minCntFromMidnight < tp2.minCntFromMidnight) ||
    (tp1.minCntFromMidnight == tp2.minCntFromMidnight &&
     tp1.isArrival > tp2.isArrival);
}


unsigned
calcMaxNumOfBusyCells(vector<TimePoint>& times)
{
    std::sort(times.begin(), times.end(), compTimes);

    unsigned maxNumOfBusyCells = 0;
    unsigned curMaxNumOfBusyCells = 0;

    for (const auto& tp : times) {
        curMaxNumOfBusyCells += (tp.isArrival ? 1 : -1);

        if (curMaxNumOfBusyCells > maxNumOfBusyCells) {
            maxNumOfBusyCells = curMaxNumOfBusyCells;
        }
    }

    return maxNumOfBusyCells;
}


int
main()
{
    unsigned N;
    unsigned hour, min;

    scanf("%u", &N);
    vector<TimePoint> times;
    for (unsigned i = 0; i < N; ++i) {
        scanf("%u:%u", &hour, &min);
        times.push_back({hour, min, true});

        scanf("%u:%u", &hour, &min);
        times.push_back({hour, min, false});
    }

    unsigned maxNumOfBusyCells = calcMaxNumOfBusyCells(times);

    printf("%u\n", maxNumOfBusyCells);

    return 0;
}
