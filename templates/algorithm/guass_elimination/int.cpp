#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#define SIZE 10010
using namespace std;

int varNum, equNum;
int matrix[SIZE][SIZE];
int solution[SIZE];

bool isSolved[SIZE];

bool hasSameSign(int a, int b)
{
    return (a >> 31) == (b >> 31);
}

int getGcd(int a, int b)
{
    if (b == 0)
        return a;
    else
        return getGcd(b, a % b);
}

int getLcm(int a, int b)
{
    return a * b / getGcd(a, b);
}

void swapEqu(int equA, int equB)
{
    for (int cntVar = 0; cntVar <= varNum; cntVar++)
        swap(matrix[cntVar][equA], matrix[cntVar][equB]);
}

void printMatrix()
{
    cout << endl;
    for (int cntEqu = 0; cntEqu < equNum; cntEqu++)
        for (int cntVar = 0; cntVar <= varNum; cntVar++)
        {
            cout << setw(4) << matrix[cntVar][cntEqu];
            if (cntVar == varNum - 1)
                cout << " | ";
            else if (cntVar == varNum)
                cout << endl;
        }
    cout << endl;
}

void printSolution()
{
    for (int cntVar = 0; cntVar < varNum; cntVar++)
    {
        cout << "x_" << cntVar;
        if (isSolved[cntVar])
            cout << " = " << solution[cntVar];
        else
            cout << " is unsure.";
        cout << endl;
    }
}

int guass()
{
    for (int cntVar = 0; cntVar < varNum; cntVar++)
        isSolved[cntVar] = false;

    int headEqu = 0;

    for (int cntVar = 0; headEqu < equNum && cntVar < varNum; headEqu++, cntVar++)
    {
        // For current variable, find the line with the biggest absolute value.
        // Then swap it with the head line in order to promote precision.
        int maxAbsValue = abs(matrix[cntVar][headEqu]);
        int maxAbsEqu = headEqu;
        for (int cntEqu = headEqu + 1; cntEqu < equNum; cntEqu++)
            if (abs(matrix[cntVar][cntEqu] > maxAbsValue))
            {
                maxAbsValue = abs(matrix[cntVar][cntEqu]);
                maxAbsEqu = cntEqu;
            }
        swapEqu(headEqu, maxAbsEqu);
        // If even the biggest absolute value is 0, it means that this variable no longer exists.
        if (matrix[cntVar][headEqu] == 0)
        {
            headEqu--;
            continue;
        }

        // cout << "Before" << endl;
        // printMatrix();

        // Let's get started!
        for (int cntEqu = headEqu + 1; cntEqu < equNum; cntEqu++)
        {
            if (matrix[cntVar][cntEqu] != 0)
            {
                int lcm = getLcm(abs(matrix[cntVar][headEqu]), abs(matrix[cntVar][cntEqu]));
                int multipier = lcm / matrix[cntVar][cntEqu];
                int divider = lcm / matrix[cntVar][headEqu];

                // cout << "lcm: " << lcm << " multipier: " << multipier << " divider: " << divider << endl;

                // Update each equation.
                for (int cntColumn = cntVar; cntColumn <= varNum; cntColumn++)
                    matrix[cntColumn][cntEqu] = matrix[cntColumn][cntEqu] * multipier - matrix[cntColumn][headEqu] * divider;
            }
        }

        // cout << "Process" << endl;
        // printMatrix();
        //  cout << "headEqu: " << headEqu << endl;

    }

    // cout << "Final" << endl;
    // printMatrix();
    // cout << "headEqu: " << headEqu << endl;

    // And then let's solve it!
    // First check if the solution exists.
    // If the matrix has one solution, after the operations above headEqu should == equNum.
    // Otherwise there exists equations in which all parameters are 0.

    if (headEqu < equNum)
    {
        // Check if solutions exist.
        for (int cntEqu = headEqu; cntEqu < equNum; cntEqu++)
            if (matrix[varNum][cntEqu] != 0)
                return -1;

        // Then it must have multiple solutions!
        for (int cntEqu = headEqu - 1; cntEqu >= 0; cntEqu--)
        {
            // Let's first see which variable(s) is unsolved.
            int unsureNum = 0, unsureVar;
            for (int cntVar = 0; cntVar < varNum; cntVar++)
            {
                if (matrix[cntVar][cntEqu] > 0 && !isSolved[cntVar])
                    unsureNum++, unsureVar = cntVar;
            }

            // If current equation has more than one unsolved variable,
            // we can not figure out the solution from it.
            if (unsureNum > 1)
                continue;

            // Otherwise, we can figure it out from here.
            int constant = matrix[varNum][cntEqu];

            // Then we remove all those solved variables, leaving the unsolved one alone.
            for (int cntVar = 0; cntVar < varNum; cntVar++)
                if (isSolved[cntVar])
                    constant -= matrix[cntVar][cntEqu] * solution[cntVar];

            solution[unsureVar] = constant / matrix[unsureVar][cntEqu];
            isSolved[unsureVar] = true;
        }
    }
    else
    {
        // Then there must be only one solution.
        // Under this situation, equNum == varNum.
        for (int cntEqu = equNum - 1; cntEqu >= 0; cntEqu--)
        {
            int constant = matrix[varNum][cntEqu];

            // Remove solved variables.
            for (int cntVar = varNum - 1; cntVar >= cntEqu; cntVar--)
                constant -= matrix[cntVar][cntEqu] * solution[cntVar];

            solution[cntEqu] = constant / matrix[cntEqu][cntEqu];
            isSolved[cntEqu] = true;
        }
    }
    return 0;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> varNum >> equNum;

    for (int cntEqu = 0; cntEqu < equNum; cntEqu++)
        for (int cntVar = 0; cntVar <= varNum; cntVar++)
            cin >> matrix[cntVar][cntEqu];

    if(guass() == -1)
        cout << "No solution." << endl;
    else
        printSolution();

    return 0;
}
