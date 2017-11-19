#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#define SIZE 100001
using namespace std;

typedef struct Node {
    string num;
    int mark[3];
} phone;

phone arr[SIZE];

char getType(int i)
{
    switch(i)
    {
        case 0:
            return 'q';
        case 1:
            return 's';
        case 2:
            return 'k';
    }
}

char getIndex(char c)
{
    if (c == 'q')
        return 0;
    else if (c == 's')
        return 1;
    else if (c == 'k')
        return 2;
}

int main()
{
    ios::sync_with_stdio(false);
    int oprNum;
    while (cin >> oprNum)
    {
        int num = 0;
        for (int t = 0; t < oprNum; t++)
        {
            char opr;
            string phoneNum;
            cin >> opr >> phoneNum;
            if (opr == 'A')
            {
                bool isAnswered = false;
                for (int i = 0; i < num; i++)
                {
                    if (arr[i].num == phoneNum)
                    {
                        int maxTypeVal = arr[i].mark[0], maxTypeIndex = 0;
                        for (int j = 1; j < 3; j++)
                        {
                            if (arr[i].mark[j] > maxTypeVal)
                            {
                                maxTypeVal = arr[i].mark[j];
                                maxTypeIndex = j;
                            }
                        }
                        cout << getType(maxTypeIndex) << "=" << maxTypeVal << endl;
                        isAnswered = true;
                        break;
                    }
                }

                if (!isAnswered)
                    cout << "N" << endl;

            }
            else if (opr == 'B')
            {
                char type;
                cin >> type;

                bool isRecorded = false;
                for (int i = 0; i < num; i++)
                {
                    if (arr[i].num == phoneNum)
                    {
                        arr[i].mark[getIndex(type)]++;
                        isRecorded = true;
                        break;
                    }
                }

                if (!isRecorded)
                {
                    arr[num].num = phoneNum;
                    for (int i = 0; i < 3; i++)
                    {
                        arr[num].mark[i] = 0;
                    }
                    arr[num].mark[getIndex(type)]++;
                    num++;
                }
                cout << "Y" << endl;
            }
        }
    }
    return 0;
}
