#include <iostream>
#include <cstdio>
using namespace std;

bool isLeap(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int main()
{
	ios::sync_with_stdio(false);
	int caseNum;
	cin >> caseNum;
	for (int t = 0; t < caseNum; t++)
	{
		int year, num, count = 0, irr = 1;
		cin >> year >> num;
		while (count < num)
		{
			if (isLeap(year))
			{
				count++;
				irr = 4;
			}
			year += irr;
		}
		cout << year - irr << endl;
	}
	return 0;
}

