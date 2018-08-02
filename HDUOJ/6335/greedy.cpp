#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
using namespace std;

#define SIZE 101

int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int probNum, stuNum;
        cin >> probNum >> stuNum;
        for (int i = 0; i < probNum; i++)
        {
            int fst, snd;
            cin >> fst >> snd;
            arr[i] = fst + snd;
        }

        sort(arr + 0, arr + probNum);

        int ans = probNum;
        for (int i = 0; i < probNum; i++)
        {
            stuNum /= arr[i];
            if (stuNum == 0)
            {
                ans = i;
                break;
            }
        }

        cout << ans << endl;
    }
    return 0;
}