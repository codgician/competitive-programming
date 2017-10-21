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
	getchar();
	for (int i = 0; i < caseNum; i++)
	{
		string str;
		getline(cin, str);

		int aNum = 0, eNum = 0, iNum = 0, oNum = 0, uNum = 0;
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == 'a')
				aNum++;
			else if (str[i] == 'e')
				eNum++;
			else if (str[i] == 'i')
				iNum++;
			else if (str[i] == 'o')
				oNum++;
			else if (str[i] == 'u')
				uNum++;
		}
		
		cout << "a:" << aNum << endl;
		cout << "e:" << eNum << endl;
		cout << "i:" << iNum << endl;
		cout << "o:" << oNum << endl;
		cout << "u:" << uNum << endl;
		if (i < caseNum - 1)
			cout << endl;
	}
	return 0;
}

