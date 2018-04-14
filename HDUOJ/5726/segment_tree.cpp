#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define leftSon ((segPt << 1) + 1)
#define rightSon ((segPt << 1) + 2)
#define SIZE 100010
using namespace std;

typedef struct _SegTree
{
	int leftPt, rightPt;
	long long int gcd;
} SegTree;

SegTree segTree[SIZE << 2];
long long int arr[SIZE];
map<long long int, long long int> numMap, tmpMap1, tmpMap2;

long long int getGcd(long long int a, long long int b)
{
	if (a < b)
		swap(a, b);

	while (b > 0)
	{
		long long int tmp = a % b;
		a = b;
		b = tmp;
	}

	return a;
}

void pushUp(int segPt)
{
	segTree[segPt].gcd = getGcd(segTree[leftSon].gcd, segTree[rightSon].gcd);
}

void build(int segPt, int leftPt, int rightPt)
{
	segTree[segPt].leftPt = leftPt;
	segTree[segPt].rightPt = rightPt;

	if (leftPt == rightPt)
	{
		segTree[segPt].gcd = arr[leftPt];
		return;
	}

	int midPt = (leftPt + rightPt) >> 1;
    build(leftSon, leftPt, midPt);
    build(rightSon, midPt + 1, rightPt);
	pushUp(segPt);
}

long long int query(int segPt, int leftPt, int rightPt)
{
	if (segTree[segPt].leftPt >= leftPt && segTree[segPt].rightPt <= rightPt)
	{
		return segTree[segPt].gcd;
	}

	long long int ans = -1;
	int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;

	if (leftPt <= midPt)
	{
		ans = query(leftSon, leftPt, rightPt);
	}

	if (rightPt > midPt)
	{
		if (ans == -1)
		{
			ans = query(rightSon, leftPt, rightPt);
		}
		else
		{
			ans = getGcd(ans, query(rightSon, leftPt, rightPt));
		}
	}

	return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	int caseNum;
	cin >> caseNum;
	for (int t = 1; t <= caseNum; t++)
	{
		numMap.clear();
		tmpMap1.clear();
		tmpMap2.clear();
		int num;
		cin >> num;
		for (int i = 0; i < num; i++)
		{
			cin >> arr[i];
		}

		build(0, 0, num - 1);

		tmpMap1[arr[0]]++;
		numMap[arr[0]]++;
		for (int i = 1; i < num; i++)
		{
			tmpMap2[arr[i]]++;
			numMap[arr[i]]++;

			for (auto it = tmpMap1.begin(); it != tmpMap1.end(); it++)
			{
				long long int nextGcd = getGcd(arr[i], it -> first);
				numMap[nextGcd] += it -> second;
				tmpMap2[nextGcd] += it -> second;
			}
			tmpMap1.clear();

			for (auto it = tmpMap2.begin(); it != tmpMap2.end(); it++)
			{
				tmpMap1[it -> first] = it -> second;
			}
			tmpMap2.clear();
		}

		int qNum;
		cin >> qNum;
		cout << "Case #" << t << ":" << endl; 
		while (qNum--)
		{
			int leftPt, rightPt;
			cin >> leftPt >> rightPt;
			leftPt--;
			rightPt--;

			int ans = query(0, leftPt, rightPt);
			cout << ans << " " << numMap[ans] << endl;
		}
	}
	return 0;
}