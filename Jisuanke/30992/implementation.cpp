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
#include <list>
#include <functional>
#include <iterator>
using namespace std;

#define PLAYER_SIZE 210

list<int> stk;
multiset<int> mst[PLAYER_SIZE];
int sumArr[PLAYER_SIZE];

int getRealVal(int n)
{
    return n > 13 ? n - 13 : n;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        int playerNum, cardNum;
        cin >> playerNum >> cardNum;
        stk = list<int>();
        for (int i = 0; i < playerNum; i++)
        {
            mst[i] = multiset<int>();
            sumArr[i] = 0;
        }

        for (int i = 0; i < cardNum; i++)
        {
            int cnt;
            cin >> cnt;
            // Convert to 3 ~ 15
            if (cnt < 3)
                cnt += 13;
            stk.push_front(cnt);
        }

        // Initialize
        for (int i = 0; i < playerNum; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (stk.size() > 0)
                {
                    mst[i].insert(stk.back());
                    sumArr[i] += getRealVal(stk.back());
                    stk.pop_back();
                }
            }
        }

        bool isOn = true;
        int lastPlayer = 0;
        int lastVal = *mst[lastPlayer].begin();
        sumArr[lastPlayer] -= getRealVal(*mst[lastPlayer].begin());
        mst[lastPlayer].erase(mst[lastPlayer].begin());

        // Throw card
        for (int i = (lastPlayer + 1) % playerNum; isOn; i = (i + 1) % playerNum)
        {
            if (i == lastPlayer)
            {
                if (stk.size() > 0)
                {
                    mst[i].insert(stk.back());
                    sumArr[i] += getRealVal(stk.back());
                    stk.pop_back();
                }

                for (int j = (i + 1) % playerNum; j != i; j = (j + 1) % playerNum)
                {
                    if (stk.size() > 0)
                    {
                        mst[j].insert(stk.back());
                        sumArr[j] += getRealVal(stk.back());
                        stk.pop_back();
                    }
                }

                lastVal = *mst[i].begin();
                sumArr[i] -= getRealVal(*mst[i].begin());
                mst[i].erase(mst[i].begin());

                if (mst[i].size() == 0)
                {
                    isOn = false;
                    break;
                }

                continue;
            }

            auto it = mst[i].find(lastVal + 1);
            if (it == mst[i].end())
            {
                if (lastVal != 15 && *(prev(mst[i].end())) == 15)
                {
                    lastVal = 15;
                    lastPlayer = i;
                    sumArr[i] -= getRealVal(15);
                    mst[i].erase(prev(mst[i].end()));

                    if (mst[i].size() == 0)
                    {
                        isOn = false;
                        break;
                    }
                }
            }
            else
            {
                lastVal = *it;
                lastPlayer = i;
                sumArr[i] -= getRealVal(*it);
                mst[i].erase(it);

                if (mst[i].size() == 0)
                {
                    isOn = false;
                    break;
                }
            }
        }

        cout << "Case #" << t << ":" << endl;
        for (int i = 0; i < playerNum; i++)
        {
            if (mst[i].size() == 0)
            {
                cout << "Winner" << endl;
                continue;
            }

            cout << sumArr[i] << endl;
        }
    }
    return 0;
}