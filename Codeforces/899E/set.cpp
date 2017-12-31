#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <queue>
#include <vector>
#include <set>
#include <iterator>
#define SIZE 200001
using namespace std;

int arr[SIZE];

set<pair<int, int> > len, segment;  // len<-length, leftPt>; segment<leftPt, length>
int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    int leftPt = 0, rightPt = 0;
    while (rightPt < n)
    {
        cin >> arr[rightPt];
        if (arr[rightPt] != arr[leftPt])
        {
            len.insert({-(rightPt - leftPt), leftPt}); // length * (-1), descending order
            segment.insert({leftPt, rightPt - leftPt});
            leftPt = rightPt;
        }
        rightPt++;
    }
    len.insert({-(rightPt - leftPt), leftPt});
    segment.insert({leftPt, rightPt - leftPt});

    int ans = 0;
    while (len.size())
    {
        ans++;
        pair<int, int> cntLen = *len.begin();
        len.erase(cntLen);
        set<pair<int, int> >::iterator leftSegmentPos = segment.lower_bound({cntLen.second, -cntLen.first});
        set<pair<int, int> >::iterator rightSegmentPos = segment.upper_bound({cntLen.second, -cntLen.first});

        // Merge left and right segment if they exist and has the same number
        if (leftSegmentPos != segment.begin() && rightSegmentPos != segment.end())
        {
            leftSegmentPos--;
            if (arr[(*leftSegmentPos).first] == arr[(*rightSegmentPos).first])
            {
                pair<int, int> leftSegment = *leftSegmentPos, rightSegment = *rightSegmentPos;
                len.erase({-leftSegment.second, leftSegment.first});
                len.erase({-rightSegment.second, rightSegment.first});
                segment.erase(leftSegment);
                segment.erase(rightSegment);
                len.insert({-(leftSegment.second + rightSegment.second), leftSegment.first});
                segment.insert({leftSegment.first, leftSegment.second + rightSegment.second});
            }
        }
        segment.erase({cntLen.second, -cntLen.first});
    }
    cout << ans << endl;
    return 0;
}
