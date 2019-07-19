#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int m, n;
	while (cin >> m >> n)
	{
		int maxLocM, maxLocN, maxScr = 0;
		int cntScr;
		for (int cntLocM = 1; cntLocM <= m; cntLocM++)
			for (int cntLocN = 1; cntLocN <= n; cntLocN++)
			{
				cin >> cntScr;	
				if (abs(cntScr) > abs(maxScr))
				{
					maxScr = cntScr;
					maxLocM = cntLocM;
					maxLocN = cntLocN;
				}
			}
		cout << maxLocM << " " << maxLocN << " " << maxScr << endl;
	}
	return 0;
}
