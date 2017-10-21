#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

char getBigCase(char c)
{
	if (c >= 'a' && c <= 'z')
		return c - 32;
	else
		return c;
}

int main()
{
	ios::sync_with_stdio(false);
	string str;
	while (getline(cin, str))
	{
		for (int i = 0; i < str.length(); i++)
		{
			if (i == 0 || str[i - 1] == ' ')
				str[i] = getBigCase(str[i]);
		}
		cout << str << endl;
	}
	return 0;
}

