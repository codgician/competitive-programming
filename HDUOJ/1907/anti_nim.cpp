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

        int sg = 0, maxSize = 1;
        for (int i = 0; i < num; i++)
        {
            int cnt;
            cin >> cnt;
            sg ^= cnt;
            maxSize = max(maxSize, cnt);
        }

        bool ans = false;
        if (maxSize == 1 && sg == 0)
            ans = true;
        else if (maxSize > 1 && sg != 0)
            ans = true;

        if (ans)
            cout << "John" << endl;
        else
            cout << "Brother" << endl;
    }

    return 0;
}