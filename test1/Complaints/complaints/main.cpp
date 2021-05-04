//
//  main.cpp
//  complaints
//
//  Created by Лабутин Антон Александрович on 23.03.2021.
//

/*
 Офисное здание

 В одной очень большой стране в одном очень большом городе стояло очень-очень большое здание, в котором граждане этой страны подавали жалобы на других граждан. Так как жалобщиков было очень много, оно работало круглосуточно, но каждый из посетителей, пришедших в какое-то время после нуля часов, был обязан покинуть здание до 24 часов.

 Клерков, принимающих жалобы, было не очень много, из-за чего гражданам приходилось сидеть и ждать в очереди, пока нужный клерк освободится.

 На эту организацию, принимающую жалобы, в неё же поступила жалоба, что жалобы рассматриваются недостаточно быстро и вам было поручено определить, а сколько же жалобщиков одновременно находится в здании. К счастью для вас, во всех жителей этой страны были встроены чипы, точно определяющие положение в любой момент времени.

 Вам был дан доступ к данным за сутки. В 00:00:00 здание жалобщиков не ещё не содержало, а в 24:00:00 уже не содержало, так как все жалующиеся покинули здание. Дверей в здании много, поэтому вполне могли случаться такие ситуации, когда в одну и ту же секунду один жалобщик прибывал, а другой — покидал помещение. В таком случае оба считались находящимися в здании.

 Ваша задача — определить максимальное число жалобщиков, одновременно находящихся в здании.

 Input format

 На вход программы подаётся число 1⩽N⩽200000 — число записей в базе данных. Каждая запись имеет содержит два времени с точностью до секунд — время прибытия и время убытия в формате HH:MM:SS.
 Output format

 Одно число — максимальное количество жалобщиков, одновременно находящихся в здании.
 Examples

 Input

 5
 02:03:42 20:44:18
 02:01:25 13:54:01
 13:04:48 23:39:34
 02:08:16 19:30:44
 01:02:34 08:00:07

 Output

 4
 */

#include <cstdio>
#include <vector>
#include <algorithm>

using std::vector;

constexpr unsigned SEC_PER_HOUR = 3600;
constexpr unsigned SEC_PER_MIN = 60;


using TimePoint = struct TimePoint {
    TimePoint(unsigned hour, unsigned min, unsigned sec, bool isArr)
    : secCntFromMidnight(sec + min * SEC_PER_MIN + hour * SEC_PER_HOUR), isArrival(isArr)
    {}

    unsigned secCntFromMidnight;
    bool isArrival;
};


bool
compTimes(const TimePoint& tp1, const TimePoint& tp2)
{
    return (tp1.secCntFromMidnight < tp2.secCntFromMidnight) ||
    (tp1.secCntFromMidnight == tp2.secCntFromMidnight &&
     tp1.isArrival > tp2.isArrival);
}


unsigned
calcMaxNumOfPeople(vector<TimePoint>& times)
{
    std::sort(times.begin(), times.end(), compTimes);

    unsigned maxNumOfPeople = 0;
    unsigned curMaxNumOfPeople = 0;

    for (const auto& tp : times) {
        curMaxNumOfPeople += (tp.isArrival ? 1 : -1);

        if (curMaxNumOfPeople > maxNumOfPeople) {
            maxNumOfPeople = curMaxNumOfPeople;
        }
    }

    return maxNumOfPeople;
}


int
main()
{
    unsigned N;
    unsigned hour, min, sec;

    scanf("%u", &N);
    vector<TimePoint> times;
    for (unsigned i = 0; i < N; ++i) {
        scanf("%u:%u:%u", &hour, &min, &sec);
        times.push_back({hour, min, sec, true});

        scanf("%u:%u:%u", &hour, &min, &sec);
        times.push_back({hour, min, sec, false});
    }

    unsigned maxNumOfPeople = calcMaxNumOfPeople(times);

    printf("%u\n", maxNumOfPeople);

    return 0;
}
