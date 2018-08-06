#include <bits/stdc++.h>

using namespace std;

vector<int> ask(int i);

struct interval {
    int low;
    int high;
    int leftCnt;
    int midCnt;
    int rightCnt;
};

void printinterval(interval x) {
//    cout << "interval: " << x.low << " <= i < " << x.high << ", " << x.leftCnt << ", " << x.midCnt << ", " << x.rightCnt << "\n";
}

map<int, vector<int>> cache;
vector<int> smartAsk(int i) {
    if (cache.find(i) == cache.end()) {
        cache[i] = ask(i);
    }
    return cache[i];
}

int find_best(int N) {
    vector<int> smalls;

    int maxI = 0;
    int maxCnt = 0;

    int maxSmalls = sqrt(N) * 2;

    for (int i = 0; i <= maxSmalls && i != N; ++i) {
        auto x = smartAsk(i);
        if (x[0] + x[1] > maxCnt) {
            maxCnt = x[0] + x[1];
            maxI = i;
        } else if (x[0] + x[1] == 0) {
            return i;
        }
    }

//    cout << "maxCnt = " << maxCnt << "\n";

    vector<interval> todo = {{0, N, 0, maxCnt, 0}};
    while (todo.size() > 0) {
        auto x = todo.back();
        todo.pop_back();
        if (x.midCnt == 0) {
            continue;
        }
        if (x.low + 1 >= x.high) {
            smalls.push_back(x.low);
            continue;
        }
        if (x.midCnt > 10) {
            printinterval(x);
        }
        int mid = (x.low + x.high) / 2;
        bool done = false;
        for (int i = mid; i != x.high; ++i) {
            auto y = smartAsk(i);
            if (y[0] + y[1] == maxCnt) {
                // we've got a big
                todo.push_back({x.low, mid, x.leftCnt, y[0] - x.leftCnt - (i - mid), y[1] + (i - mid)});
                todo.push_back({i + 1, x.high, y[0], y[1] - x.rightCnt, x.rightCnt});
                done = true;
                break;
            } else if (y[0] + y[1] == 0) {
                return i;
            } else {
                // we've got a small
//                cout << "small = " << i << "\n";
                smalls.push_back(i);
            }
        }
        for (int i = mid - 1; !done && i >= x.low; --i) {
            auto y = smartAsk(i);
            if (y[0] + y[1] == maxCnt) {
                // we've got a big
                todo.push_back({x.low, i, x.leftCnt, y[0] - x.leftCnt, y[1]});
                todo.push_back({mid + 1, x.high, y[0] + (mid - i), y[1] - x.rightCnt - (mid - i), x.rightCnt});
                break;
            } else if (y[0] + y[1] == 0) {
                return i;
            } else {
//                 we've got a small
//                cout << "small = " << i << "\n";
                smalls.push_back(i);
            }
        }
    }

    for (auto x : smalls) {
        auto y = smartAsk(x);
        if (y[0] + y[1] == 0) {
            return x;
        }
//        cout << x << "\n";
    }
}
//
//static const int max_q = 10000;
//static int n;
//static int query_count = 0;
//static vector<int> g;
//static vector<vector<int> > rank_count;
//
//vector<int> ask(int i) {
////    cout << "Query: " << i << "\n";
//	query_count++;
//	if(query_count > max_q) {
//		cerr << "Query limit exceeded" << endl;
//		exit(0);
//	}
//
//	if(i < 0 || i >= n) {
//		cerr << "Bad index: " << i << endl;
//		exit(0);
//	}
//
//	vector<int> res(2);
//	res[0] = rank_count[g[i] - 1][i + 1];
//	res[1] = rank_count[g[i] - 1][n] - res[0];
//	return res;
//}
//
//int main() {
//	cin >> n;
//
//	g.resize(n);
//	for(int i = 0; i < n; i++) {
//		cin >> g[i];
//		if(g[i] < 1) {
//			cerr << "Invalid rank " << g[i] << " at index " << i << endl;
//			exit(0);
//		}
//	}
//
//	int max_rank = *max_element(g.begin(), g.end());
//
//	rank_count.resize(max_rank + 1, vector<int>(n + 1, 0));
//	for(int r = 0; r <= max_rank; r++) {
//		for(int i = 1; i <= n; i++) {
//			rank_count[r][i] = rank_count[r][i - 1];
//			if(g[i - 1] == r)
//			  rank_count[r][i]++;
//		}
//	}
//
//	for(int i = 0; i <= n; i++)
//		for(int r = 1; r <= max_rank; r++)
//			rank_count[r][i] += rank_count[r - 1][i];
//
//	int res = find_best(n);
//	cout << res << endl << "Query count: " << query_count << endl;
//
//	return 0;
//}

