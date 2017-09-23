// POJ - 1222
// Enumeration!

// We only need to enumerate the first row,
// because the rest of the rows will be decided by the first row.
// The goal of operating the (n+1)th row is to make the (n)th row all 0.
// Then at last we check if the last row is all 0.

#include <iostream>
#include <cstring>
using namespace std;

bool lights[7][7];
bool tmp[7][7];
bool result[7][7];

void switchLight(int i, int j)
{
    tmp[i][j] = !tmp[i][j];
    if (i > 0)
        tmp[i - 1][j] = !tmp[i - 1][j];
    if (i < 5)
        tmp[i + 1][j] = !tmp[i + 1][j];
    if (j > 0)
        tmp[i][j - 1] = !tmp[i][j - 1];
    if (j < 4)
        tmp[i][j + 1] = !tmp[i][j + 1];
}

void applyColumn(int i)
{
    for (int j = 0; j < 5; j++)
    {
        if (result[i][j])
            switchLight(i, j);
    }
}

void genNextResult(int i)
{
    for (int j = 0; j < 5; j++)
        if (tmp[i][j])
            result[i + 1][j] = 1;
}

int main()
{
    ios::sync_with_stdio(false);

    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        // Initialize.
        for (int j = 0; j < 5; j++)
            for (int i = 0; i < 6; i++)
                cin >> lights[i][j];

        for (int j = 0; j < 32; j++)
        {
            // Initialize.
            memset(result, 0 ,sizeof(result));
            memcpy(tmp, lights, sizeof(lights));

            // Initialize the first row of result[].
            if (j & 1)
                result[0][0] = 1;
            if (j & 2)
                result[0][1] = 1;
            if (j & 4)
                result[0][2] = 1;
            if (j & 8)
                result[0][3] = 1;
            if (j & 16)
                result[0][4] = 1;

            // Emulate.
            for (int k = 0; k < 6; k++)
            {
                applyColumn(k);
                genNextResult(k);
            }

            // Validate.
            bool flag = true;
            for (int k = 0; k < 5; k++)
            {
                if (tmp[5][k])
                {
                    flag = false;
                    break;
                }
            }

            if (flag)
            {
                cout << "PUZZLE #" << (t + 1) << endl;
                for (int j = 0; j < 5; j++)
                {
                    for (int i = 0; i < 6; i++)
                    {
                        cout << result[i][j];
                        if (i < 6)
                            cout << " ";
                    }
                    cout << endl;
                }
                break;
            }
        }
    }
    return 0;
}
