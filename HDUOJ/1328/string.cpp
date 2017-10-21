#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int caseNum;
	cin >> caseNum;
	for (int t = 1; t <= caseNum; t++)
	{
		string str;
		cin >> str;
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == 'Z')
				str[i] = 'A';
			else
				str[i] += 1;
		}
		cout << "String #" << t << endl << str << endl << endl;
	}
	return 0;
}

