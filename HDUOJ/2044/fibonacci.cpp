#include <iostream>
#include <cstdio>
#define SIZE 51
using namespace std;

long long fibb[SIZE];

void getFibb()
{
	fibb[1] = 1;
	fibb[2] = 2;
	for (int i = 3; i < SIZE - 1; i++)
		fibb[i] = fibb[i - 1] + fibb[i - 2];
}

int main()
{
	ios::sync_with_stdio(false);
	getFibb();
	int caseNum;
	cin >> caseNum;
	for (int t = 0; t < caseNum; t++)
	{
		int startPt, endPt;
		cin >> startPt >> endPt;
		cout << fibb[endPt - startPt] << endl;
	}
	return 0;
}

