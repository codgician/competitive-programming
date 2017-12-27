#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define FAC_SIZE 55
#define C_SIZE 250001
using namespace std;

typedef struct _Fac {
    int value;
    int num;
} fac;

fac arr[FAC_SIZE];
unsigned long long int c1[C_SIZE], c2[C_SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int facType;
    while (cin >> facType)
    {
        if (facType < 1)
            break;

        int valueSum = 0;
        for (int i = 0; i < facType; i++)
        {
            cin >> arr[i].value >> arr[i].num;
            valueSum += arr[i].value * arr[i].num;
        }

        int target = valueSum / 2;

        memset(c1, 0, sizeof(c1));
        c1[0] = 1;
        for (int i = 0; i < facType; i++)
        {
            memset(c2, 0, sizeof(c2));
            for (int j = 0; j <= target; j++)
            {
                for (int k = 0; k <= arr[i].num * arr[i].value && j * arr[i].value + k <= target; k++)
                {
                    c2[j * arr[i].value + k] += c1[k];
                }
            }
            memcpy(c1, c2, sizeof(c2));
        }

        int ans = 0;
        for (int i = target; i >= 0; i--)
        {
            if (c1[i] > 0)
            {
                ans = i;
                break;
            }
        }
        cout << valueSum - ans << " " << ans << endl;
    }
    return 0;
}
