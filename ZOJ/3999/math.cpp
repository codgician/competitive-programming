#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <set>
#include <vector>
#include <queue>
#define EQU_SIZE 10
#define NUMERATOR 0
#define DENOMINATOR 1
using namespace std;

long long int equ[2][EQU_SIZE];

long long int getGcd(long long int a, long long int b)
{
    if (b == 0)
        return a;
    else
        return getGcd(b, a % b);
}

long long int getAbs(long long int a)
{
    if (a < 0)
        a = -a;
    return a;
}

bool isDigit(char ch)
{
    return ch >= '0' && ch <= '9';
}

long long int getValue(bool which, long long int x)
{
    long long int ans = 0, cnt = 1;
    for (int i = 0; i < EQU_SIZE; i++)
    {
        ans += equ[which][i] * cnt;
        cnt *= x;
    }
    return ans;
}

void getDx(bool which)
{
    for (int i = 1; i < EQU_SIZE; i++)
    {
        equ[which][i - 1] = equ[which][i] * i;
    }
    equ[which][EQU_SIZE - 1] = 0;
}

void readPoly(bool which)
{
    for (int i = 0; i < EQU_SIZE; i++)
        equ[which][i] = 0;

    string s;
    cin >> s;
    int cntNum = 0, tmp = 1;
    int cntStage = 0;
    for (int i = s.length(); i >= 0; i--)
    {
        if (isDigit(s[i]))
        {
            cntNum += tmp * (s[i] - '0');
            tmp *= 10;
        }
        else if (s[i] == '^')
        {
            cntStage = cntNum;
            cntNum = 0, tmp = 1;
        }
        else if (s[i] == 'x')
        {
            if (i == s.length() - 1 || s[i + 1] != '^')
            {
                cntStage = 1;
                cntNum = 0, tmp = 1;
            }
        }
        else if (s[i] == '+')
        {
            if (s[i + 1] == 'x')
            {
                cntNum = 1;
            }
            equ[which][cntStage] += cntNum;
            cntNum = 0, tmp = 1, cntStage = 0;
        }
        else if (s[i] == '-')
        {
            if (s[i + 1] == 'x')
            {
                cntNum = 1;
            }
            equ[which][cntStage] -= cntNum;
            cntNum = 0, tmp = 1, cntStage = 0;
        }
    }

    if (s[0] != '-' && s[0] != '+')
    {
        if (s[0] == 'x')
        {
            cntNum = 1;
        }
        equ[which][cntStage] += cntNum;
        cntNum = 0, tmp = 1, cntStage = 0;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        readPoly(NUMERATOR);
        readPoly(DENOMINATOR);
        int n;
        cin >> n;
        long long int numeratorVal = getValue(NUMERATOR, n);
        long long int denominatorVal = getValue(DENOMINATOR, n);

        if (denominatorVal != 0)
        {
            if ((numeratorVal < 0 && denominatorVal > 0) || (numeratorVal > 0 && denominatorVal < 0))
            {
                cout << "-";
            }
            numeratorVal = getAbs(numeratorVal);
            denominatorVal = getAbs(denominatorVal);
            if (numeratorVal % denominatorVal == 0)
            {
                cout << numeratorVal / denominatorVal << endl;
            }
            else
            {
                long long int gcd = getGcd(numeratorVal, denominatorVal);
                cout << numeratorVal / gcd << "/" << denominatorVal / gcd << endl;
            }
        }
        else
        {
            if (numeratorVal != 0)
            {
                cout << "INF" << endl;
            }
            else
            {
                while (numeratorVal == 0 && denominatorVal == 0)
                {
                    getDx(NUMERATOR);
                    getDx(DENOMINATOR);
                    numeratorVal = getValue(NUMERATOR, n);
                    denominatorVal = getValue(DENOMINATOR, n);
                }

                if (denominatorVal == 0)
                {
                    cout << "INF" << endl;
                }
                else
                {
                    if ((numeratorVal < 0 && denominatorVal > 0) || (numeratorVal > 0 && denominatorVal < 0))
                    {
                        cout << "-";
                    }
                    numeratorVal = getAbs(numeratorVal);
                    denominatorVal = getAbs(denominatorVal);
                    if (numeratorVal % denominatorVal == 0)
                    {
                        cout << numeratorVal / denominatorVal << endl;
                    }
                    else
                    {
                        long long int gcd = getGcd(numeratorVal, denominatorVal);
                        cout << numeratorVal / gcd << "/" << denominatorVal / gcd << endl;
                    }
                }
            }
        }
    }
    return 0;
}
