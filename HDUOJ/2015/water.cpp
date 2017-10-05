#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int arrLength, avgLength;
	while (cin >> arrLength >> avgLength)
	{
		int sum = 0;
		for (int i = 1; i <= arrLength; i++)
		{
			sum += 2 * i;
			if (i % avgLength == 0)
			{
				if (i == avgLength)
					cout << sum / avgLength;
				else
					cout << " " << sum / avgLength;
				sum = 0;
			} else if (i == arrLength && sum > 0) {
				cout << " " << sum / (arrLength % avgLength);
			}
		}
		cout << endl;
	}
	return 0;
}

