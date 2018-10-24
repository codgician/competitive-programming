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
#include <bitset>
using namespace std;

#define SIZE 1010

bitset<SIZE> state, toggle[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int switchNum, blobNum;
    while (cin >> switchNum >> blobNum)
    {
        state.reset();
        for (int i = 0; i < switchNum; i++)
            toggle[i].reset();

        int litNum;
        cin >> litNum;
        for (int i = 0; i < litNum; i++)
        {
            int cnt;
            cin >> cnt;
            cnt--;
            state[cnt] = 1;
        }

        int ans = -1;
        for (int i = 0; i < switchNum; i++)
        {
            int num;
            cin >> num;

            if (i > 0)
                toggle[i] = toggle[i - 1];

            for (int j = 0; j < num; j++)
            {
                int cnt;
                cin >> cnt;
                cnt--;
                toggle[i][cnt] = !toggle[i][cnt];
            }

            if (ans == -1 && toggle[i] == state)
            {
                ans = i + 1;
            }
        }

        if (ans != -1)
        {
            cout << ans << endl;
            continue;
        }

        for (int i = 0; i < blobNum; i++)
        {
            if (toggle[switchNum - 1][i] == 1)
            {
                state[i] = !state[i];
            }
        }

        for (int i = 0; i < switchNum; i++)
        {
            if (state == toggle[i])
            {
                ans = switchNum + i + 1;
                break;
            }
        }

        cout << ans << endl;
    }

    return 0;
}