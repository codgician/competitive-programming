#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <iterator>
#define SIZE 100010
#define BIT_NUM 320
using namespace std;

int primeArr[SIZE], factorArr[SIZE], primePt;

int arr[SIZE];
int smallPrimeArr[BIT_NUM][SIZE];

vector<int> bigPrimeArr[SIZE];

int len;

inline void initPrime()
{
    memset(factorArr, 0, sizeof(factorArr));
    primePt = 0;
    for (int i = 2; i < SIZE; i++)
    {
        if (factorArr[i] == 0)
        {
            factorArr[i] = i;
            primeArr[primePt++] = i;
        }

        for (int j = 0; j < primePt; j++)
        {
            if (primeArr[j] > factorArr[i] || primeArr[j] > (SIZE - 1) / i)
                break;
            factorArr[i * primeArr[j]] = primeArr[j];
        }
    }
}

int main()
{
    initPrime();
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        memset(smallPrimeArr, 0, sizeof(smallPrimeArr));
        for (int i = 0; i < primePt; i++)
        {
            bigPrimeArr[primeArr[i]].clear();
        }

        int qNum;
        scanf("%d%d", &len, &qNum);
        for (int i = 1; i <= len; i++)
        {
            scanf("%d", arr + i);
        }

        for (int i = 1; i <= len; i++)
        {
            for (int j = 0; j < primePt && primeArr[j] <= arr[i] && primeArr[j] <= BIT_NUM; j++)
            {
                if (arr[i] % primeArr[j] == 0)
                {
                    int cntNum = 0;
                    while (arr[i] % primeArr[j] == 0)
                    {
                        cntNum++;
                        arr[i] /= primeArr[j];
                    }
                    smallPrimeArr[j][i] = cntNum;
                }
            }

            if (arr[i] > BIT_NUM)
            {
                bigPrimeArr[arr[i]].push_back(i);
            }
        }

        for (int j = 0; j < primePt && primeArr[j] <= BIT_NUM; j++)
        {
            for (int i = 2; i <= len; i++)
            {
                smallPrimeArr[j][i] += smallPrimeArr[j][i - 1];
            }
        }

        while (qNum--)
        {
            int leftPt, rightPt, cnt;
            scanf("%d%d%d", &leftPt, &rightPt, &cnt);

            bool ans = true;
            for (int i = 0; i < primePt && primeArr[i] <= cnt && primeArr[i] <= BIT_NUM; i++)
            {
                if (cnt % primeArr[i] == 0)
                {
                    int cntNum = 0;
                    while (cnt % primeArr[i] == 0)
                    {
                        cntNum++;
                        cnt /= primeArr[i];
                    }

                    int actualNum = smallPrimeArr[i][rightPt] - smallPrimeArr[i][leftPt - 1];
                    if (actualNum < cntNum)
                    {
                        ans = false;
                        break;
                    }
                }
            }

            if (ans && cnt > BIT_NUM)
            {
                int lowerBound = lower_bound(bigPrimeArr[cnt].begin(), bigPrimeArr[cnt].end(), leftPt) - bigPrimeArr[cnt].begin();
                int upperBound = upper_bound(bigPrimeArr[cnt].begin(), bigPrimeArr[cnt].end(), rightPt) - bigPrimeArr[cnt].begin();
                if (lowerBound == upperBound)
                    ans = false;
            }
            
            if (ans)
                printf("Yes\n");
            else
                printf("No\n");
        }
    }
    return 0;
}