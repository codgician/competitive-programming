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

int ans[20] = {1, 2, 3, 5, 7, 11, 13, 17, 23, 31, 37, 53, 71, 73, 113, 131, 137, 173, 311, 317};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
    	string str;
    	cin >> str;

    	cout << "Case #" << t << ": ";
    	if (str.length() >= 4)
    	{
    		cout << ans[19] << endl;
    		continue;
    	}

    	int num = 0;
    	for (auto it = str.begin(); it != str.end(); ++it)
    	{
    		num = num * 10 + (*it - '0');
    	}

    	int pos = lower_bound(ans + 0, ans + 20, num) - ans;
    	if (pos > 19)
    		pos = 19;
    	if (ans[pos] > num)
    		pos--;
    	cout << ans[pos] << endl;
    }

    return 0;
}