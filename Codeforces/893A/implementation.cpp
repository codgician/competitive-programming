#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
using namespace std;

bool isInGame[3];

int main()
{
    ios::sync_with_stdio(false);
    int roundNum;
    cin >> roundNum;
    memset(isInGame, true ,sizeof(isInGame));
    isInGame[2] = false;
    bool flag = false;
    for (int i = 0; i < roundNum; i++)
    {
        int cntWinner;
        cin >> cntWinner;
        if (!isInGame[cntWinner - 1])
        {
            flag = true;
            break;
        }
        for (int i = 0; i < 3; i++)
        {
            if (i != cntWinner - 1)
            {
                isInGame[i] = !isInGame[i];
            }
        }
    }
    if (flag)
        cout << "NO" << endl;
    else
        cout << "YES" << endl;
    return 0;
}
