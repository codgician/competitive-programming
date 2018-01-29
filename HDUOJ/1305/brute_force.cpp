#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <map>
#define SIZE 10
using namespace std;

string arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    string str;
    int arrPt = 0, setNum = 1;
    while (cin >> arr[arrPt++])
    {
        if (arr[arrPt - 1] == "9")
        {
            bool ans = true;
            for (int i = 0; i < arrPt - 1; i++)
            {
                for (int j = i + 1; j < arrPt - 1; j++)
                {
                    bool notPrefix = false;
                    for (int k = 0; k < min(arr[i].length(), arr[j].length()); k++)
                    {
                        if (arr[i][k] != arr[j][k])
                        {
                            notPrefix = true;
                            break;
                        }
                    }
                    if (!notPrefix)
                    {
                        ans = false;
                        break;
                    }
                }
            }
            cout << "Set " << setNum << " is ";
            if (!ans)
            {
                cout << "not ";
            }
            cout << "immediately decodable" << endl;
            arrPt = 0;
            setNum++;
        }
    }
    return 0;
}
