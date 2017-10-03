#include <iostream>
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
	int a, b;
	while (cin >> a >> b)
	{
		int gcd, lcm;
		if (b > a)
			swap(a, b);
		gcd = workGcd(a, b);
		lcm = a * b / gcd;
		cout << lcm << endl;
	}
	return 0;
}

