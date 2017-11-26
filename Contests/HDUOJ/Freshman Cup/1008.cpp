#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <climits>
#include <iomanip>
#define SIZE 1024
using namespace std;

long long int typeCount[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int digitNum;
    while (cin >> digitNum)
    {
        memset(typeCount, 0, sizeof(typeCount));
        for (int i = 0; i < digitNum; i++)
        {
            int type = 0;
            string num;
            cin >> num;
            for (int j = 0; j < num.length(); j++)
            {
                type |= 1 << ((num[j] - '0'));
                // Break if all digits have occurred.
                if (type == SIZE - 1)
                    break;
            }
            typeCount[type]++;
        }

        long long int ans = 0;

        // Groups of different types.
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = i + 1; j < SIZE; j++)
            {
                // If these types contain same numbers.
                if (i & j)
                {
                    ans += typeCount[i] * typeCount[j];
                }

            }
        }

        // Groups of the same type.
        for (int i = 0; i < SIZE; i++)
        {
            // ans += typeCount[i] * typeCount[i - 1] / 2;
            if (typeCount[i] & 1)
            {
                ans += ((typeCount[i] - 1) >> 1) * typeCount[i];
            }
            else
            {
                ans += (typeCount[i] >> 1) * (typeCount[i] - 1);
            }
        }

        cout << ans << endl;
    }
    return 0;
}

