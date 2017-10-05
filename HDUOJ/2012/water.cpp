#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

bool isPrime(int x)
{
	for (int i = 2; i <= sqrt(x); i++)
	{
		if (x % i == 0)
			return false;
	}
	return true;
}

int calc(int n)
{
	return n * n + n + 41;
}

int main()
{
	ios::sync_with_stdio(false);
	int x, y;
	while (cin >> x >> y)
	{
		if (x == 0 && y == 0)
			break;
		bool flag = false;
		for (int i = x; i <= y; i++)
		{
			if (!isPrime(calc(i)))
			{
				cout << "Sorry" << endl;
				flag = true;
				break;
			}
		}
		if (!flag)
			cout << "OK" << endl;
	}
	return 0;
}
