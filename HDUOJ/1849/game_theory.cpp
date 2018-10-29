#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int chessNum;
    while (cin >> chessNum)
    {
        if (chessNum == 0)
            break;

        int ans = 0;
        while (chessNum--)
        {
            int cntPos;
            cin >> cntPos;
            ans ^= cntPos;
        }

        if (ans == 0)
        {
            cout << "Grass Win!" << endl;
        }
        else
        {
            cout << "Rabbit Win!" << endl;
        }
    }
    return 0;
}
