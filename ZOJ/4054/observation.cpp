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
    	string str;
    	cin >> str;

    	int len = str.size();
    	long long int ans = 0;

    	// Base
    	for (int i = 1; i <= ((len + 1) >> 1); i++)
    	{
    		ans += ((long long int)i * (len - i + 1)) << 1;
    	}
    	if (len & 1)
    		ans -= (long long int)((len + 1) >> 1) * ((len + 1) >> 1);

    	// Conflicts
    	int cntPt = 0;
		for (auto it = str.begin(); it != str.end(); ++it)
		{
			if (*it == '0')
			{
				// Contribute to seqs that start from here
				ans += len - cntPt;
				if (it != str.begin() && *prev(it) == '0')
				{
					ans += (long long int)cntPt * (len - cntPt);
				}
			}
			else if (*it == '1')
			{
				if (it != str.begin() && *prev(it) == '1')
				{
					ans += (long long int)cntPt * (len - cntPt);
				}
			}
			cntPt++;
		}    	

    	cout << ans << endl;
    }

    return 0;
}