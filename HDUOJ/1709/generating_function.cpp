#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 101
#define C_SIZE 10001
using namespace std;

long long int c1[C_SIZE], c2[C_SIZE];
int weight[SIZE];
int ans[SIZE * SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int weightNum;
    while (cin >> weightNum)
    {
        int weightSum = 0;
        for (int i = 0; i < weightNum; i++)
        {
            cin >> weight[i];
            weightSum += weight[i];
        }

        memset(c1, 0, sizeof(c1));
        c1[0] = 1;
        for (int i = 0; i < weightNum; i++)
        {
            memset(c2, 0, sizeof(c2));
            for (int j = 0; j <= 1; j++)
            {
                for (int k = 0; j * weight[i] + k <= weightSum; k++)
                {
                    c2[j * weight[i] + k] += c1[k];
                    c2[abs(j * weight[i] - k)] += c1[k];
                }
            }
            memcpy(c1, c2, sizeof(c2));
        }

        int num = 0, ansPt = 0;
        for (int i = 0; i <= weightSum; i++)
        {
            if (c1[i] == 0)
            {
                num++;
                ans[ansPt++] = i;
            }
        }
        cout << num << endl;
        for (int i = 0; i < ansPt; i++)
        {
            cout << ans[i];
            if (i < ansPt - 1)
                cout << " ";
            else
                cout << endl;
        }
    }
    return 0;
}
