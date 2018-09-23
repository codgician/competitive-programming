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

#define SIZE 1000010

long long int arr[SIZE];

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
    	long long int cntMoney;
    	cin >> num >> cntMoney;
    	for (int i = 0; i < num; i++)
    	{
    		cin >> arr[i];
    	}
    	for (int i = 0; i < num; i++)
    	{
    		long long int cnt;
    		cin >> cnt;
    		arr[i] -= cnt;
    	}

    	int startPt = 0, cntPt = 0;
    	while (cntPt < startPt + num)
    	{
    		cntMoney += arr[cntPt % num];
    		while (startPt < min(num, cntPt + 1) && cntMoney < 0)
    		{
    			// Pop head
    			cntMoney -= arr[startPt++];
    		}

    		if (cntMoney < 0)
    		{
    			startPt = -2;
    			break;
    		}

    		cntPt++;
    	}

    	cout << startPt + 1 << endl;
    }

    return 0;
}