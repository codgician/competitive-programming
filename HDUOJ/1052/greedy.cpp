#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdio>
#include <algorithm>
#define SIZE 1001
using namespace std;

int king[SIZE], tianji[SIZE];

bool cmpRule(int a, int b)
{
    return a > b;
}

int main()
{
    ios::sync_with_stdio(false);
    int horseNum;
    while (cin >> horseNum)
    {
        if (horseNum == 0)
            break;
        for (int i = 0; i < horseNum; i++)
            cin >> tianji[i];
        for (int i = 0; i < horseNum; i++)
            cin >> king[i];

        sort(king, king + horseNum, cmpRule);
        sort(tianji, tianji + horseNum, cmpRule);

        int money = 0;
        int tianjiHeadPt = 0, tianjiTailPt = horseNum - 1;
        int kingHeadPt = 0, kingTailPt = horseNum - 1;
        while (tianjiHeadPt <= tianjiTailPt)
        {
            // If Tianji's fastest horse is even faster than the King,
            // just grab the money!
            if (tianji[tianjiHeadPt] > king[kingHeadPt])
            {
                money += 200;
                tianjiHeadPt++;
                kingHeadPt++;
            }
            // If not, let the slowest horse lose with dignity.
            else if (tianji[tianjiHeadPt] < king[kingHeadPt])
            {
                if (tianji[tianjiTailPt] != king[kingHeadPt])
                    money -= 200;
                tianjiTailPt--;
                kingHeadPt++;
            }
            // If two horses have the same speed
            // leave them temporarily
            // and let the slowest horses compete.
            else
            {
                // If Tianji's slowest horse is faster than King's slowest.
                // grab the money directly.
                if (tianji[tianjiTailPt] > king[kingTailPt])
                {
                    money += 200;
                    tianjiTailPt--;
                    kingTailPt--;
                }
                // If not, let the Tianji's slowest lose to King's fastest with dignity.
                else
                {
                    if (tianji[tianjiTailPt] != king[kingHeadPt])
                        money -= 200;
                    tianjiTailPt--;
                    kingHeadPt++;
                }
            }
        }
        cout << money << endl;
    }
    return 0;
}
