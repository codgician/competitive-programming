#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <set>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int pileNum;
        cin >> pileNum;
        int greenSum = 0;
        for (int i = 0; i < pileNum; i++)
        {
            int cnt;
            cin >> cnt;
            greenSum += cnt;
        }
        int blueSum = 0;
        for (int i = 0; i < pileNum; i++)
        {
            int cnt;
            cin >> cnt;
            blueSum += cnt;
        }
        if (greenSum > blueSum)
            cout << "BaoBao" << endl;
        else
            cout << "DreamGrid" << endl;
    }
    return 0;
}
