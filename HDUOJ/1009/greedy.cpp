// Improved for: http://acm.hdu.edu.cn/discuss/problem/post/reply.php?postid=2202&messageid=78&deep=1

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;

typedef struct Node {
	int javaBean;
	int catFood;
} room;

room arr[1010];

bool sortRule(const room &a, const room &b)
{
	if (a.catFood == 0 && b.catFood == 0)
		return a.javaBean > b.javaBean;
	else if (a.catFood == 0)
		return true;
	else if (b.catFood == 0)
		return false;
	else
		return (double)a.javaBean / a.catFood > (double)b.javaBean / b.catFood;
}

int main()
{
	ios::sync_with_stdio(false);
	int m, n;
	while (cin >> m >> n)
	{
		if (m == -1 && n == -1)
			break;

		for (int i = 0; i < n; i++)
			cin >> arr[i].javaBean >> arr[i].catFood;
		sort(arr, arr + n, sortRule);

		double ans = 0;
		for (int i = 0; i < n; i++)
		{
			if (m >= arr[i].catFood)
			{
				ans += arr[i].javaBean;
				m -= arr[i].catFood;
			} else {
				if (arr[i].catFood == 0)
					ans += (double)arr[i].javaBean;
				else
					ans += (double)arr[i].javaBean * m / arr[i].catFood;
				m = 0;
			}
		}
		printf("%.3lf\n", ans); 
	}
	return 0;
}
