#include <iostream>
#include <cstdio>
#include <climits>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int judgeNum;
	while (cin >> judgeNum)
	{
		int maxScr = INT_MIN;
		int minScr = INT_MAX;
		int sum = 0;
		for (int i = 0; i < judgeNum; i++)
		{
			int tmp;
			cin >> tmp;
			sum += tmp;
			if (tmp > maxScr)
				maxScr = tmp;
			else if (tmp < minScr)
				minScr = tmp;
		}
		float avgScr = (float)(sum - maxScr - minScr) / (judgeNum - 2);
		printf("%.2f\n", avgScr);
	}
	return 0;
}

