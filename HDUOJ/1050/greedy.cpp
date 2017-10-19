#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define SIZE 401
using namespace std;

bool isDone[SIZE];

typedef struct Node {
	int startPt;
	int endPt;
} mv;

mv arr[SIZE];

bool cmpRule(mv a, mv b)
{
	return a.startPt < b.startPt;
}

bool check(int cntPt, int prevEndPt)
{
    if (cntPt & 1 == 0)
        cntPt--;
    if (prevEndPt & 1 == 1)
        prevEndPt++;
    return cntPt > prevEndPt;
}

int main()
{
	ios::sync_with_stdio(false);
	int caseNum;
	cin >> caseNum;
	for (int t = 0; t < caseNum; t++)
	{
		int mvTable;
		cin >> mvTable;
		for (int i = 0; i < mvTable; i++)
		{
			isDone[i] = false;
			int startPt, endPt;
			cin >> startPt >> endPt;
			if (startPt > endPt)
				swap(startPt, endPt);
			arr[i].startPt = startPt;
			arr[i].endPt = endPt;
		}

		sort(arr, arr + mvTable, cmpRule);

		int doneNum = 0, sumTime = 0;
		while (doneNum < mvTable)
		{
			int prevEndPt = 0;
			for (int i = 0; i < mvTable; i++)
			{
				if (!isDone[i] && check(arr[i].startPt, prevEndPt))
				{
					isDone[i] = true;
					doneNum++;
					prevEndPt = arr[i].endPt;
				}
			}
			sumTime += 10;
		}
		cout << sumTime << endl;
	}
	return 0;
}
