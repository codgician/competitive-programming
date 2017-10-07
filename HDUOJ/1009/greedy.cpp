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
		// FUCK!
		if (n == 0)
		{
			printf("0.000\n");
			continue;
		}
		for (int i = 0; i < n; i++)
			cin >> arr[i].javaBean >> arr[i].catFood;
		sort(arr, arr + n, sortRule);

		double ans = 0;
		int pt = 0;
		while (m > 0)
		{
			if (m >= arr[pt].catFood)
			{
				ans += arr[pt].javaBean;
				m -= arr[pt].catFood;
			} else {
				ans += (double)arr[pt].javaBean * m / arr[pt].catFood;
				m = 0;
			}
			pt++;
		}
		printf("%.3lf\n", ans); 
	}
	return 0;
}
