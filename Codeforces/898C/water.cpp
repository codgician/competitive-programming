#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 21
using namespace std;

typedef struct _Contact {
    string name;
    int phoneNum;
    string phone[999];
    bool isCountryCode[999];
} contact;

contact arr[SIZE];

bool cmpRulePhone(string a, string b)
{
    return a < b;
}

bool isSuffix(string a, string b)
{
    int aPt = a.length() - 1, bPt = b.length() - 1;

    if (bPt > aPt)
        return false;
    else if (a == b)
        return true;

    for (aPt, bPt; aPt >= 0 && bPt >= 0; aPt--, bPt--)
    {
        if (a[aPt] != b[bPt])
            return false;
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    int contactNum;
    cin >> contactNum;
    int arrPt = 0;

    for (int i = 0; i < contactNum; i++)
    {
        arr[arrPt].phoneNum = 0;

        int cntPt = arrPt;
        int phoneNum;
        string name;
        cin >> name >> phoneNum;
        for (int j = 0; j < arrPt; j++)
        {
            if (arr[j].name == name)
            {
                cntPt = j;
                break;
            }
        }

        arr[cntPt].name = name;

        for (int j = arr[cntPt].phoneNum; j < arr[cntPt].phoneNum + phoneNum; j++)
        {
            cin >> arr[cntPt].phone[j];
            arr[cntPt].isCountryCode[j] = false;
        }
        arr[cntPt].phoneNum += phoneNum;
        if (arrPt == cntPt)
            arrPt++;
    }

    cout << arrPt << endl;

    for (int i = 0; i < arrPt; i++)
    {
        int actualPhoneNum = arr[i].phoneNum;

        for (int j = 0; j < arr[i].phoneNum; j++)
        {
            for (int k = 0; k < arr[i].phoneNum; k++)
            {
                if (j == k || arr[i].isCountryCode[k])
                    continue;

                if (isSuffix(arr[i].phone[k], arr[i].phone[j]))
                {
                    arr[i].isCountryCode[j] = true;
                    actualPhoneNum--;
                    break;
                }
            }
        }

        cout << arr[i].name << " " << actualPhoneNum;

        if (actualPhoneNum > 0)
        {
            for (int j = 0; j < arr[i].phoneNum; j++)
            {
                if (!arr[i].isCountryCode[j])
                {
                    cout << " " << arr[i].phone[j];
                }
            }
        }
        cout << endl;
    }
    return 0;
}
