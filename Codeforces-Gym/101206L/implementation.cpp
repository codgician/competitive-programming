#include <bits/stdc++.h>
using namespace std;
 
class Date {
public:
	int year, month, day;
	bool operator == (const Date & snd) const {
		return year == snd.year && month == snd.month && day == snd.day;
	}
 
	bool operator < (const Date & snd) const {
		if (year != snd.year)
			return year < snd.year;
		if (month != snd.month)
			return month < snd.month;
		return day < snd.day;
	}
	
	bool operator > (const Date & snd) const {
        return snd < *this && !(snd == *this);
	}
};
 
int getDay(Date d) {
    if (d.month < 3)
        d.month += 12, d.year--;
    return (d.day + ((d.month + 1) * 26) / 10 + d.year + d.year / 4 + 6 * (d.year / 100) + d.year / 400 + 5) % 7 + 1;
}

int main() {
	int caseNum; scanf("%d", &caseNum);
	for (int t = 1; t <= caseNum; t++) {
		Date d; int h, m, s, tim = 0;
		scanf("%d-%d-%d %d:%d:%d", &d.year, &d.month, &d.day, &h, &m, &s);
		tim = 3600 * h + 60 * m + s; 
		
		Date leftPt = Date{d.year, 3, 1}, rightPt = Date{d.year, 11, 1};
        leftPt.day += 14 - getDay(leftPt);
        rightPt.day += 7 - getDay(rightPt);
					
		cout << "Case #" << t << ": ";
		if (d > leftPt && d < rightPt) {
			cout << "PDT\n";
			continue;
		}
		
		if (d < leftPt || d > rightPt) {
			cout << "PST\n";
			continue;
		}
		
		if (d == leftPt) {
			int cur = 2 * 3600, nxt = 3 * 3600 - 1;
			if (tim >= cur && tim <= nxt) {
				cout << "Neither\n";
			} else if (tim < cur) {
				cout << "PST\n";
			} else {
				cout << "PDT\n";
			}
		}
		
		if (d == rightPt) {
			int cur = 3600, nxt = 2 * 3600 - 1;
			if (tim > nxt) {
				cout << "PST\n";
			} else if (tim < cur) {
				cout << "PDT\n";
			} else {
				cout << "Both\n";
			}
		}
	}
	return 0;
}
