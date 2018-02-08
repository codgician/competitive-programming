#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <map>
#define SIZE 501
using namespace std;

queue<int> q;
map<string, int> boyId, girlId;
string boyName[SIZE], girlName[SIZE];

int boyPrefOrder[SIZE][SIZE], girlPrefScore[SIZE][SIZE];
int girlMatch[SIZE];
bool hasProposed[SIZE][SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int matchNum;
    while (cin >> matchNum)
    {
        boyId.clear();
        girlId.clear();
        memset(hasProposed, false, sizeof(hasProposed));
        memset(girlMatch, -1, sizeof(girlMatch));

        for (int i = 0; i < matchNum; i++)
        {
            string boyStr;
            cin >> boyStr;
            boyName[i] = boyStr;
            boyId[boyStr] = i;
            for (int j = 0; j < matchNum; j++)
            {
                string girlStr;
                cin >> girlStr;
                if (i == 0)
                {
                    girlName[j] = girlStr;
                    girlId[girlStr] = j;
                }
                boyPrefOrder[i][j] = girlId[girlStr];
            }
            q.push(i);
        }
        for (int i = 0; i < matchNum; i++)
        {
            string girlStr;
            cin >> girlStr;
            for (int j = 0; j < matchNum; j++)
            {

                string boyStr;
                cin >> boyStr;
                girlPrefScore[girlId[girlStr]][boyId[boyStr]] = matchNum - j;
            }
        }

        while (!q.empty())
        {
            int cntBoyId = q.front();
            q.pop();

            for (int i = 0; i < matchNum; i++)
            {
                int cntGirlId = boyPrefOrder[cntBoyId][i];
                if (hasProposed[cntBoyId][cntGirlId])
                    continue;

                hasProposed[cntBoyId][cntGirlId] = true;

                if (girlMatch[cntGirlId] == -1)
                {
                    girlMatch[cntGirlId] = cntBoyId;
                    break;
                }
                else if (girlPrefScore[cntGirlId][cntBoyId] > girlPrefScore[cntGirlId][girlMatch[cntGirlId]])
                {
                    q.push(girlMatch[cntGirlId]);
                    girlMatch[cntGirlId] = cntBoyId;
                    break;
                }
            }
        }

        for (int i = 0; i < matchNum; i++)
        {
            cout << boyName[girlMatch[i]] << " " << girlName[i] << endl;
        }
        cout << endl;
    }
    return 0;
}
