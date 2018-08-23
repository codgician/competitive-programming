#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
using namespace std;

#define SIZE 20000010

int factorArr[SIZE], primeArr[SIZE >> 1], phi[SIZE];
long long int ans[SIZE];
int primePt;

void initEuler()
{
    memset(factorArr, 0, sizeof(factorArr));
    primePt = 0;
    for (int i = 2; i < SIZE; i++)
    {
        if (factorArr[i] == 0)
        {
            factorArr[i] = i;
            primeArr[primePt++] = i;
            phi[i] = i - 1;
        }

        for (int j = 0; j < primePt; j++)
        {
            if (primeArr[j] > factorArr[i] || primeArr[j] > (SIZE - 1) / i)
                break;
            factorArr[i * primeArr[j]] = primeArr[j];
            phi[i * primeArr[j]] = phi[i] * (i % primeArr[j] == 0 ? primeArr[j] : primeArr[j] - 1);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    initEuler();
    ans[0] = 0;
    ans[1] = 0;
    for (int i = 2; i <= 20000000; i++)
    {
        ans[i] = ans[i - 1] + ((phi[i]) >> (i & 1));
    }

    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int lim;
        cin >> lim;
        cout << ans[lim] << endl;
    }
    return 0;
}