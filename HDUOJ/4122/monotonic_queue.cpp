// HDUOJ - 4122 & POJ - 4002
// Maintain a monotonic queue.

#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#define LEFT true
#define RIGHT false
using namespace std;

struct Node {
    int num;
    long long int t;
} order[3050];

int q[100010], cost[100010]; // q: Stores the time to make mooncakes.
int head = 0, tail = 0;
long long int ans = 0;
int n, m, t ,s;

int getMonth(string month)
{
    if (month == "Jan")
        return 1;
    else if (month == "Feb")
        return 2;
    else if (month == "Mar")
        return 3;
    else if (month == "Apr")
        return 4;
    else if (month == "May")
        return 5;
    else if (month == "Jun")
        return 6;
    else if (month == "Jul")
        return 7;
    else if (month == "Aug")
        return 8;
    else if (month == "Sep")
        return 9;
    else if (month == "Oct")
        return 10;
    else if (month == "Nov")
        return 11;
    else if (month == "Dec")
        return 12;
}

int getMonthDays(int month, bool isLeapYear)
{
    switch (month)
    {
        case 1:
            return 31;
        case 2:
            return isLeapYear ? 29 : 28;
        case 3:
            return 31;
        case 4:
            return 30;
        case 5:
            return 31;
        case 6:
            return 30;
        case 7:
            return 31;
        case 8:
            return 31;
        case 9:
            return 30;
        case 10:
            return 31;
        case 11:
            return 30;
        case 12:
            return 31;
    }
}

bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

long long int getTime(int year, int month, int day, int hour)
{
    long long int d = 0;
    bool isLeap = isLeapYear(year);

    // Previous years.
    for (int i = 2000; i < year; i++)
    {
        if (isLeapYear(i))
        {
            d += 366;
        }
        else
        {
            d += 365;
        }
    }

    // Current year.
    for (int i = 1; i < month; i++)
    {
        d += getMonthDays(i, isLeap);
    }

    d += day - 1;

    return d * 24 + hour;

}

void pop(bool loc)
{
    if (loc == LEFT)
    {
        head++;
    }
    else if (loc == RIGHT)
    {
        tail--;
    }
}

void push(int time)
{
    // Compare: make before and store & make now.
    while (head < tail && cost[q[tail - 1]] + (time - q[tail - 1]) * s >= cost[time])
    {
        pop(RIGHT);
    }

    q[tail] = time;
    tail++;
	
    // Pop head if it expires.
    while (head < tail && time - q[head] > t)
		pop(LEFT);

    return;
}

int main()
{
    ios::sync_with_stdio(false);

    while (true)
    {
        // Don't forget to initialize!
        ans = 0;
        head = 0;
        tail = 0;

        cin >> n >> m;
        if (n == 0 && m == 0)
        {
            break;
        }

        for (int i = 0; i < n; i++)
        {
            string month;
            int year, day, hour;
            cin >> month >> day >> year >> hour >> order[i].num;
            order[i].t = getTime(year, getMonth(month), day, hour);
        }

        cin >> t >> s;
        for (int i = 0; i < m; i++)
        {
            cin >> cost[i];
        }

        int k = 0;

        // For every single hour.
        for (int i = 0; i < m ; i++)
        {
            push(i);

            // Note that there might be multiple orders at the same time!
            // Therefore, use while instead of if.
            while (i == order[k].t)
            {
                // Head is always the minimum.
                ans += order[k].num * (cost[q[head]] + s * (i - q[head]));

                k++;
            }
        }

        cout << ans << endl;
    }
    return 0;
}
