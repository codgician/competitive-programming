#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <iterator>
using namespace std;

priority_queue<int> pq;

int main()
{
    ios::sync_with_stdio(false);
    int len;
    cin >> len;

    long long int ans = 0;

    int cnt;
    cin >> cnt;
    pq.push(cnt);
    for (int i = 1; i < len; i++)
    {
        cin >> cnt;
        cnt -= i;
        pq.push(cnt);
        if (pq.top() > cnt)
        {
            ans += pq.top() - cnt;
            pq.pop();
            pq.push(cnt);
        }
    }

    cout << ans << endl;
    return 0;
}