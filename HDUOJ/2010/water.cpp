#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

bool isNarcissistic(int x)
{
    int a = x / 100;
    int b = (x / 10) % 10;
    int c = x % 10;

    return a * a * a + b * b * b + c * c * c == x;
}

int main()
{
    ios::sync_with_stdio(false);
    int startPt, endPt;
    while (cin >> startPt >> endPt)
    {
        bool exist = false;
        for (int i = startPt; i <= endPt; i++)
        {
            if (isNarcissistic(i))
            {
                if (!exist)
                {
                    cout << i;
                    exist = true;
                } else {
                    cout << " " << i;
                }
            }
        }
        if (!exist)
            cout << "no";
        cout << endl;
    }
    return 0;
}
