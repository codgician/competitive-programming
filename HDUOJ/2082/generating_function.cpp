#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 26
#define C_SIZE 51
using namespace std;

int num[SIZE], value[SIZE];
long long int c1[C_SIZE], c2[C_SIZE];

int main()
{
    ios::sync_with_stdio(false);
    for (int i = 0; i < 26; i++)
    {
        value[i] = i + 1;
    }
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        for (int i = 0; i < 26; i++)
        {
            cin >> num[i];
        }
        memset(c1, 0, sizeof(c1));
        c1[0] = 1;

        for (int i = 0; i < 26; i++)
        {
            memset(c2, 0, sizeof(c2));
            for (int j = 0; j <= num[i]; j++)
            {
                for (int k = 0; j * value[i] + k <= 50; k++)
                {
                    c2[j * value[i] + k] += c1[k];
                }
            }
            memcpy(c1, c2, sizeof(c2));
        }

        long long int ans = 0;
        for (int i = 1; i <= 50; i++)
        {
            ans += c1[i];
        }
        cout << ans << endl;
    }
    return 0;
}
