#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        int courseNum;
        double scoreSum = 0, creditSum = 0;
        bool isZero = false;
        cin >> courseNum;
        for (int i = 0; i < courseNum; i++)
        {
            string courseName;
            double credit, score;
            cin >> courseName >> credit >> score;
            if (score >= 60)
            {
                scoreSum += score * credit;
                creditSum += credit;
            }
            else
            {
                isZero = true;
            }
        }
        if (creditSum == 0 || isZero)
            cout << "Sorry!" << endl;
        else
            cout << fixed << setprecision(2) << scoreSum / creditSum << endl;
        if (t < caseNum - 1)
            cout << endl;
    }
    return 0;
}
