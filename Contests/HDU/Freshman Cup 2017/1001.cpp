#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        int math, eng, pol, pro;
        cin >> math >> eng >> pol >> pro;
        int tot = math + eng + pol + pro;
        if (math >= 85 && eng >= 55 && pol >= 55 && pro >= 85 && tot >= 305)
        {
            if (tot > 370)
                cout << "A" << endl;
            else
                cout << "B" << endl;
        }
        else
        {
            cout << "C" << endl;
        }
    }

    return 0;
}
