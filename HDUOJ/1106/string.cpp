#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

int arr[10010];

int getPow (int a, int n)
{
    int result = 1;
    for (int i = 0; i < n; i++)
        result *= a;
    return result;
}

int getNum (string str, int startPt, int endPt)
{
    int num = 0, powerNum = 0;
    for (int i = endPt; i >= startPt; i--)
    {
        num += getPow(10, powerNum) * (str[i] - '0');
        powerNum++;
    }
    return num;
}

int main()
{
    ios::sync_with_stdio(false);
    string str;
    while(cin >> str)
    {
        int arrPt = 0, startPt;
        for (int i = 0; i < str.length(); i++)
        {
            
            if ((i == 0 && str[0] != '5') || (str[i] != '5' && str[i - 1] == '5'))
            {
                // Record start point.
                startPt = i;
                // cout << "start: " << startPt << endl;
            }
            if (str[i] != '5' && (str[i + 1] == '5' || i == str.length() - 1))
            {
                // This is the end point. Get & store number.
                // cout << "end: " << i << endl;
                arr[arrPt] = getNum(str, startPt, i);
                arrPt++;
            }
        }
        sort(arr, arr + arrPt);
        for (int i = 0; i < arrPt; i++)
        {
            cout << arr[i];
            if (i < arrPt - 1)
                cout << " ";
            else
                cout << endl;
        }
                 
    }
    return 0;
}