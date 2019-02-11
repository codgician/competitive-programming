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

map<string, char> mp;

string getBin(char ch)
{
	int num;
	if (ch >= '0' && ch <= '9')
		num = ch - '0';
	else if (ch >= 'A' && ch <= 'F')
		num = ch - 'A' + 10;
	else
		num = ch - 'a' + 10;

	string ret;
	for (int i = 3; i >= 0; i--)
	{
		if (num & (1 << i))
			ret.push_back('1');
		else
			ret.push_back('0');
	}

	return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
    	mp.clear();
    	int ansLen, charNum;
    	cin >> ansLen >> charNum;

    	for (int i = 0; i < charNum; i++)
    	{
    		int ascii;
    		string str;
    		cin >> ascii >> str;
    		mp[str] = ascii;
    	}

    	string str, binStr, decStr;
    	cin >> str;
    	for (auto it = str.begin(); it != str.end(); ++it)
    	{
    		binStr += getBin(*it);
    	}

    	bool cntOneNum = 1;
    	string cntStr;
    	for (int i = 0; i < (int)binStr.size(); i++)
    	{
    		if (cntStr.size() == 8)
    		{
    			if (cntOneNum == binStr[i] - '0')
    			{
    				decStr += cntStr;
    			}

    			cntOneNum = 1;
    			cntStr.clear();
    		}
    		else
    		{
    			cntStr.push_back(binStr[i]);
    			if (binStr[i] == '1')
    				cntOneNum = !cntOneNum;
    		}
    	}

    	int decLen = 0;
    	cntStr.clear();
    	for (auto it = decStr.begin(); it != decStr.end() && decLen < ansLen; ++it)
    	{
    		cntStr.push_back(*it);
    		if (mp.find(cntStr) != mp.end())
    		{
    			cout << mp[cntStr];
    			decLen++;
    			cntStr.clear();
    		}
    	}
    	cout << endl;
    }
    return 0;
}