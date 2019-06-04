#include <bits/stdc++.h>
using namespace std;

#define DOT_SIZE 1010
#define SEG_SIZE 1000010

typedef struct _Dot {
    int x, y;
    int rank;
} Dot;

Dot arr[DOT_SIZE];
int rnkArr[DOT_SIZE];

typedef struct _Seg {
    int fstPt, sndPt;
    double slope;
} Seg;

Seg segArr[SEG_SIZE];

double getArea(Seg & sg, Dot & dt) {
    Dot vec1 = {arr[sg.sndPt].x - arr[sg.fstPt].x, arr[sg.sndPt].y - arr[sg.fstPt].y};
    Dot vec2 = {arr[sg.sndPt].x - dt.x, arr[sg.sndPt].y - dt.y};
    double crossProd = 1ll * vec1.x * vec2.y - 1ll * vec2.x * vec1.y;
    return abs(crossProd / 2);
}

double getSlope(Dot & fst, Dot & snd) {
    return (double)(fst.y - snd.y) / (fst.x - snd.x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int num;
    while (cin >> num) {
        for (int i = 0; i < num; i++) {
            cin >> arr[i].x >> arr[i].y;
            rnkArr[i] = i;
        }
        sort(rnkArr + 0, rnkArr + num, [](const int fst, const int snd) {
            if (arr[fst].x == arr[snd].x)
                return arr[fst].y > arr[snd].y;
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

        double ans = DBL_MAX;
        for (int i = 0; i < segNum; i++) {
            int fstPt = segArr[i].fstPt, sndPt = segArr[i].sndPt;
            int fstRank = arr[fstPt].rank, sndRank = arr[sndPt].rank;

            if (fstRank > sndRank)
                swap(fstRank, sndRank);

            if (fstRank > 0)
                ans = min(ans, getArea(segArr[i], arr[rnkArr[fstRank - 1]]));
            if (sndRank < num - 1)
                ans = min(ans, getArea(segArr[i], arr[rnkArr[sndRank + 1]]));

            swap(arr[fstPt].rank, arr[sndPt].rank);
            swap(rnkArr[fstRank], rnkArr[sndRank]);
        }
        cout << fixed << setprecision(2) << ans << endl;
    }

    return 0;
}