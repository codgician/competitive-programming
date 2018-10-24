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

    string fst, snd;
    while (cin >> fst >> snd)
    {
        int ans = 0;
        int fstLen = fst.size(), sndLen = snd.size();
        for (int i = 0; i + sndLen <= fstLen; i++)
        {
            bool isAccepted = true;
            for (int j = 0; j < sndLen; j++)
            {
                if (fst[i + j] == snd[j])
                {
                    isAccepted = false;
                    break;
                }
            }

            if (isAccepted)
                ans++;
        }
        cout << ans << endl;
    }

    return 0;
}