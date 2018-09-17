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

void decrypt(long long int leftPt, long long int rightPt, long long int & pos)
{
	if (leftPt < rightPt)
	{
		long long int k = (rightPt - leftPt + 1) >> 1;
		if (pos >= leftPt && pos <= leftPt + k - 1)
			decrypt(leftPt, leftPt + k - 1, pos);
		else
			decrypt(leftPt + k, rightPt, pos);
	}
	pos = leftPt + rightPt - pos;
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
    	long long int len, pos;
    	cin >> len >> pos;
    	decrypt(1, len, pos);
    	cout << pos << endl;
    }

    return 0;
}