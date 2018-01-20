#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#define SIZE 100064
using namespace std;

int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    unsigned long long int sum;
    int len;
    cin >> sum >> len;

    memset(arr, 0, sizeof(arr));
    int cnt = 0;
    int highestNonZeroPos = 0, lowestNonZeroPos = 100063;
    for (int i = 100063; i >= 100000; i--)
    {
        arr[i] = (sum >> (i - 100000) & 1);
        cnt += arr[i];
        if (arr[i])
        {
            highestNonZeroPos = max(highestNonZeroPos, i);
            lowestNonZeroPos = min(lowestNonZeroPos, i);
        }
    }

    if (cnt <= len)
    {
        cout << "Yes" << endl;
        int delta = len - cnt;

        while (arr[highestNonZeroPos] <= delta)
        {
            arr[highestNonZeroPos - 1] += (arr[highestNonZeroPos] << 1);
            delta -= arr[highestNonZeroPos];
            arr[highestNonZeroPos] = 0;
            if (lowestNonZeroPos == highestNonZeroPos)
                lowestNonZeroPos--;
            highestNonZeroPos--;
        }

        if (delta > 0)
        {
            for (int i = lowestNonZeroPos; i > 0 && delta > 0; i--)
            {
                if (arr[i] && delta > 0)
                {
                    arr[i]--;
                    arr[i - 1] += 2;
                    delta--;
                    lowestNonZeroPos--;
                }
            }
        }

        bool isFirst = true;
        for (int i = highestNonZeroPos; i >= lowestNonZeroPos; i--)
        {
            while (arr[i])
            {
                if (isFirst)
                {
                    cout << i - 100000;
                    isFirst = false;
                }
                else
                {
                    cout << " " << i - 100000;
                }
                arr[i]--;
            }
        }

    }
    else
    {
        cout << "No" << endl;
    }

    return 0;
}
