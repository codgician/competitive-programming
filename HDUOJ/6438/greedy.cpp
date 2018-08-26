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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int num;
        cin >> num;

        priority_queue<pair<long long int, bool>, vector<pair<long long int, bool> >, greater<pair<long long int, bool> > > pq;

        int soldNum = 0;
        long long int soldSum = 0;
        for (int i = 0; i < num; i++)
        {
            long long int val;
            cin >> val;

            if (!pq.empty() && pq.top().first < val)
            {
                // Can bring profit, sell cheapest item!
                soldNum++;
                pair<long long int, bool> cntTop = pq.top();
                pq.pop();

                if (cntTop.second == 0)
                    soldNum--;  // Regert having sold it
                else
                    soldNum++;  // Actually sell it

                soldSum += val - cntTop.first;
                pq.push(make_pair(val, 0)); 
                pq.push(make_pair(val, 1)); 
            }
            else
            {
                // Can't any bring profit
                pq.push(make_pair(val, 1));
            }
        }
        cout << soldSum << " " << soldNum << endl;
    }

    return 0;
}