#include <iostream>
#include <cstdio>
using namespace std;

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

int main()
{
    ios::sync_with_stdio(false);
    int year, month, day, sum;

    while (scanf("%d/%d/%d",&year, &month, &day) != EOF)
    {
        bool isLeap = isLeapYear(year);
        sum = 0;

        for (int i = 1; i < month; i++)
        {
            sum += getMonthDays(i, isLeap);
        }

        sum += day;

        cout << sum << endl;
    }
    return 0;
}
