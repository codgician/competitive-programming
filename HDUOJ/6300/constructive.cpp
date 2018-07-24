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

#define SIZE 3030

typedef struct _Node
{
    int id;
    int x, y;
} Node;

Node arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int num;
        cin >> num;
        num *= 3;
        for (int i = 0; i < num; i++)
        {
            arr[i].id = i + 1;
            cin >> arr[i].x >> arr[i].y;
        }

        sort(arr + 0, arr + num, [](Node & fst, Node & snd){
            if (fst.x == snd.x)
                return fst.y < snd.y;
            return fst.x < snd.x;
        });

        for (int i = 0; i < num; i++)
        {
            cout << arr[i].id;
            if ((i + 1) % 3 == 0)
                cout << endl;
            else
                cout << " ";
        }
    }
    return 0;
}