#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

char str[10010];

int main()
{
	ios::sync_with_stdio(false);
	while (cin >> str)
	{
		sort(str, str + strlen(str));
		for (int i = 0; i < strlen(str); i++)
		{
			cout << str[i];
			if (i == strlen(str) - 1)
				cout << endl;
			else
				cout << " ";
		}
	}
	return 0;
}
