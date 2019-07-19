#include <iostream>
#include <cstdio>
#define UP 6
#define DOWN 4
#define STOP 5
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int num;
	while (cin >> num)
	{
		if (num == 0)
			break;
		int ans = 0, cnt = 0, next;
		for (int i = 0; i < num; i++)
		{
			cin >> next;
			if (next > cnt)
				ans += (next - cnt) * UP;
			else
				ans += (cnt - next) * DOWN;
			ans += STOP;
			cnt = next;
		}
		cout << ans << endl;
	}
	return 0;
}
