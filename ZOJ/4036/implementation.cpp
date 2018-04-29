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

int main()
{
	ios::sync_with_stdio(false);
	int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int len, b;
        cin >> len >> b;

        bool ans = false;
        for (int i = 0; i < len; i++)
        {
            int cnt;
            cin >> cnt;
            if ((cnt + b) % 7 == 0)
                ans = true;
        }

        if (ans)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
	return 0;
}