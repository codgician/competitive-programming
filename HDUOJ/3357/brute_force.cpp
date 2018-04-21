#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <climits>
#include <iomanip>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <functional>
#include <iterator>
#define SIZE 310
using namespace std;

bool arr[SIZE][SIZE];

int main()
{
	ios::sync_with_stdio(false);
	int vertexNum, edgeNum, casePt = 0;
	while (cin >> vertexNum >> edgeNum)
	{
		if (vertexNum == 0 && edgeNum == 0)
			break;

		int ans = 0;

		for (int i = 0; i < vertexNum; i++)
		{
			arr[i][i] = true;
			for (int j = i + 1; j < vertexNum; j++)
			{
				arr[i][j] = false;
				arr[j][i] = false;
			}
		}

		for (int i = 0; i < edgeNum; i++)
		{
			int from, to;
			cin >> from >> to;
			from--;
			to--;

			if (from == to || arr[to][from])
			{
				ans++;
			}
			else if (!arr[from][to])
			{
				for (int j = 0; j < vertexNum; j++)
				{
					if (arr[j][from])
					{
						for (int k = 0; k < vertexNum; k++)
						{
							if (arr[to][k])
							{
								arr[j][k] = true;
							}
						}
					}
				}
			}
		}

		cout << ++casePt << ". " << ans << endl;
	}
	return 0;
}