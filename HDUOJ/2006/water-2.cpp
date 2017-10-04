#include <iostream>
#include <cstdio>
using namespace std;

bool isOdd(int a)
{
    return a % 2 == 1 ? true : false;
}

int main()
{
    ios::sync_with_stdio(false);
    int ans = 1, num, i = 0;
    while (cin >> num)
    {
		ans = 1;
		for (int i = 0; i < num; i++)
		{
			int tmp;
			cin >> tmp;
			if (isOdd(tmp))
				ans *= tmp;
		}
		cout << ans << endl;
    }
    return 0;
}
