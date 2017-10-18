#include <iostream>
#include <cmath>
#include <algorithm>
#include <cmath>
#define SIZE 101
using namespace std;

int chn[SIZE], jap[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int memberNum;
    while (cin >> memberNum)
    {
        if (memberNum == 0)
            break;
        for (int i = 0; i < memberNum; i++)
        {
            cin >> chn[i];
        }
        for (int i = 0; i < memberNum; i++)
        {
            cin >> jap[i];
        }

        sort(chn, chn + memberNum);
        sort(jap, jap + memberNum);

        int chnScore = 0, japScore = 0;
        for (int i = 0; i < memberNum; i++)
        {
            if (chn[i] > jap[i])
                chnScore += 2;
            else if (chn[i] == jap[i])
            {
                chnScore++;
                japScore++;
            }
            else
                japScore += 2;
        }
        cout << chnScore << " vs " << japScore << endl;
    }
    return 0;
}
