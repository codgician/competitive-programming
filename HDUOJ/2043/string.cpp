#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

bool type[4];
int typeNum;

void recordType(int i)
{
	if (!type[i])
	{
		typeNum++;
		type[i] = true;
	}
	return;
}

bool isGreatPwd(string pwd)
{
	if (pwd.length() < 8 || pwd.length() > 16)
		return false;
	
	// Initialize.
	typeNum = 0;
	for (int i = 0; i < 4; i++)
		type[i] = false;
	
	// Check every char inside the string.
	for (int i = 0; i < pwd.length(); i++)
	{
		if (pwd[i] >= 'A' && pwd[i] <= 'Z')
			recordType(0);
		else if (pwd[i] >= 'a' && pwd[i] <= 'z')
			recordType(1);
		else if (pwd[i] >= '0' && pwd[i] <= '9')
			recordType(2);
		else
			recordType(3);
	}

	if (typeNum < 3)
		return false;
	return true;
}

int main()
{
	ios::sync_with_stdio(false);
	int caseNum;
	cin >> caseNum;
	for (int t = 0; t < caseNum; t++)
	{
		string pwd;
		cin >> pwd;
		if (isGreatPwd(pwd))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}
