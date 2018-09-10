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

#define SIZE 100010

long long int work(vector<int> & vec)
{
    long long int ans = 0;
    set<int> st;

    for (auto rit = vec.rbegin(); rit != vec.rend(); ++rit)
    {
        auto it = st.lower_bound(*rit);
        if (it == st.begin())
        {
            ans += *rit;
        }
        else
        {
            --it;
            ans += *rit - *it;
        }
        st.insert(*rit);
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int recNum;
    while (cin >> recNum)
    {
        vector<int> xVec, yVec;
        for (int i = 0; i < recNum; i++)
        {
            int x, y;
            cin >> x >> y;
            xVec.push_back(x);
            yVec.push_back(y);
        }

        cout << work(xVec) + work(yVec) << endl;
    }
    return 0;
}