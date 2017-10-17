#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

bool cmp(string a, string b)
{
    bool aIsPositive = true, bIsPositive = true;
    int aStartPt = 0, bStartPt = 0, aEndPt = a.length() - 1, bEndPt = b.length() - 1;

    if (a[0] == '+' || a[0] == '-')
    {
        aStartPt = 1;
        if (a[0] == '-')
            aIsPositive = false;
    }
    if (b[0] == '+' || b[0] == '-')
    {
        bStartPt = 1;
        if (b[0] == '-')
            bIsPositive = false;
    }

    bool aIsZero = true, bIsZero = true;
    int aDotLoc = -1, bDotLoc = -1;

    for (int i = aStartPt; i <= aEndPt; i++)
    {
        if (a[i] == '0')
        {
            if (aDotLoc == -1 && aIsZero)
            {
                aStartPt++;
            }
        }
        else if (a[i] == '.')
        {
            aDotLoc = i;
            break;
        }
        else
        {
            aIsZero = false;
        }
    }
    for (int i = bStartPt; i <= bEndPt; i++)
    {
        if (b[i] == '0')
        {
            if (bDotLoc == -1 && bIsZero)
            {
                bStartPt++;
            }
        }
        else if (b[i] == '.')
        {
            bDotLoc = i;
            break;
        }
        else
        {
            bIsZero = false;
        }
    }

    if (aIsZero && bIsZero)
    {
        return true;
    }
    else if (aIsPositive != bIsPositive)
    {
        return false;
    }

    if (aDotLoc != -1)
    {
        for (int i = aEndPt; i > aDotLoc; i--)
        {
            if (a[i] == '0')
            {
                aEndPt--;
            }
            else
                break;
        }
        aEndPt--;
    }
    if (bDotLoc != -1)
    {
        for (int i = bEndPt; i > bDotLoc; i--)
        {
            if (b[i] == '0')
            {
                bEndPt--;
            }
            else
                break;
        }
        bEndPt--;
    }

    if (aEndPt - aStartPt != bEndPt - bStartPt)
    {
        return false;
    }

    for (int i = aStartPt, j = bStartPt; i <= aEndPt && j <= bEndPt; i++, j++)
    {
        if (a[i] != b[j])
        {
            return false;
        }
    }

    return true;

}

int main()
{
    ios::sync_with_stdio(false);
    string a, b;
    while (cin >> a >> b)
    {
        if (cmp(a, b))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}
