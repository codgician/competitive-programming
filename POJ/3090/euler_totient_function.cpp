#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <cfloat>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
using namespace std;

#define SIZE 40010

int factorArr[SIZE], primeArr[SIZE], phi[SIZE];
int phiPrefixSum[SIZE];
int primePt;

void initPhi()
{
    phi[1] = 1;
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
            phi[i * primeArr[j]] = phi[i] * (primeArr[j] - (factorArr[i] != primeArr[j]));
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    initPhi();
    phiPrefixSum[1] = 0;
    for (int i = 2; i < SIZE; i++)
    {
        phiPrefixSum[i] = phiPrefixSum[i - 1] + phi[i];
    }

    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        int len;
        cin >> len;
        int ans = (phiPrefixSum[len] << 1) + 3;
        cout << t << " " << len << " " << ans << endl;
    }
    return 0;
}