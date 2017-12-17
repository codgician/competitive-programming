#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 24
using namespace std;

int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int num;
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        cin >> arr[i];
    }
    bool ans = false;

    // For every start point
    for (int i = 0; i < 12; i++)
    {
        // Note there should not be two consecutive leap years!
        bool isPrevYearLeap = false;
        bool isNextYear = false;
        bool isValid = true;
        for (int j = 0; j < num; j++)
        {
            int cnt = i + j;
            if (cnt >= SIZE)
                break;
            if (cnt >= 12)
            {
                isNextYear = true;
                cnt -= 12;
            }

            if (!isNextYear && arr[j] == 29)
                isPrevYearLeap = true;

            if (arr[j] != month[cnt])
            {
                if (cnt == 1 && arr[j] == 29 && (!isNextYear || (isNextYear && !isPrevYearLeap)))
                {
                    continue;
                }
                isValid = false;
                break;
            }
        }

        if (isValid)
        {
            ans = true;
            break;
        }
    }

    if (ans)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    return 0;
}
