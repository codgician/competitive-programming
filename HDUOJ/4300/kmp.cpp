#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <iterator>
#include <functional>
#define SIZE 100010
using namespace std;

char encrypt[26], decrypt[26];
int nextArr[SIZE], extArr[SIZE];

void initNext(string &str)
{
    int strLen = str.length();
    nextArr[0] = 0;
    for (int i = 1, matchNum = 0; i < strLen; i++)
    {
        while (matchNum > 0 && str[i] != str[matchNum])
            matchNum = nextArr[matchNum - 1];
        if (str[i] == str[matchNum])
            matchNum++;
        nextArr[i] = matchNum;
    }
}

void kmp(string &a, string &b)
{
    int aLen = a.length(), bLen = b.length();
    extArr[0] = 0;
    for (int i = 0, matchNum = 0; i < aLen; i++)
    {
        while (matchNum > 0 && (matchNum == bLen || a[i] != b[matchNum]))
            matchNum = nextArr[matchNum - 1];
        if (a[i] == b[matchNum])
            matchNum++;
        extArr[i] = matchNum;
    }
}

int main()
{
	ios::sync_with_stdio(false);
	int caseNum;
	cin >> caseNum;
	while (caseNum--)
	{
		string str;
        for (int i = 0; i < 26; i++)
        {
            char ch;
            cin >> ch;
            encrypt[i] = ch;
            decrypt[ch - 'a'] = 'a' + i;
        }

		cin >> str;
        int strLen = str.length();

        string cipher = str.substr(0, strLen >> 1);
        string text = str.substr(strLen >> 1);
        for (int i = 0; i < (int)text.length(); i++)
            cipher[i] = decrypt[cipher[i] - 'a'];

        initNext(cipher);
        kmp(text, cipher);
        
        int textLen = extArr[(int)text.length() - 1];
        int cipherLen = strLen - textLen;
        for (int i = 0; i < cipherLen; i++)
            cout << str[i];
        for (int i = 0; i < cipherLen; i++)
            cout << decrypt[str[i] - 'a'];
        cout << endl;
	}
	return 0;
}