#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int caseNum;
	cin >> caseNum;
	for (int i = 0; i < caseNum; i++)
	{
		string str;
		cin >> str;
		bool flag = true;
		for (int i = 0; i <= str.length() / 2; i++)
		{
			if (str[i] != str[str.length() - i - 1])
			{
				flag = false;
				cout << "no" << endl;
				break;
			}
		}
		if (flag)
			cout << "yes" << endl;
	}
	return 0;
}

