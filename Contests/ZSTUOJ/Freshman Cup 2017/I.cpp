#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 122
using namespace std;

char str[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int k;
    while (cin >> str >> k)
    {
        int strLength = strlen(str), pt = 0, exp = 0;
        bool isLessThanOne = false, stopCountingExp = false;

        // Remove zeros
        while (str[pt] == '0')
            pt++;

        // Integer part
        char intPart;
        if (str[pt] == '.')
        {
            isLessThanOne = true;
            pt++;
            while (str[pt] == '0')
            {
                pt++;
                exp++;
            }
            exp++;
            stopCountingExp = true;
            intPart = str[pt];
        }
        else
        {
            intPart = str[pt];
        }
        cout << intPart;
        pt++;

        // Decimal part and exponent part
        if (k > 1)
            cout << '.';
        int endPt = pt + k - 2;
        while (pt <= endPt && pt <= strLength - 1)
        {
            if (str[pt] == '.')
            {
                stopCountingExp = true;
                endPt++;
            }
            else
            {
                cout << str[pt];
                if (!stopCountingExp)
                    exp++;
            }
            pt++;
        }
        // Print zeros if endPt is larger than length
        if (endPt > strLength - 1)
        {
            while (pt <= endPt)
            {
                cout << '0';
                pt++;
            }
        }
        // If haven't met decimal point, keep counting exponent
        else if (!stopCountingExp)
        {
            while (pt <= strLength - 1)
            {
                if (str[pt] == '.')
                    break;
                exp++;
                pt++;
            }
        }
        cout << 'e';
        if (isLessThanOne)
            cout << '-';
        cout << exp << endl;
    }
    return 0;
}
