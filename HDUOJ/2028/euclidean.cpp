#include <iostream>
#include <cstdio>
using namespace std;

int workGcd(int a, int b)
{
	if (b == 0)
		return a;
	else 
		return workGcd(b, a%b);
}

int main()
{
	ios::sync_with_stdio(false);
	int num;
	while (cin >> num)
	{
		long long int a, b;
		cin >> a;
		for (int i = 1; i < num; i++)
		{
			cin >> b;
			// Mind overflow!!! orz.
			a = a / workGcd(a, b) * b;
		}
		cout << a << endl;
	}
	return 0;
}

