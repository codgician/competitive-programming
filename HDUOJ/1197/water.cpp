#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	for (int i = 2992; i < 10000; i++)
	{
		int decSum = 0, ddecSum = 0, hexSum = 0;
		int decTmp = i, ddecTmp = i, hexTmp = i;
		for (int j = 0; j < 4; j++)
		{
			decSum += decTmp % 10;
			ddecSum += ddecTmp % 12;
			hexSum += hexTmp % 16;
			decTmp /= 10;
			ddecTmp /= 12;
			hexTmp /= 16;
		}
		if (decSum == ddecSum && ddecSum == hexSum)
			cout << i << endl;
	}
	return 0;
}
