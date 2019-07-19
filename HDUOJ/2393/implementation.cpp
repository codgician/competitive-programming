#include <iostream>
#include <cstdio>
using namespace std;

bool isRight(int a, int b, int c)
{
	return a*a + b*b == c*c;
}

int main()
{
	ios::sync_with_stdio(false);
	int caseNum;
	cin >> caseNum;
	for (int t = 1; t <= caseNum; t++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		if (a > c)
			swap(a,c);
		if (b > c)
			swap(b,c);
		cout << "Scenario #" << t << ":" << endl;
		cout << (isRight(a, b, c) ? "yes" : "no") << endl << endl;
	}
	return 0;
}

