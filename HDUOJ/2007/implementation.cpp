// Keep in mind that pow() works with double.
// Never force conversion between double and int!!!

#include <iostream>
#include <cstdio>
using namespace std;

int getSquare(int x)
{
    return x * x;
}

int getCubic(int x)
{
    return x * x * x;
}

bool isOdd(int x)
{
    return x % 2 == 1 ? true : false;
}

int main()
{
    ios::sync_with_stdio(false);
    int startPt, endPt;
    while (cin >> startPt >> endPt)
    {
        int oddAns = 0, evenAns = 0;
        if (startPt > endPt)
            swap(startPt, endPt);
        for (int i = startPt; i <= endPt; i++)
        {
            if (isOdd(i))
                oddAns += getCubic(i);
            else
                evenAns += getSquare(i);
        }
        cout << evenAns << " " << oddAns << endl;
    }
    return 0;
}
