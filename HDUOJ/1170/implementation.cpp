#include <iostream>
#include <cstdio>
using namespace std;

void output(double ans)
{
	if (ans != (int)ans)
		printf("%.0lf\n", ans);
	else
		printf("%.0lf\n", ans);
}

int main()
{
	ios::sync_with_stdio(false);
	int caseNum;
	cin >> caseNum;
	for (int i = 0; i < caseNum; i++)
	{
		char opr;
		double a, b;
		cin >> opr >> a >> b;
		if (opr == '+')
			output(a + b);
		else if (opr == '-')
			output(a - b);
		else if (opr == '*')
			output(a * b);
		else if (opr == '/')
			output(a / b);
	}
	return 0;
}

