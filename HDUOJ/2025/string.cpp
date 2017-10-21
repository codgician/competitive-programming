#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	string str;
	while(cin >> str)
	{
		char maxChar = 'a';
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] > maxChar)
				maxChar = str[i];
		}
		for (int i = 0; i < str.length(); i++)
		{
			cout << str[i];
			if (str[i] == maxChar)
				cout << "(max)";
		}
		cout << endl;
	}
	return 0;
}

