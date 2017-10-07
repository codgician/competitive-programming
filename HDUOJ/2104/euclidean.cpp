#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int gcd(int a, int b)
{
	if (b == 0)
		return a;
	else
		return gcd(b, a % b);

}

int main()
{
	ios::sync_with_stdio(false);
	int m, n;
	while (cin >> m >> n)
	{
		if (m == -1 && n == -1)
			break;
		if (n > m)
			swap(m, n);
		if (gcd(m, n) == 1)
			cout << "YES";
		else
			cout << "POOR Haha";
		cout << endl;
	}
	return 0;
}
