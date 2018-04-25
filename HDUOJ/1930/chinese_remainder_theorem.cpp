#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <climits>
#include <iomanip>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <functional>
#include <iterator>
#define ORIG_LEN 3
#define EQU_NUM 4
#define ANS_SIZE 210
using namespace std;

long long int mod[EQU_NUM], cst[EQU_NUM];
char ansArr[ANS_SIZE];
int equNum;

long long int extEuclid(long long int a, long long int b, long long int &x, long long int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }

    long long int gcd = extEuclid(b, a % b, x, y);
    long long int tmp = x;
    x = y;
    y = tmp - y * (a / b);

    return gcd;
}

long long int crt()
{
    long long int modProd = mod[0], prevAns = cst[0];

    for (int i = 1; i < equNum; i++)
    {
        long long int x, y;
        long long int a = modProd, b = mod[i], c = cst[i] - prevAns;
        long long int gcd = extEuclid(a, b, x, y);

        if (c % gcd != 0)
            return -1;

        long long int cntAns = c / gcd * x;
        if (cntAns < 0)
            cntAns = (mod[i] / gcd) - (-cntAns) % (mod[i] / gcd);
        else
            cntAns %= mod[i] / gcd;

        prevAns += modProd * cntAns;
        modProd = modProd / gcd * mod[i];
    }

    return prevAns % modProd;
}

int main()
{
    ios::sync_with_stdio(false);
    equNum = EQU_NUM;
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int groupNum;
        cin >> groupNum;

        for (int i = 0; i < EQU_NUM; i++)
        {
            cin >> mod[i];
        }

        for (int i = 0; i < groupNum; i++)
        {
            long long int encoded;
            cin >> encoded;

            for (int j = EQU_NUM - 1; j >= 0; j--)
            {
                cst[j] = encoded % 100;
                encoded /= 100;
            }

            long long int ans = crt();

            for (int j = ORIG_LEN - 1; j >= 0; j--)
            {
                int tmp = ans % 100;
                if (tmp == 27)
                {
                    ansArr[i * ORIG_LEN + j] = ' ';
                }
                else
                {
                    ansArr[i * ORIG_LEN + j] = 'A' + tmp - 1;
                }
                ans /= 100;
            }
        }

        int lastNotBlank = -1;
        for (int i = 0; i < ORIG_LEN * groupNum; i++)
        {
            if (ansArr[i] != ' ')
                lastNotBlank = i;
        }

        for (int i = 0; i <= lastNotBlank; i++)
        {
            cout << ansArr[i];
        }
        cout << endl;
    }
    return 0;
}