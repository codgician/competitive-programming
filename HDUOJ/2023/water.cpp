#include <iostream>
#include <cstdio>
#include <iomanip>
using namespace std;

double scr[55][10], avg[10];

int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	while (cin >> n >> m)
	{
		int stuNum = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				cin >> scr[i][j];

		// Calculate average score for courses.
		for (int j = 0; j < m; j++)
		{
			double tmp = 0;
			for (int i = 0; i < n; i++)
				tmp += scr[i][j];
			avg[j] = tmp / (double)n;
		}

		// Calculate average score for students.
		// And validate whether student meets the requirement.
		for (int i = 0; i < n; i++)
		{
			double tmp = 0;
			bool flag = true;
			for (int j = 0; j < m; j++)
			{
				tmp += scr[i][j];
				if (scr[i][j] < avg[j])
					flag = false;
			}

			if (flag)
                stuNum++;


            cout << fixed << setprecision(2) << tmp / (double)m;
			if (i == n - 1)
				cout << endl;
			else
				cout << " ";
		}

		for (int j = 0; j < m; j++)
		{
			cout << fixed << setprecision(2) << avg[j];
			if (j == m - 1)
				cout << endl;
			else
				cout << " ";
		}

		cout << stuNum << endl << endl;

	}
	return 0;
}
