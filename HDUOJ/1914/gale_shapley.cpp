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
#define SIZE 99
using namespace std;

int boyPrefOrder[SIZE][SIZE], girlPrefScore[SIZE][SIZE];
int girlMatch[SIZE], boyMatch[SIZE];
bool hasProposed[SIZE][SIZE];

char boyName[SIZE], girlName[SIZE];
map<char, int> boyId, girlId;

queue<int> q;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        boyId.clear();
        girlId.clear();
        memset(hasProposed, false, sizeof(hasProposed));
        memset(girlMatch, -1, sizeof(boyMatch));
        memset(boyMatch, -1, sizeof(boyMatch));

        int matchNum;
        cin >> matchNum;
        for (int i = 0; i < matchNum; i++)
        {
            char boyCh;
            cin >> boyCh;
            boyId[boyCh] = i;
            boyName[i] = boyCh;
            q.push(i);
        }
        for (int i = 0; i < matchNum; i++)
        {
            char girlCh;
            cin >> girlCh;
            girlId[girlCh] = i;
            girlName[i] = girlCh;
        }
        for (int i = 0; i < matchNum; i++)
        {
            char boyCh, tmp;
            cin >> boyCh >> tmp;
            for (int j = 0; j < matchNum; j++)
            {
                char girlCh;
                cin >> girlCh;
                boyPrefOrder[boyId[boyCh]][j] = girlId[girlCh];
            }
        }
        for (int i = 0; i < matchNum; i++)
        {
            char girlCh, tmp;
            cin >> girlCh >> tmp;
            for (int j = 0; j < matchNum; j++)
            {
                char boyCh;
                cin >> boyCh;
                girlPrefScore[girlId[girlCh]][boyId[boyCh]] = matchNum - j;
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
                    boyMatch[cntBoyId] = cntGirlId;
                    break;
                }
                else if (girlPrefScore[cntGirlId][cntBoyId] > girlPrefScore[cntGirlId][girlMatch[cntGirlId]])
                {
                    q.push(girlMatch[cntGirlId]);
                    girlMatch[cntGirlId] = cntBoyId;
                    boyMatch[cntBoyId] = cntGirlId;
                    break;
                }
            }
        }

        for (int i = 0; i < 26; i++)
        {
            char cntCh = 'a' + i;
            if (boyId.count(cntCh))
                cout << cntCh << " " << girlName[boyMatch[boyId[cntCh]]] << endl;
        }
        if (t < caseNum - 1)
            cout << endl;

    }
    return 0;
}
