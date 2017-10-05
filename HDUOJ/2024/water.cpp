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
	getchar();
	for (int t = 0; t < caseNum; t++)
	{
		string str;
		bool flag = true;
		getline(cin, str);
		for (int i = 0; i < str.length(); i++)
		{
			// The first char must be alphabet or "_".
			if (str[i] != '_' && (str[i] < 'A' || (str[i] > 'Z' && str[i] < 'a') || str[i] > 'z'))
			{
				if (i == 0 || str[i] < '0' || str[i] > '9')
				{
					flag = false;
					cout << "no" << endl;
					break;
				}
			}
		}
		if (flag)
			cout << "yes" << endl;
	}
	return 0;
}

