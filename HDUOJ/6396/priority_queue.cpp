#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
using namespace std;

#define MON_SIZE 100010
#define VAL_SIZE 5

priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq[VAL_SIZE];
int atkArr[VAL_SIZE];
int defArr[MON_SIZE][VAL_SIZE], expArr[MON_SIZE][VAL_SIZE];

// Fast read from wkc
#define SIZE 100
char S[SIZE], *SS = S, *ST = S, CH;
inline char getc()
{
    return SS == ST && (ST = (SS = S) + fread(S, 1, SIZE, stdin), SS == ST) ? 0 : *SS++;
}
template<class T>inline bool read(T &x)
{
    x = 0; int sgn = 1;
    while (CH = getc(), !isdigit(CH) && CH != '-')
        if (CH == 0)
            return 0;

    if (CH == '-')
        sgn = -1;
    else
        x = CH ^ 48;

    while (CH = getc(), isdigit(CH))
        x = (x << 3) + (x << 1) + (CH ^ 48);

    x *= sgn;
    return 1;
}

int main()
{
    int caseNum;
    read(caseNum);
    while (caseNum--)
    {
        int monsNum, valNum;
        read(monsNum);
        read(valNum);
        for (int i = 0; i < valNum; i++)
        {
            pq[i] = priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > >();
            read(atkArr[i]);
        }
        for (int i = 0; i < monsNum; i++)
        {
            for (int j = 0; j < valNum; j++)
            {
                read(defArr[i][j]);
            }
            pq[0].push(make_pair(defArr[i][0], i));
            for (int j = 0; j < valNum; j++)
            {
                read(expArr[i][j]);
            }
        }

        int ans = 0;
        while (true)
        {
            bool hasUpdated = false;
            for (int i = 0; i < valNum; i++)
            {
                while (!pq[i].empty() && pq[i].top().first <= atkArr[i])
                {
                    hasUpdated = true;
                    pair<int, int> cntTop = pq[i].top();
                    pq[i].pop();

                    if (i == valNum - 1)
                    {
                        ans++;
                        for (int j = 0; j < valNum; j++)
                        {
                            atkArr[j] += expArr[cntTop.second][j];
                        }
                    }
                    else
                    {
                        cntTop.first = defArr[cntTop.second][i + 1];
                        pq[i + 1].push(cntTop);
                    }
                }
            }

            if (!hasUpdated)
                break;
        }

        printf("%d\n", ans);
        for (int i = 0; i < valNum; i++)
        {
            printf("%d", atkArr[i]);
            if (i < valNum - 1)
                putchar(' ');
            else
                putchar('\n');
        }
    }
    return 0;
}
