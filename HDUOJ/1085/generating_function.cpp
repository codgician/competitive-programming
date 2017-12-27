#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 8001
using namespace std;

long long int c1[SIZE], c2[SIZE];
int num[3], money[3] = {1, 2, 5};

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> num[0] >> num[1] >> num[2])
    {
        if (num[0] == 0 && num[1] == 0 && num[2] == 0)
            break;

        memset(c1, 0, sizeof(c1));
        c1[0] = 1;

        for (int i = 0; i < 3; i++)
        {
            memset(c2, 0, sizeof(c2));
            for (int j = 0; j <= num[i]; j++)
            {
                for (int k = 0; k < SIZE && j * money[i] + k < SIZE; k++)
                {
                    c2[j * money[i] + k] += c1[k];
                }
            }
            memcpy(c1, c2 ,sizeof(c2));
        }

        int pt = 0;
        while (c1[pt] > 0 && pt < SIZE)
        {
            pt++;
        }
        cout << pt << endl;
    }
    return 0;
}
