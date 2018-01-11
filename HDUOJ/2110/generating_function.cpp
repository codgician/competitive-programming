#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#define SIZE 10001
using namespace std;

typedef struct _Prop
{
    int value;
    int num;
} prop;

prop arr[SIZE];
int c1[SIZE], c2[SIZE];

const int mod = 10000;

int main()
{
    ios::sync_with_stdio(false);
    int propNum;
    while (cin >> propNum)
    {
        if (propNum == 0)
            break;
        int valueSum = 0;
        for (int i = 0; i < propNum; i++)
        {
            cin >> arr[i].value >> arr[i].num;
            valueSum += arr[i].value * arr[i].num;
        }

        if (valueSum % 3 > 0)
        {
            cout << "sorry" << endl;
        }
        else
        {
            int target = valueSum / 3;

            memset(c1, 0, sizeof(c1));
            c1[0] = 1;
            for (int i = 0; i < propNum; i++)
            {
                memset(c2, 0, sizeof(c2));
                for (int j = 0; j <= arr[i].num && j * arr[i].value <= target; j++)
                {
                    for (int k = 0; k + j * arr[i].value <= target; k++)
                    {
                        c2[k + j * arr[i].value] += c1[k];
                        c2[k + j * arr[i].value] %= mod;
                    }
                }
                memcpy(c1, c2, sizeof(c2));
            }

            if (c1[target] > 0)
            {
                cout << c1[target] % mod << endl;
            }
            else
            {
                cout << "sorry" << endl;
            }
        }
    }
    return 0;
}
