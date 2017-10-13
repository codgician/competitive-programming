#include <iostream>
#include <cstdio>
#include <cmath>
#define SIZE 41
using namespace std;

int step[SIZE];

int main()
{
	ios::sync_with_stdio(false);
	step[1] = 1;
	step[2] = 1;
	for (int i = 3; i < SIZE; i++)
		step[i] = step[i - 1] + step[i - 2];
	int caseNum;
	cin >> caseNum;
	for (int t = 0; t < caseNum; t++)
	{
		int m;
		cin >> m;
		cout << step[m] << endl;
	}
	return 0;
}

