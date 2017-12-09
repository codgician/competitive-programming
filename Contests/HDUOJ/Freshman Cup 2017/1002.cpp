#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

char id[19];
int year, month, day;
int para[17] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
int ans[11] = {1,0,10,9,8,7,6,5,4,3,2};

bool isValid()
{
    // First check birthday.
    int cntYear = (id[6] - '0') * 1000 + (id[7] - '0') * 100 + (id[8] - '0') * 10 + (id[9] - '0');
    int cntMonth = (id[10] - '0') * 10 + (id[11] - '0');
    int cntDay = (id[12] - '0') * 10 + (id[13] - '0');

    if (year - cntYear < 18)
    {
        return false;
    }
    else if (year - cntYear == 18)
    {
        if (month < cntMonth)
            return false;
        else if (month == cntMonth)
        {
            if (day < cntDay)
                return false;
        }
    }

    // Next check validation code.
    int tot = 0;
    for (int i = 0; i < 17; i++)
    {
        if (id[i] - '0' < 0 || id[i] - '0' > 9)
            return false;
        tot += (((para[i] * (id[i] - '0'))) % 11);
    }

    if (id[17] != 'X' && (id[17] - '0' < 0 || id[17] - '0' > 9))
        return false;

    tot = tot % 11;

    int v = id[17] - '0';

    if (id[17] == 'X')
        v = 10;

    return ans[tot] == v;

}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    while (scanf("%d", &caseNum) != EOF)
    {
        scanf("%d-%d-%d", &year, &month, &day);
        for (int t = 0; t < caseNum; t++)
        {
            scanf("%s", id);
            if (isValid())
            {
                printf("Accepted\n");
            }
            else
            {
                printf("Sorry\n");
            }
        }
    }
    return 0;
}
