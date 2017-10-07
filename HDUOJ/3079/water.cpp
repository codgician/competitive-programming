#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

char convertChar(char c)
{
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
		return c - 32;
	else if (c <= 'Z' && c != 'A' && c != 'E' && c != 'I' && c != 'O' && c!= 'U')
		return c + 32;
	else
		return c;
}

int main()
{
	ios::sync_with_stdio(false);
	int caseNum;
	cin >> caseNum;
	for (int t = 0; t < caseNum; t++)
	{
		string str;
		cin >> str;
		for (int i = 0; i < str.length(); i++)
			cout << convertChar(str[i]);
		cout << endl;
	}
	return 0;
}

