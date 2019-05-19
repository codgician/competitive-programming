#include <bits/stdc++.h>
using namespace std;

#define DOT_SIZE 2010
#define SEG_SIZE 4000010

typedef struct _Dot {
    long long int x, y;
    int rank;
} Dot;

Dot arr[DOT_SIZE];
int rnkArr[DOT_SIZE];

typedef struct _Seg {
    int fstPt, sndPt;
    double slope;
} Seg;

Seg segArr[SEG_SIZE];

long long int get2Area(Seg & sg, Dot & dt) {
    Dot vec1 = {arr[sg.sndPt].x - arr[sg.fstPt].x, arr[sg.sndPt].y - arr[sg.fstPt].y};
    Dot vec2 = {arr[sg.sndPt].x - dt.x, arr[sg.sndPt].y - dt.y};
    long long int crossProd = vec1.x * vec2.y - vec2.x * vec1.y;
    return crossProd;
}

double getSlope(Dot & fst, Dot & snd) {
    return (double)(fst.y - snd.y) / (fst.x - snd.x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int num;
    long long int area;
    cin >> num >> area;
    area <<= 1;
    for (int i = 0; i < num; i++) {
        cin >> arr[i].x >> arr[i].y;
        rnkArr[i] = i;
    }
    sort(rnkArr + 0, rnkArr + num, [](const int fst, const int snd) {
        return arr[fst].x < arr[snd].x;
    });
    for (int i = 0; i < num; i++) {
        arr[rnkArr[i]].rank = i;
    }

    int segNum = 0;
    for (int i = 0; i < num; i++)
        for (int j = i + 1; j < num; j++)
            segArr[segNum++] = {i, j, getSlope(arr[i], arr[j])};
    sort(segArr + 0, segArr + segNum, [](const Seg & fst, const Seg & snd) {
        return fst.slope < snd.slope;
    });

    for (int i = 0; i < segNum; i++) {
        int fstPt = segArr[i].fstPt, sndPt = segArr[i].sndPt;
        int fstRank = arr[fstPt].rank, sndRank = arr[sndPt].rank;

        if (fstRank > sndRank)
            swap(fstRank, sndRank);

        if (fstRank > 0) {
            int leftRnk = 0, rightRnk = fstRank - 1;
            while (leftRnk <= rightRnk) {
                int midRnk = (leftRnk + rightRnk) >> 1;
                long long int cntArea = get2Area(segArr[i], arr[rnkArr[midRnk]]);
                if (cntArea == area) {
                    cout << "Yes" << endl;
                    cout << arr[fstPt].x << " " << arr[fstPt].y << endl;
                    cout << arr[sndPt].x << " " << arr[sndPt].y << endl;
                    cout << arr[rnkArr[midRnk]].x << " " << arr[rnkArr[midRnk]].y << endl;
                    return 0;
                }

                if (cntArea < area) {
                    rightRnk = midRnk - 1;
                } else {
                    leftRnk = midRnk + 1;
                }
            }
        }

        if (sndRank < num - 1) {
            int leftRnk = sndRank + 1, rightRnk = num - 1;
            while (leftRnk <= rightRnk) {
                int midRnk = (leftRnk + rightRnk) >> 1;
                long long int cntArea = get2Area(segArr[i], arr[rnkArr[midRnk]]);
                if (cntArea == area) {
                    cout << "Yes" << endl;
                    cout << arr[fstPt].x << " " << arr[fstPt].y << endl;
                    cout << arr[sndPt].x << " " << arr[sndPt].y << endl;
                    cout << arr[rnkArr[midRnk]].x << " " << arr[rnkArr[midRnk]].y << endl;
                    return 0;
                }

                if (cntArea < area) {
                    leftRnk = midRnk + 1;
                } else {
                    rightRnk = midRnk - 1;
                }
            }
        }

        swap(arr[fstPt].rank, arr[sndPt].rank);
        swap(rnkArr[fstRank], rnkArr[sndRank]);
    }
    cout << "No" << endl;

    return 0;
}