#include "bits/stdc++.h"
using namespace std;

#define EPS 1e-6

int W, H, X0, Y0, XF, YF;
int F;
vector<int> wx1, wy1, wx2, wy2;

bool overlap(int x0, int x1, int x2, int x3) {
	if (min(x0, x1) < min(x2, x3)) {
		return max(x0, x1) >= min(x2, x3);
	} else if (min(x2, x3) < min(x0, x1)) {
		return max(x2, x3) >= min(x0, x1);
	} else return true;
}

bool contains(int x1, int x2, int x3, int x4, double ipx) {
	return min(x1, x2) <= ipx && ipx <= max(x1, x2) && min(x3, x4) <= ipx && ipx <= max(x3, x4);
}

bool intersects(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3) {
	// cout << x0 << " " << y0 << " " << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x3 << " " << y3 << ": ";
	if (x0 == x1 && x2 == x3) {
		if (x1 != x2) return false;
		return overlap(y0, y1, y2, y3);
	} else if (x0 == x1) {
		double m = (y2 - y3) / (double) (x2 - x3);
		if (abs(m) <= EPS) {
			return overlap(x0, x1, x2, x3) && overlap(y0, y1, y2, y3);
		}
		double b = y2 - m * x2;
		double ipx = x0;
		double ipy = m * ipx + b;
		return contains(y0, y1, y2, y3, ipy);
	} else if (x2 == x3) {
		double m = (y0 - y1) / (double) (x0 - x1);
		if (abs(m) <= EPS) {
			return overlap(x0, x1, x2, x3) && overlap(y0, y1, y2, y3);
		}
		double b = y0 - m * x0;
		double ipx = x2;
		double ipy = m * ipx + b;
		return contains(y0, y1, y2, y3, ipy);
	} else {
		double m1 = (y0 - y1) / (double) (x0 - x1);
		double m2 = (y2 - y3) / (double) (x2 - x3);
		double b1 = y1 - m1 * x1;
		double b2 = y3 - m2 * x3;
		if (abs(m1 - m2) <= EPS) {
			if (abs(b1 - b2) > EPS) {
				return false;
			}
			return overlap(x0, x1, x2, x3);
		}
		double ipx = (b2 - b1) / (m1 - m2);
		return contains(x0, x1, x2, x3, ipx);
	}
}

bool valid(int x0, int y0, int x1, int y1) {
	if (x1 < 0 || y1 < 0 || x1 >= W || y1 >= H) {
		return false;
	}
	if (x0 == x1 && y0 == y1) return true;
	for (int i = 0; i < F; ++i) {
		if (intersects(x0, y0, x1, y1, wx1[i], wy1[i], wx2[i], wy2[i])) {
			// cout << "Overlap" << endl;
			return false;
		}
		// cout << "No Overlap" << endl;
	}
	// cout << "valid" << endl;
	return true;
}

int main() {
	while (cin >> W >> H >> X0 >> Y0 >> XF >> YF >> F) {
		wx1.resize(F); wy1.resize(F); wx2.resize(F); wy2.resize(F);
		for (int i = 0; i < F; ++i) {
			cin >> wx1[i] >> wy1[i] >> wx2[i] >> wy2[i];
		}
		static unsigned A[64][64][30][30];
		memset(A, -1, 4*64*64*30*30);
		queue<tuple<int, int, int, int>> q;
		q.push(make_tuple(X0, Y0, 0, 0));
		A[X0][Y0][15][15] = 0;
		while (q.size() && A[XF][YF][15][15] == (unsigned) -1) {
			auto cur = q.front();
			q.pop();

			int x = get<0>(cur), y = get<1>(cur), vx = get<2>(cur), vy = get<3>(cur);
			int d = A[x][y][vx+15][vy+15];
			// cout << x << " " << y << " " << vx << " " << vy << endl;
			if (valid(x, y, x + vx, y + vy) && A[x + vx][y + vy][vx+15][vy+15] > d + 1) {
				A[x + vx][y + vy][vx+15][vy+15] = d + 1;
				q.push(make_tuple(x + vx, y + vy, vx, vy));
			}
			vx += 1;
			if (valid(x, y, x + vx, y + vy) && A[x + vx][y + vy][vx+15][vy+15] > d + 1) {
				A[x + vx][y + vy][vx+15][vy+15] = d + 1;
				q.push(make_tuple(x + vx, y + vy, vx, vy));
			}
			vx -= 2;
			//printf("%d %d %d %d %d\n", x, y, x +vx, y+vy, A[x+vx][y+vy][vx+15][vy+15]);
			if (valid(x, y, x + vx, y + vy) && A[x + vx][y + vy][vx+15][vy+15] > d + 1) {
				A[x + vx][y + vy][vx+15][vy+15] = d + 1;
				q.push(make_tuple(x + vx, y + vy, vx, vy));
			}
			vx += 1; vy += 1;
			if (valid(x, y, x + vx, y + vy) && A[x + vx][y + vy][vx+15][vy+15] > d + 1) {
				A[x + vx][y + vy][vx+15][vy+15] = d + 1;
				q.push(make_tuple(x + vx, y + vy, vx, vy));
			}
			vy -= 2;
			if (valid(x, y, x + vx, y + vy) && A[x + vx][y + vy][vx+15][vy+15] > d + 1) {
				A[x + vx][y + vy][vx+15][vy+15] = d + 1;
				q.push(make_tuple(x + vx, y + vy, vx, vy));
			}
		}
		cout << A[XF][YF][15][15] << endl;

		wx1.clear(); wx2.clear(); wy1.clear(); wy2.clear();
	}
}